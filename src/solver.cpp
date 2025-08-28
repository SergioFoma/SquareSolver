#include "solver.h"
#include "myAssert.h"
#include "mathComparison.h"

#include <ctype.h>
#include <math.h>
#include <stdlib.h>

void solveEquation( Coefficients coefficients, SolveResult* answer ) {

    myAssert( answer != NULL, (void)0 )

    if ( mathComparison( coefficients.a, 0.0 ) )  {
        solveLinear( coefficients, answer );
    }
    else {
        solveSquare( coefficients, answer );
    }
}

void solveSquare( Coefficients coefficients, SolveResult* answer ) {

    myAssert( answer != NULL , (void)0 )

    double D = coefficients.b * coefficients.b - 4 * coefficients.a * coefficients.c;

    if ( D < 0 ) {
        ( answer->countRoots ) = zeroRoot;
    }
    else {
        double firstPart = - coefficients.b / ( 2 * coefficients.a );
        double secondPart = sqrt( D ) / ( 2 * coefficients.a );

        ( answer->x1) = firstPart - secondPart;
        ( answer->x2) = firstPart + secondPart;
        ( answer->countRoots) = ( mathComparison(answer->x1, answer->x2) ) ? twoSameRoot: twoRoot;
    }
}

void solveLinear( Coefficients coefficients, SolveResult* answer ) {

    myAssert( answer != NULL, (void)0 )

    if( mathComparison( coefficients.b, 0 ) && mathComparison( coefficients.c, 0) ) {
        ( answer->countRoots ) = alotRoot;
    }
    else if( mathComparison( coefficients.b, 0 ) && !mathComparison( coefficients.c, 0 ) ){
        ( answer->countRoots) = zeroRoot;
    }
    else {
        answer->x1 = answer->x2 = -coefficients.c / coefficients.b;
        ( answer->countRoots ) = oneRoot;
    }
}
