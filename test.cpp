#include "test.h"

#include <math.h>
#include <stdio.h>
#include <assert.h>

int testSolve( TestCaseData caseData ) {

    SolveResult actualResult = { NAN, NAN, zeroRoot };
    solveEquation( caseData.coeff, &actualResult);

    if ( isnan( caseData.truResult.x1 ) && isnan( caseData.truResult.x2) && isnan( actualResult.x1) &&
         isnan( actualResult.x2 ) ) {

        return 1;
    }
    else if ( fabs( caseData.truResult.x1 - actualResult.x1 ) <= delta &&
              fabs( caseData.truResult.x2 - actualResult.x2) <= delta &&
              caseData.truResult.countRoots == actualResult.countRoots ) {
                
        return 1;
    }

    return 0;
}

void printFail( TestCaseData caseData ) {

    SolveResult actualResult = { NAN, NAN, zeroRoot };
    solveEquation( caseData.coeff, &actualResult );

    printf("\n\nFALED: solveEquation( %lg %lg %lg ) -> x1 = %lg, x2 = %lg, countRoots = %d"
           " should be( x1 = %lg, x2 = %lg, countRoots = %d)", caseData.coeff.a, caseData.coeff.b, caseData.coeff.c,
            actualResult.x1, actualResult.x2, actualResult.countRoots,
           caseData.truResult.x1, caseData.truResult.x2, caseData.truResult.countRoots );

}

 void test() {

    TestCaseData tests[] = { 
                                { {2, 4, 2}, {-1, -1, twoSameRoot} }, 
                                { {1.2, -123.7, 11.1}, {0.0898115, 102.993522, twoRoot} },
                                { {0, 0, 0}, {NAN, NAN, alotRoot} },
                                {{0, 1, 0}, {0, 0, oneRoot} },
                                { {0, 0, 1}, {NAN, NAN, zeroRoot} }
                            }; 

    for (size_t testIndex = 0; testIndex < ( sizeof( tests) / sizeof( tests[0] ) ) ; testIndex++ ) {

        if( !testSolve( tests[ testIndex ] ) ) {

            printFail( tests[ testIndex] );
        }
        else {

            printf("Complited successfully with coefficients %lg %lg %lg\n",
                    tests[ testIndex ].coeff.a, tests[ testIndex ].coeff.b, tests[ testIndex ].coeff.c );
        }
    }

 }
