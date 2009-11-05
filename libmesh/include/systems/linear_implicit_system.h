// $Id$

// The libMesh Finite Element Library.
// Copyright (C) 2002-2008 Benjamin S. Kirk, John W. Peterson, Roy H. Stogner
  
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



#ifndef __linear_implicit_system_h__
#define __linear_implicit_system_h__

// C++ includes

// Local Includes
#include "implicit_system.h"


// Forward Declarations
template <typename T> class LinearSolver;
template <typename T> class ShellMatrix;


/**
 * This class provides a specific system class.  It aims
 * at implicit systems, offering nothing more than just
 * the essentials needed to solve a system.  Note
 * that still additional vectors/matrices may be added,
 * as offered in the parent class \p ExplicitSystem.
 */

// ------------------------------------------------------------
// LinearImplicitSystem class definition

class LinearImplicitSystem : public ImplicitSystem
{
public:

  /**
   * Constructor.  Optionally initializes required
   * data structures.
   */
  LinearImplicitSystem (EquationSystems& es,
			const std::string& name,
			const unsigned int number);

  /**
   * Destructor.
   */
  virtual ~LinearImplicitSystem ();

  /**
   * The type of system.
   */
  typedef LinearImplicitSystem sys_type;

  /**
   * The type of the parent.
   */
  typedef ImplicitSystem Parent;
  
  /**
   * @returns a clever pointer to the system.
   */
  sys_type & system () { return *this; }
  
  /**
   * Clear all the data structures associated with
   * the system. 
   */
  virtual void clear ();

  /**
   * Reinitializes the member data fields associated with
   * the system, so that, e.g., \p assemble() may be used.
   */
  virtual void reinit ();
   
  /**
   * Prepares \p matrix and \p _dof_map for matrix assembly.
   * Does not actually assemble anything.  For matrix assembly,
   * use the \p assemble() in derived classes.
   * @e Should be overloaded in derived classes.
   */
  virtual void assemble () { ImplicitSystem::assemble(); }
 
  /**
   * Assembles & solves the linear system A*x=b. 
   */
  virtual void solve ();
 
  /**
   * Returns a pointer to a linear solver appropriate for use in
   * adjoint and/or sensitivity solves
   */
  virtual LinearSolver<Number> *get_linear_solver() const;

  /**
   * Releases a pointer to a linear solver acquired by 
   * \p this->get_linear_solver()
   */
  virtual void release_linear_solver(LinearSolver<Number> *) const;

  /**
   * Assembles a residual in \p rhs and/or a jacobian in \p matrix,
   * as requested.
   */
  virtual void assembly(bool get_residual, bool get_jacobian);

  /**
   * @returns \p "LinearImplicit".  Helps in identifying
   * the system type in an equation system file.
   */
  virtual std::string system_type () const { return "LinearImplicit"; }

  /**
   * The \p LinearSolver defines the interface used to
   * solve the linear_implicit system.  This class handles all the
   * details of interfacing with various linear algebra packages
   * like PETSc or LASPACK.
   */
  AutoPtr<LinearSolver<Number> > linear_solver;
  
  /**
   * Returns  the number of iterations 
   * taken for the most recent linear solve.
   */
  unsigned int n_linear_iterations() const { return _n_linear_iterations; }

  /**
   * Returns the final residual for the linear system solve.
   */
  Real final_linear_residual() const { return _final_linear_residual; }
  
  /**
   * This function enables the user to provide a shell matrix, i.e. a
   * matrix that is not stored element-wise, but as a function.  When
   * you register your shell matrix using this function, calling \p
   * solve() will no longer use the \p matrix member but the
   * registered shell matrix instead.  You can reset this behaviour to
   * its original state by supplying a \p NULL pointer to this
   * function.
   */
  void attach_shell_matrix (ShellMatrix<Number>* shell_matrix);
  
  /**
   * Detaches a shell matrix.  Same as \p attach_shell_matrix(NULL).
   */
  void detach_shell_matrix (void) { attach_shell_matrix(NULL); }

  /**
   * Returns a pointer to the currently attached shell matrix, if any,
   * or \p NULL else.
   */
  ShellMatrix<Number>* get_shell_matrix(void) { return _shell_matrix; }
  
protected:
  
  /**
   * The number of linear iterations required to solve the linear
   * system Ax=b.
   */
  unsigned int _n_linear_iterations;

  /**
   * The final residual for the linear system Ax=b.
   */
  Real _final_linear_residual;

  /**
   * User supplies shell matrix or \p NULL if no shell matrix is used.
   */
  ShellMatrix<Number>* _shell_matrix;

};



// ------------------------------------------------------------
// LinearImplicitSystem inline methods


#endif
