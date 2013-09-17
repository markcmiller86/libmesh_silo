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

namespace libMesh
{


// ------------------------------------------------------------
// Silo class members
SiloIO::SiloIO (MeshBase& mesh) :
  MeshInput<MeshBase> (mesh, /*is_parallel_format=*/true),
  MeshOutput<MeshBase> (mesh, /*is_parallel_format=*/true),
  ParallelObject (mesh)
{
}


#if defined(LIBMESH_HAVE_SILO)
void SiloIO::read (const std::string& base_filename)
{
  START_LOG ("read()","SiloIO");

  // This function must be run on all processors at once
  parallel_object_only();

  // Get a reference to the mesh.  We need to be specific
  // since Nemesis_IO is multiply-inherited
  // MeshBase& mesh = this->mesh();
  MeshBase& mesh = MeshInput<MeshBase>::mesh();

  // And if that didn't work, then we're actually reading into a
  // SerialMesh, so forget about gathering neighboring elements
  if (mesh.is_serial())
    return;

  // Gather neighboring elements so that the mesh has the proper "ghost" neighbor information.
  MeshCommunication().gather_neighboring_elements(libmesh_cast_ref<ParallelMesh&>(mesh));
}

#else

void SiloIO::read (const std::string& )
{
  libMesh::err <<  "ERROR, Silo API is not defined!" << std::endl;
  libmesh_error();
}

#endif // #if defined(LIBMESH_HAVE_SILO)


#if defined(LIBMESH_HAVE_SILO)

void SiloIO::write (const std::string& base_filename)
{
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
    DBfile *dbfile = DBCreate(base_filename.c_str(), 0, DB_LOCAL, "libmesh output", DB_PDB);
    libmesh_assert(dbfile);

    void* coords[3] = {&x[0], &y[0], &z[0]};
    char* coordnames[3] = {"x","y","z"};
    DBPutUcdmesh(dbfile, "lm_ucdmesh", mesh.spatial_dimension(), coordnames, coords,
                       (int)num_nodes, (int)mesh.n_elem(), "zonelist", NULL,
                        sizeof(Real)==4?DB_FLOAT:DB_DOUBLE, NULL);

    DBClose(dbfile); 
}

void SiloIO::write_nodal_data (const std::string&,
                               const std::vector<Number>&,
                               const std::vector<std::string>&)
{

}

#else

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
