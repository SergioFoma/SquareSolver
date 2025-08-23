#include "test.h"

#include <math.h>
#include <stdio.h>
#include <assert.h>

int testSolve( SolveResult truResult, SolveResult* actualResult ) {

    assert( actualResult != NULL );

    if ( isnan(truResult.x1) && isnan(truResult.x2) && isnan( (*actualResult).x1 ) &&
         isnan( (*actualResult).x2 ) ) {

        return 1;
    }

    else if ( fabs( truResult.x1 - (*actualResult).x1 ) <= delta  &&
              fabs( truResult.x2 - (*actualResult).x2 <= delta ) &&
              fabs( truResult.countRoots - (*actualResult).countRoots) <= delta) {

        return 1;
    }
    else {

        return 0;
    }
}

void printFail( Coefficients coeff, SolveResult truResult, SolveResult* actualResult ) {

    assert( actualResult != NULL );

    printf("\n\nFALED: solveEquation( %lg %lg %lg ) -> x1 = %lg, x2 = %lg, countRoots = %d"
           " should be( x1 = %lg, x2 = %lg, countRoots = %d)", coeff.a, coeff.b, coeff.c,
           (*actualResult).x1, (*actualResult).x2, (*actualResult).countRoots,
           truResult.x1, truResult.x2, truResult.countRoots );

}

 void test() {

    Coefficients coeff = { 2, 4, 2 };
    SolveResult truResult = { -1, -1, twoSameRoot };
    SolveResult actualResult = solveEquation( coeff );

    if (!testSolve( truResult, &actualResult ) ) {

        printFail( coeff, truResult, &actualResult );
    }
    else {

        printf("\nok\n");
    }

    coeff = { 1.2, -123.7, 11.1};
    truResult = { 0.0898115, 102.993522, twoRoot };
    actualResult = solveEquation( coeff );

    if (!testSolve( truResult, &actualResult ) ) {

        printFail( coeff, truResult, &actualResult );
    }
    else {

        printf("ok\n");
    }

    coeff = { 0, 0, 0 };
    truResult = { NAN, NAN, alotRoot };
    actualResult = solveEquation( coeff );

    if (!testSolve( truResult, &actualResult ) ) {

        printFail( coeff, truResult, &actualResult );
    }
    else {

        printf("ok\n");
    }

    coeff = { 0, 1, 0 };
    truResult = { 0, 0, oneRoot };
    actualResult = solveEquation( coeff );

    if (!testSolve( truResult, &actualResult ) ) {

        printFail( coeff, truResult, &actualResult );
    }
    else {

        printf("ok\n");
    }

    coeff = { 0, 0, 1 };
    truResult = { NAN, NAN, zeroRoot };
    actualResult = solveEquation( coeff );

    if (!testSolve( truResult, &actualResult ) ) {

        printFail( coeff, truResult, &actualResult );
    }
    else {

        printf("ok\n");
    }
 }
