#ifndef H_TEST
#define H_TEST

#include "solver.h"

void test();

int testSolve( SolveResult truResult, SolveResult* actualResult );

void printFail( Coefficients coeff, SolveResult truResult, SolveResult* actualResult );

#endif
