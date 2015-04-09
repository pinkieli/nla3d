// This file is a part of nla3d project. For information about authors and
// licensing go to project's repository on github:
// https://github.com/dmitryikh/nla3d 

#pragma once
#include "sys.h"

namespace nla3d {

namespace math {

class SparseSymmetricMatrix;

// EquationSolver - abstract class for solving a system of linear equations.
// This class primarly used in FESolver class.

class EquationSolver {
public:
  virtual void solveEquations (math::SparseSymmetricMatrix* matrix, double* rhs, double* unknowns) = 0;
  void setSymmetric (bool symmetric = true);
  void setPositive (bool positive = true);
protected:
  uint32 numberOfEquations = 0;

  // number of rhs 
	int nrhs = 1; 
  bool isSymmetric = true;
  bool isPositive = true;
};

class PARDISO_equationSolver : public EquationSolver {
public:
  ~PARDISO_equationSolver ();
  void solveEquations (math::SparseSymmetricMatrix* matrix, double* rhs, double* unknowns);
protected:
  void initializePARDISO (math::SparseSymmetricMatrix* matrix);
  void releasePARDISO ();

  // Internal solver memory pointer pt
	void *pt[64]; 
  // Paramaters for PARDISO solver (see MKL manual for clarifications)
	int iparm[64];

  // maximum number of numerical factorizations
	int maxfct = 1; 

  // which factorization to use
	int mnum = 1; 
  // don't print statistical information in file
	int msglvl = 0; 
  
  bool firstRun = true;
  // real symmetric undifinite defined matrix
	int mtype = -2; 
};

extern EquationSolver* defaultEquationSolver;

} // namespace math

} //namespace nla3d
