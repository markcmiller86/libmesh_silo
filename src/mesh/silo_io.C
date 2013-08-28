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

namespace libMesh
{


//-----------------------------------------------
// anonymous namespace for implementation details
#warning DO WE NEED THIS
namespace {

}



// ------------------------------------------------------------
// Silo class members
SiloIO::SiloIO (MeshBase& mesh) :
  MeshInput<MeshBase> (mesh, /*is_parallel_format=*/true),
  MeshOutput<MeshBase> (mesh, /*is_parallel_format=*/true),
  ParallelObject (mesh),
{
}


#if defined(LIBMESH_HAVE_EXODUS_API) && defined(LIBMESH_HAVE_SILO_API)
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
  libMesh::err <<  "ERROR, Nemesis API is not defined!" << std::endl;
  libmesh_error();
}

#endif // #if defined(LIBMESH_HAVE_EXODUS_API) && defined(LIBMESH_HAVE_SILO_API)





#if defined(LIBMESH_HAVE_EXODUS_API) && defined(LIBMESH_HAVE_SILO_API)

void Nemesis_IO::write (const std::string& base_filename)
{
  // Get a constant reference to the mesh for writing
  const MeshBase & mesh = MeshOutput<MeshBase>::mesh();

  // Create the filename for this processor given the base_filename passed in.
  std::string nemesis_filename = nemhelper->construct_nemesis_filename(base_filename);

}

#else

void Nemesis_IO::write (const std::string& )
{
  libMesh::err <<  "ERROR, Nemesis API is not defined!" << std::endl;
  libmesh_error();
}

#endif // #if defined(LIBMESH_HAVE_EXODUS_API) && defined(LIBMESH_HAVE_SILO_API)


} // namespace libMesh
