
#include <TXLib.h>
#include "test.h"
#include "myAssert.h"
#include "mathComparison.h"

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

int testSolve( TestCaseData caseData ) {

    SolveResult actualResult = { NAN, NAN, zeroRoot };
    solveEquation( caseData.coeff, &actualResult);

    if ( isnan( caseData.trueResult.x1 ) && isnan( caseData.trueResult.x2) && isnan( actualResult.x1) &&
         isnan( actualResult.x2 ) ) {
        return 1;
    }
    else if ( mathComparison( caseData.trueResult.x1, actualResult.x1 ) &&
              mathComparison( caseData.trueResult.x2, actualResult.x2) &&
              caseData.trueResult.countRoots == actualResult.countRoots ) {
        return 1;
    }
    return 0;
}

void printFail( TestCaseData caseData ) {

    SolveResult actualResult = { NAN, NAN, zeroRoot };
    solveEquation( caseData.coeff, &actualResult );

    printf("\n\n\033[31;40mFALED: solveEquation( %lg %lg %lg ) -> x1 = %lg, x2 = %lg, countRoots = %d"
           " should be( x1 = %lg, x2 = %lg, countRoots = %d)\033[0m", caseData.coeff.a, caseData.coeff.b, caseData.coeff.c,
            actualResult.x1, actualResult.x2, actualResult.countRoots,
           caseData.trueResult.x1, caseData.trueResult.x2, caseData.trueResult.countRoots );

}

void testFromFunction() {

    TestCaseData testData[] = { 
                                { {2, 4, 2}, {-1, -1, twoSameRoot} }, 
                                { {1.2, -123.7, 11.1}, {0.0898115, 102.993522, twoRoot} },
                                { {0, 0, 0}, {NAN, NAN, alotRoot} },
                                { {0, 1, 0}, {0, 0, oneRoot} },
                                { {0, 0, 1}, {NAN, NAN, zeroRoot} }
                            };
    
    size_t testCount = sizeof( testData ) / sizeof( testData[ 0 ] );

    runTestFromArray( testData, testCount );
}

RootsCount getRootsCountFromFile( const char* lineCountRoots ) {

    myAssert( lineCountRoots != NULL, zeroRoot )

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
    
    printf("\033[31;40mОшибка считывания количества корней уравнения\033[0m");
    return zeroRoot;
}

void readNumbersFromFile( FILE* testFile, TestCaseData* testCase ) {

    myAssert( testFile != NULL, (void)0 )
    myAssert( testCase != NULL, (void)0 )

    double* numbers[] = { &( (testCase->coeff).a ), &( (testCase->coeff).b ) , &( (testCase->coeff).c ), 
                         &( (testCase->trueResult).x1 ) , &( (testCase->trueResult).x2 )  };
    
    size_t sizeNumbers = 5;
    size_t maxLineTrash = 100;
    char* trash = ( char* )calloc( maxLineTrash, sizeof( char ) );

    for ( size_t indexNumbers = 0; indexNumbers < sizeNumbers ; indexNumbers++ ) {

        if ( fscanf( testFile, "%lg", numbers[ indexNumbers ]  ) == 1 ) {
            continue;
        }
        else {

            // На Windows нельзя считать в fscanf строчку NAN как duuble, поэтому считываю как строчку,
            // чтобы перевести переменную типа double в NAN в ручную.
            fscanf( testFile, "%100s", trash);

            if ( strncmp( trash, "NAN", 4 ) == 0 ) {

                *numbers[ indexNumbers ] = NAN;
            }
        }
    }

    free( trash );
}

void clearBufferFunction( FILE* testFile ) {

    myAssert( testFile != NULL, (void)0 )

    while ( fgetc( testFile ) != '\n' && fgetc( testFile ) != EOF );
}

int testFromFile( char* testName ) {

    myAssert( testName != NULL, 0)

    FILE* testFile = NULL;

    testFile = fopen( testName, "r");

    if ( testFile == NULL ) {
        printf("\033[31;40mОшибка открытия файла.\033[0m");
        return 0;
    }

    size_t testCount = 0;
    size_t maxLineCountRoots = 100;

    fscanf( testFile, "%u", &testCount );
    clearBufferFunction( testFile );

    TestCaseData* testData = ( TestCaseData* )calloc( testCount,  sizeof( TestCaseData ) );

    if ( testData == NULL ) {
        printf("\033[31;40mПамять переполнена\033[0m");
        return 0;
    }

    char* lineCountRoots = ( char* )calloc( maxLineCountRoots , sizeof( char ) );

    if( lineCountRoots == NULL ) {
        printf("\033[31;40mПамять переполнена\033[0m");
        return 0;
    }

    for ( size_t line = 0; line < testCount; line++ ) {
        
        readNumbersFromFile( testFile, &( testData[ line ] ) );

        fscanf( testFile, "%s", lineCountRoots);
        clearBufferFunction( testFile );
        
        testData[line].trueResult.countRoots = getRootsCountFromFile( lineCountRoots );
    }

    runTestFromArray( testData, testCount );

    free( lineCountRoots );
    free( testData );

    fclose( testFile );
    return 1;
}

void runTestFromArray(const TestCaseData* testData, size_t testCount) {

    myAssert( testData != NULL, (void)0 )

    for (size_t testIndex = 0; testIndex < testCount ; testIndex++ ) {

        if( !testSolve( testData[ testIndex ] ) ) {
            printFail( testData[ testIndex] );
        }
        else {
            printf("\033[32;40mComplited successfully with coefficients %lg %lg %lg\n\033[0m",
                    testData[ testIndex ].coeff.a, testData[ testIndex ].coeff.b, testData[ testIndex ].coeff.c );
        }
    }
 }