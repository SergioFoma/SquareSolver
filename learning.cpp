#include <TXLib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

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

void printResult( Coefficients coefficients, SolveResult answer );

void test();

int testSolve( SolveResult truResult, SolveResult* actualResult );

void printFail( Coefficients coeff, SolveResult truResult, SolveResult* actualResult );


int main( ) {

    printf("Введите коэффициенты квадратного уравнения( a, b и c соответсвенно)"
    " на следующей строке через пробел: \n\n");

    Coefficients coefficients;

    if ( scanf("%lg %lg %lg", &coefficients.a, &coefficients.b, &coefficients.c) < 3 ) {

        printf("\nОшибка. Введен неверный формат квадратного уравнения.");
        return 0;
    }

    test();

    SolveResult answer = solveEquation( coefficients );
    printResult( coefficients, answer );

    return 0;
}

//------------------------------------------------------------------------------------------------------
//!
//! @param [in] coefficients    coefficients - структура, содержащая коэффициенты квадратного уравнения.
//!
//! @note   Вызывает либо решение линейного уравнения ( solveLinear ), либо квадратного (solveSquare ).
//! Возращает структуру, в которую передаются корни ур - я и количество корней.
//!
//------------------------------------------------------------------------------------------------------

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


//----------------------------------------------------------------------------------------------------
//!
//! @param [in] coefficients   coefficients - структура, содержащая коэффициенты квадратного уравнения.
//! @param [in] *x1   *x1 - указатель на меньший корень уравнения.
//! @param [in] *x2   *x2 - указатель на больший корень уравнения.
//! @param [in] *countRoots    *countRoots- указатель на количество корней.
//!
//! @note Решает квадратное уравнение, записывает результат в x1, x2 и countRoots соответственно.
//-----------------------------------------------------------------------------------------------------
void solveSquare( Coefficients coefficients, double* x1, double* x2, RootsCount* countRoots ) {

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

//-----------------------------------------------------------------------------------------------------
//!
//! @param [in] coefficients   coefficients - структура, содержащая коэффициенты квадратного уравнения.
//! @param [in] answer  answer - структура, сожеражащая корни уравнения и их количество.
//!
//! @note Выводит соответсвующие пояснение и решение.
//!
//-----------------------------------------------------------------------------------------------------
void printResult( Coefficients coefficients, SolveResult answer ) {

    printf("\na: %lg b: %lg c: %lg\n", coefficients.a, coefficients.b, coefficients.c );

    switch ( answer.countRoots ) {

        case zeroRoot:

            printf("\nНет корней.");
            break;

        case twoRoot:

            printf("\nУравнение квадратное.\nМеньший корень: %lg\nБольший корень: %lg",
            answer.x1, answer.x2 );
            break;

        case oneRoot:

            printf("\nУравнение линейное.\nКорень уравнения: %lg", answer.x1 );
            break;

        case alotRoot:

            printf("\nУравнение имеет бесконечное количество корней.");
            break;

        case twoSameRoot:

            printf("\nУравнение квадратное.\nИмеет единственный корень: %lg", answer.x1 );
            break;

        default:

            printf("\nОшибка. Не определено количество корней.");
            break;
    }
}
//-----------------------------------------------------------------------------------------------------
//!
//! @param [in] coefficients   coefficients - структура, содержащая коэффициенты квадратного уравнения.
//! @param [in] *x1   *x1 - указатель на меньший корень уравнения.
//! @param [in] *x2   *x2 - указатель на больший корень уравнения.
//! @param [in] *countRoots    *countRoots- указатель на количество корней.
//!
//! @note Решает линейное уравнение, результат записывает в x1, x2 и countRoots соотвественно.
//!
//------------------------------------------------------------------------------------------------------
void solveLinear( Coefficients coefficients, double* x1, double* x2, RootsCount* countRoots ) {

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

int testSolve( SolveResult truResult, SolveResult* actualResult ) {

    if ( isnan(truResult.x1) && isnan(truResult.x2) && isnan( (*actualResult).x1 )
    && isnan( (*actualResult).x2 ) ) {

        return 1;
    }

    else if ( fabs( truResult.x1 - (*actualResult).x1 ) <= delta  &&
    fabs( truResult.x2 - (*actualResult).x2 <= delta )
    && fabs( truResult.countRoots - (*actualResult).countRoots) <= delta) {

        return 1;
    }
    else {

        return 0;
    }
}

void printFail( Coefficients coeff, SolveResult truResult, SolveResult* actualResult ) {

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

    coeff = { 1.2, -123.7, 11.1};
    truResult = { 0.0898115, 102.993522, twoRoot };
    actualResult = solveEquation( coeff );

    if (!testSolve( truResult, &actualResult ) ) {

        printFail( coeff, truResult, &actualResult );
    }

    coeff = { 0, 0, 0 };
    truResult = { NAN, NAN, alotRoot };
    actualResult = solveEquation( coeff );

    if (!testSolve( truResult, &actualResult ) ) {

        printFail( coeff, truResult, &actualResult );
    }

    coeff = { 0, 1, 0 };
    truResult = { 0, 0, oneRoot };
    actualResult = solveEquation( coeff );

    if (!testSolve( truResult, &actualResult ) ) {

        printFail( coeff, truResult, &actualResult );
    }

    coeff = { 0, 0, 1 };
    truResult = { NAN, NAN, zeroRoot };
    actualResult = solveEquation( coeff );

    if (!testSolve( truResult, &actualResult ) ) {

        printFail( coeff, truResult, &actualResult );
    }


 }




