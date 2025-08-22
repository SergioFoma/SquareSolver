#include <TXLib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

enum rootsCount {

    zeroRoot = 0,
    twoRoot = 1,
    oneRoot = 2,
    alotRoot = 3,
    twoSameRoot = 4

}; // возможное количество решений

const double delta = 1e-8; // Дельта окрестность

struct Coefficients {

    double a;
    double b;
    double c;
};

double getDiscriminant( struct Coefficients coefficients );

void solveSquare( struct Coefficients coefficients );

void solveEquation( struct Coefficients coefficients );

void printResault( rootsCount typeOfEquation, struct Coefficients coefficients , double result1, double result2 );

void solveLinear( struct Coefficients coefficients );

int main( ) {

    printf("Введите коэффициенты квадратного уравнения( a, b и c соответсвенно)"
    " на следующей строке через пробел: \n\n");

    Coefficients coefficients;

    if ( scanf("%lg %lg %lg", &coefficients.a, &coefficients.b, &coefficients.c) < 3 ) {

        printf("\nОшибка. Введен неверный формат квадратного уравнения.");
        return 0;
    }

    solveEquation( coefficients );

    return 0;
}

//----------------------------------------------------------------------------------------------------
//!
//! @param [in] a   a - коэффициент
//! @param [in] b   b - коэффициент
//! @param [in] c   c - коэффициент
//! @param [in] delta delta - эпсилон окрестноть
//!
//! @note   Вызывает либо решение линейного уравнения ( solveLinear ), либо квадратного (solveSquare ).
//!
//!----------------------------------------------------------------------------------------------------

void solveEquation( struct Coefficients coefficients ) {

    if ( fabs( coefficients.a ) <= delta ) {

        solveLinear( coefficients );
    }
    else {
        solveSquare( coefficients );
    }

}


//!------------------------------------------------------------------
//!
//! @param [in] a   a - коэффициент
//! @param [in] b   b - коэффициент
//! @param [in] c   c - коэффициент
//!
//! @note Решает квадратное уравнение
//!------------------------------------------------------------------
void solveSquare( struct Coefficients coefficients ) {

    double D = coefficients.b * coefficients.b - 4 * coefficients.a * coefficients.c;

    if ( D < -delta ) {

        printResault( zeroRoot, coefficients, 0, 0 );
    }

    else {

        double firstPart = - coefficients.b / ( 2 * coefficients.a );
        double secondPart = sqrt( D ) / ( 2 * coefficients.a );

        double x1 = firstPart - secondPart;
        double x2 = firstPart + secondPart;

        if ( fabs( x1  - x2 ) <= delta ) {

            printResault( twoSameRoot, coefficients, x1, x2 );
        }
        else {

            printResault( twoRoot, coefficients, x1, x2 );
        }
    }
}

//!---------------------------------------------------------------------------------------------------
//!
//! @param [in] typeOfEquation typeOfEquation - тип уравнения
//! @param [in] a               a - коэффициент
//! @param [in] b               b - коэффициент
//! @param [in] c               c - коэффициент
//! @param [in] result1         result1 - первый корень
//! @param [in] result2         result2 - второй корень
//!
//! @note Выводит соответсвующие пояснение и решение
//!---------------------------------------------------------------------------------------------------
void printResault( rootsCount typeOfEquation, struct Coefficients coefficients, double result1, double result2 ) {

    printf("\na: %lg b: %lg c: %lg\n", coefficients.a, coefficients.b, coefficients.c );

    switch ( typeOfEquation ) {

        case zeroRoot:

            printf("\nНет корней.");
            break;

        case twoRoot:

            printf("\nУравнение квадратное.\nМеньший корень: %lg\nБольший корень: %lg", result1, result2 );
            break;

        case oneRoot:

            printf("\nУравнение линейное.\nКорень уравнения: %lg", result1 );
            break;

        case alotRoot:

            printf("\nУравнение имеет бесконечное количество корней.");
            break;

        case twoSameRoot:

            printf("\nУравнение квадратное.\nИмеет единственный корень: %lg", result1 );
            break;

        default:

            printf("\nОшибка. Не определено количество корней.");
            break;
    }
}
//!-------------------------------------
//!
//! @param [in] b   b - коэффициент
//! @param [in] c   c - коэффициент
//!
//! @note Решает линейное уравнение
//!------------------------------------
void solveLinear( struct Coefficients coefficients ) {

    if( fabs( coefficients.b ) <= delta && fabs( coefficients.c ) <= delta ) {

        printResault( alotRoot, coefficients, 0, 0 );
    }
    else if( fabs( coefficients.b ) <= delta && fabs( coefficients.c ) >= delta ){

        printResault( zeroRoot, coefficients, 0, 0 );
    }
    else {

        double result = -coefficients.c / coefficients.b;
        printResault( oneRoot, coefficients, result, result );
    }

}
