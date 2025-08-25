#include "solver.h"

#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

void solveEquation( Coefficients coefficients, SolveResult* answer ) {

    if ( fabs( coefficients.a ) <= delta ) {

        solveLinear( coefficients, answer );
    }
    else {

        solveSquare( coefficients, answer );
    }
}

void solveSquare( Coefficients coefficients, SolveResult* answer ) {

    assert( answer );

    double D = coefficients.b * coefficients.b - 4 * coefficients.a * coefficients.c;

    if ( D < -delta ) {

        ( answer-> countRoots ) = zeroRoot;
    }

    else {

        double firstPart = - coefficients.b / ( 2 * coefficients.a );
        double secondPart = sqrt( D ) / ( 2 * coefficients.a );

        ( answer->x1) = firstPart - secondPart;
        ( answer->x2) = firstPart + secondPart;
        ( answer->countRoots) = ( fabs( answer->x1 - answer->x2) < delta ) ? twoSameRoot: twoRoot;
    }
}

void solveLinear( Coefficients coefficients, SolveResult* answer ) {

    assert( answer );

    if( fabs( coefficients.b ) <= delta && fabs( coefficients.c ) <= delta ) {

        ( answer->countRoots ) = alotRoot;
    }
    else if( fabs( coefficients.b ) <= delta && fabs( coefficients.c ) >= delta ){

        ( answer->countRoots) = zeroRoot;
    }
    else {

        answer->x1 = answer->x2 = -coefficients.c / coefficients.b;
        ( answer->countRoots ) = oneRoot;
    }

}
