#ifndef H_SOLVER
#define H_SOLVER

enum RootsCount {

    zeroRoot = 0,
    twoRoot = 1,
    oneRoot = 2,
    alotRoot = 3,
    twoSameRoot = 4

}; // возможное количество решений

const double delta = 1e-5; // Дельта окрестность

struct Coefficients {

    double a;
    double b;
    double c;
};

struct SolveResult {

    double x1;
    double x2;

    RootsCount countRoots;
};

SolveResult solveEquation( Coefficients coefficients );

void solveSquare( Coefficients coefficients, double* x1, double* x2, RootsCount* countRoots );

void solveLinear( Coefficients coefficients, double* x1, double* x2, RootsCount* countRoots );

#endif
