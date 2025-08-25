#include <TXLib.h>
#include "test.h"

#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

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

void testFromFunction() {

    TestCaseData testData[] = { 
                                { {2, 4, 2}, {-1, -1, twoSameRoot} }, 
                                { {1.2, -123.7, 11.1}, {0.0898115, 102.993522, twoRoot} },
                                { {0, 0, 0}, {NAN, NAN, alotRoot} },
                                {{0, 1, 0}, {0, 0, oneRoot} },
                                { {0, 0, 1}, {NAN, NAN, zeroRoot} }
                            };
    
    size_t testCount = sizeof( testData ) / sizeof( testData[ 0 ] );

    test( testData, testCount );
}

RootsCount getCountRoots( const char* lineCountRoots ) {

    if ( strcmp( lineCountRoots, "zeroRoot") == 0 ) {

        return zeroRoot;
    }
    else if ( strcmp( lineCountRoots, "twoRoot" ) == 0) {

        return twoRoot;
    }
    else if ( strcmp( lineCountRoots, "oneRoot" ) == 0) {

        return oneRoot;
    }
    else if ( strcmp( lineCountRoots, "alotRoot" ) == 0) {

        return alotRoot;
    }
    else if ( strcmp( lineCountRoots, "twoSameRoot" ) == 0 ) {

        return twoSameRoot;
    }
    
    printf("Ошибка считывания количества корней уравнения");

    return zeroRoot;
}

void testFromFile( char* testName ) {

    FILE* testFile;

    testFile = fopen( testName, "r");

    const size_t testCount = 5;
    TestCaseData testData [ testCount ];

    if ( testFile == NULL ) {
        
        printf("Ошибка открытия файла.");
    }
    else {

        for ( size_t line = 0; line < testCount; line++ ) {

            TestCaseData testCase = {};

            char lineCountRoots[ 1000 ] = "";
            
            double* numbers[] = { &testCase.coeff.a, &testCase.coeff.b, &testCase.coeff.c, 
                                  &testCase.truResult.x1, &testCase.truResult.x2 };
            
            for ( int indexNumbers = 0; indexNumbers < 5; indexNumbers++ ) {

                if ( fscanf( testFile, "%lg", numbers[ indexNumbers ] ) == 1 ) {

                    continue;
                }
                else {

                    char trash[ 100 ] = "";

                    fscanf( testFile, "%100s", trash);

                    if ( strncmp( trash, "NAN", 3 ) == 0 ) {

                        *numbers[ indexNumbers ] = NAN;
                    }
                }

            }

            fscanf( testFile, "%s", lineCountRoots);

            while ( fgetc( testFile ) != '\n' );
            
            testCase.truResult.countRoots = getCountRoots( lineCountRoots );

            testData[ line ] = testCase;
        }
    }

    test( testData, testCount );

    fclose( testFile );

}

void test(TestCaseData* testData, const size_t testCount) {

    for (size_t testIndex = 0; testIndex < testCount ; testIndex++ ) {

        if( !testSolve( testData[ testIndex ] ) ) {

            printFail( testData[ testIndex] );
        }
        else {

            printf("Complited successfully with coefficients %lg %lg %lg\n",
                    testData[ testIndex ].coeff.a, testData[ testIndex ].coeff.b, testData[ testIndex ].coeff.c );
        }
    }

 }
