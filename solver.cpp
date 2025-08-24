#include "solver.h"

#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

SolveResult solveEquation( Coefficients coefficients ) {

    double x1 = NAN, x2 = NAN;
    RootsCount countRoots = zeroRoot;

    if ( fabs( coefficients.a ) <= delta ) {

        solveLinear( coefficients, &x1, &x2, &countRoots );
    }
    else {

        solveSquare( coefficients, &x1, &x2, &countRoots );
    }

    return { x1, x2, countRoots };
}

void solveSquare( Coefficients coefficients, double* x1, double* x2, RootsCount* countRoots ) {

    assert( x1 != NULL );
    assert( x2 != NULL );
    assert( countRoots != NULL );

    double D = coefficients.b * coefficients.b - 4 * coefficients.a * coefficients.c;

    if ( D < -delta ) {

        *countRoots = zeroRoot;
    }

    else {

        double firstPart = - coefficients.b / ( 2 * coefficients.a );
        double secondPart = sqrt( D ) / ( 2 * coefficients.a );

        *x1 = firstPart - secondPart;
        *x2 = firstPart + secondPart;
        *countRoots = ( fabs( *x1 - *x2) < delta ) ? twoSameRoot: twoRoot;
    }
}

void solveLinear( Coefficients coefficients, double* x1, double* x2, RootsCount* countRoots ) {

    assert( x1 != NULL );
    assert( x2 != NULL );
    assert( countRoots != NULL );

    if( fabs( coefficients.b ) <= delta && fabs( coefficients.c ) <= delta ) {

        *countRoots = alotRoot;
    }
    else if( fabs( coefficients.b ) <= delta && fabs( coefficients.c ) >= delta ){

        *countRoots = zeroRoot;
    }
    else {

        *x1 = *x2 = -coefficients.c / coefficients.b;
        *countRoots = oneRoot;
    }

}
