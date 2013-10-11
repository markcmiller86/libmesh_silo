// The libMesh Finite Element Library.
// Copyright (C) 2002-2012 Benjamin S. Kirk, John W. Peterson, Roy H. Stogner

// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
#warning UPDATE COPYRIGHT

// LibMesh includes
#include "libmesh/elem.h"
#include "libmesh/silo_io.h"
#include "libmesh/libmesh_logging.h"
#include "libmesh/node.h"
#include "libmesh/parallel_mesh.h"
#include "libmesh/parallel.h"
#include "libmesh/mesh_communication.h"

using namespace Silo;

typedef struct zt_pairs { ElemType lm_type; int silo_type; } zt_pairs;

static const zt_pairs elem_types[] =
{
    {EDGE2,    DB_ZONETYPE_BEAM},
    {TRI3,     DB_ZONETYPE_TRIANGLE},
    {QUAD4,    DB_ZONETYPE_QUAD},
    {TET4,     DB_ZONETYPE_TET},
    {PYRAMID5, DB_ZONETYPE_PYRAMID},
    {PRISM6,   DB_ZONETYPE_PRISM},
    {HEX8,     DB_ZONETYPE_HEX}
};
static const int n_elem_types = sizeof(elem_types)/sizeof(elem_types[0]);

static ElemType lm_elem_type(int st)
{
    static int lastidx = 0;
    if (elem_types[lastidx].silo_type == st)
        return elem_types[lastidx].lm_type;
    for (int i = 0; i < n_elem_types; i++, lastidx++)
    {
        if (lastidx >= n_elem_types) lastidx = 0;
        if (elem_types[lastidx].silo_type == st)
            return elem_types[lastidx].lm_type;
    }
    return INVALID_ELEM;
}

static int silo_elem_type(const ElemType et)
{
    static int lastidx = 0;
    if (elem_types[lastidx].lm_type == et)
        return elem_types[lastidx].silo_type;
    for (int i = 0; i < n_elem_types; i++, lastidx++)
    {
        if (lastidx >= n_elem_types) lastidx = 0;
        if (elem_types[lastidx].lm_type == et)
            return elem_types[lastidx].silo_type;
    }
    return -1;
}

