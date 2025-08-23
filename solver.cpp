#include "solver.h"

#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

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
