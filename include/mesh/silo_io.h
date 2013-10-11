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



#ifndef LIBMESH_SILO_IO_H
#define LIBMESH_SILO_IO_H

// Local includes
#include "libmesh/libmesh_config.h"
#include "libmesh/libmesh_common.h"
#include "libmesh/mesh_output.h"
#include "libmesh/mesh_input.h"

namespace libMesh
{

namespace Silo {
#include "silo.h"
}

// Forward declarations
class MeshBase;

/**
 * This class implements writing meshes in the Silo format.
 * For a full description of the Silo format and to obtain the
 * Silo software see
 * <a href="http://silo.llnl.gov">the Silo home page</a>
 *
 * @author Mark C. Miller, 2013
 */

// ------------------------------------------------------------
// SiloIO class definition
class SiloIO : public MeshInput<MeshBase>,
	       public MeshOutput<MeshBase>,
               public ParallelObject

{
 public:

  /**
   * Constructor.  Takes a reference to a constant mesh object.
   * This constructor will only allow us to write the mesh.
   */
  explicit
  SiloIO (const MeshBase&);

  /**
   * Constructor.  Takes a writeable reference to a mesh object.
   * This constructor is required to let us read in a mesh.
   */
  explicit
  SiloIO (MeshBase&);

  virtual ~SiloIO();

  /**
   * This method implements writing a mesh to a specified file.
   */
  virtual void write (const std::string& );

  /**
   * This method implements writing a mesh with nodal data to a
   * specified file where the nodal data and variable names are provided.
   */
  virtual void write_nodal_data (const std::string&,
				 const std::vector<Number>&,
				 const std::vector<std::string>&);

   /**
    * This method implements reading a mesh from a specified file.
    */
  virtual void read (const std::string& mesh_file);

private:

#if LIBMESH_HAVE_SILO
  Silo::DBfile *get_file_handle(const std::string&);

  Silo::DBfile *_dbfile;
#endif

};

} // namespace libMesh


#endif // LIBMESH_SILO_IO_H