namespace libMesh
{

// ------------------------------------------------------------
// Silo class members
SiloIO::SiloIO (MeshBase& mesh) :
  MeshInput<MeshBase> (mesh, /*is_parallel_format=*/true),
  MeshOutput<MeshBase> (mesh, /*is_parallel_format=*/true),
  ParallelObject (mesh)
{
#if defined(LIBMESH_HAVE_SILO)
    _dbfile = 0;
#endif
}

#if defined(LIBMESH_HAVE_SILO)

SiloIO::~SiloIO()
{
    if (_dbfile) DBClose(_dbfile);
    _dbfile = 0;
}

DBfile *
SiloIO::get_file_handle(const std::string& filename)
{
    if (_dbfile && std::string(_dbfile->pub.name) != filename)
    {
        DBClose(_dbfile);
        _dbfile = 0;
    }

    if (!_dbfile)
        _dbfile = DBCreate(filename.c_str(), 0, DB_LOCAL, "libmesh output", DB_PDB);

    libmesh_assert(_dbfile);
    return _dbfile;
}

void SiloIO::read (const std::string& base_filename)
{
  START_LOG ("read()","SiloIO");

  STOP_LOG ("read()","SiloIO");
}

void SiloIO::write (const std::string& base_filename)
{
    START_LOG ("write()","SiloIO");

    // Get a constant reference to the mesh for writing
    const MeshBase & mesh = MeshOutput<MeshBase>::mesh();

    std::vector<Real> x, y, z;
    dof_id_type num_nodes = mesh.n_nodes();
    x.resize(num_nodes);
    if (mesh.spatial_dimension() > 1)
        y.resize(num_nodes);
    if (mesh.spatial_dimension() > 2)
        z.resize(num_nodes);

    MeshBase::const_node_iterator       it  = mesh.active_nodes_begin();
    const MeshBase::const_node_iterator end = mesh.active_nodes_end();

    for (unsigned int i = 0; it!=end; it++, i++)
    {
        x[i] = (*(*it))(0);
        if (mesh.spatial_dimension() > 1)
            y[i] = (*(*it))(1);
        if (mesh.spatial_dimension() > 2)
            z[i] = (*(*it))(2);
    }

#warning MAY NEED TO TACK ON TIMESTEP TO FILENAME
#warning HOW TO DECIDED DRIVER
#warning MAY NOT NEED TO ALWAYS CREATE
    DBfile *dbfile = get_file_handle(base_filename);

    void* coords[3] = {&x[0], &y[0], &z[0]};
    char* coordnames[3] = {"x","y","z"};
    DBPutUcdmesh(dbfile, "lm_ucdmesh", mesh.spatial_dimension(), coordnames, coords,
                       (int)num_nodes, (int)mesh.n_elem(), "lm_zl", NULL,
                        sizeof(Real)==4?DB_FLOAT:DB_DOUBLE, NULL);

    std::vector<int> silo_nlst;
    std::vector<int> silo_styp;
    std::vector<int> silo_ssiz;
    std::vector<int> silo_scnt;
    std::map<ElemType, bool> silo_elem_types;
    silo_elem_types[NODEELEM] = true;
    ElemType cur_type = INVALID_ELEM;
    int nelems = 0;
    for (MeshBase::const_element_iterator it = mesh.active_elements_begin();
          it != mesh.active_elements_end(); it++)
    {
        const Elem * elem = *it ;

#warning KEEP TRACK OF SKIPPED ELEMS FOR LATER ZONE-CENTERED VARIABLE OUTPUT
        if (silo_elem_type(elem->type()) == -1) continue;
        nelems++;
        if (elem->type() != cur_type)
        {
            silo_styp.push_back(silo_elem_type(elem->type()));
            silo_ssiz.push_back(elem->n_nodes());
            silo_scnt.push_back(0);
            cur_type = elem->type();
        }
        silo_scnt[silo_scnt.size()-1]++;

        // Handle element re-ordering for Silo
        if (cur_type == PRISM6)
        {
            silo_nlst.push_back(elem->node(3));
            silo_nlst.push_back(elem->node(0));
            silo_nlst.push_back(elem->node(1));
            silo_nlst.push_back(elem->node(4));
            silo_nlst.push_back(elem->node(5));
            silo_nlst.push_back(elem->node(2));
        }
        else if (cur_type == TET4)
        {
            silo_nlst.push_back(elem->node(1));
            silo_nlst.push_back(elem->node(0));
            silo_nlst.push_back(elem->node(2));
            silo_nlst.push_back(elem->node(3));
        }
        else
        {
            for (int i = 0; i < elem->n_nodes(); i++)
                silo_nlst.push_back(elem->node(i));
        }
    }

    if (silo_nlst.size())
    {
        DBPutZonelist2 (dbfile, "lm_zl", nelems, mesh.spatial_dimension(),
            &silo_nlst[0], (int) silo_nlst.size(), 0, 0, 0,
            &silo_styp[0], &silo_ssiz[0], &silo_scnt[0], (int) silo_scnt.size(), 0);
    }

    STOP_LOG ("write()","SiloIO");
}

void SiloIO::write_nodal_data (const std::string& base_filename,
                               const std::vector<Number>& soln,
                               const std::vector<std::string>& names)
{
    START_LOG ("write_nodal_data()","SiloIO");

    const MeshBase & mesh = MeshOutput<MeshBase>::mesh();

    // Write the mesh
    SiloIO::write(base_filename);

    DBfile *dbfile = get_file_handle(base_filename);

    int num_vars = libmesh_cast_int<int>(names.size());
    dof_id_type num_nodes = mesh.n_nodes();

    // The names of the variables to be output
    std::vector<std::string> output_names = names;

#if 0
    if(_output_variables.size())
      output_names = _output_variables;
#endif

    // This will count the number of variables actually output
    for (int c=0; c<num_vars; c++)
    {
        std::vector<std::string>::iterator pos =
            std::find(output_names.begin(), output_names.end(), names[c]);
        if (pos == output_names.end())
            continue;

        // Copy out this variable's solution
        std::vector<Number> cur_soln(num_nodes);
        for(dof_id_type i=0; i<num_nodes; i++)
          cur_soln[i] = soln[i*num_vars + c];

        DBPutUcdvar1(dbfile, output_names[c].c_str(), "lm_ucdmesh",
            &cur_soln[0], num_nodes, 0, 0, DB_DOUBLE, DB_NODECENT, 0);
    }

    STOP_LOG ("write_nodal_data()","SiloIO");
}

#else // #if defined(LIBMESH_HAVE_SILO)

void SiloIO::read (const std::string& )
{
  libMesh::err <<  "ERROR, Silo API is not defined!" << std::endl;
  libmesh_error();
}

void SiloIO::write (const std::string& )
{
  libMesh::err <<  "ERROR, Silo API is not defined!" << std::endl;
  libmesh_error();
}

void SiloIO::write_nodal_data (const std::string&,
                               const std::vector<Number>&,
                               const std::vector<std::string>&)
{
  libMesh::err <<  "ERROR, Silo API is not defined!" << std::endl;
  libmesh_error();
}

#endif // #if defined(LIBMESH_HAVE_SILO)

} // namespace libMesh
