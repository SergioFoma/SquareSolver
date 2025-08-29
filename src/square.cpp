#include <TXLib.h>
#include "solver.h"
#include "test.h"
#include "flagSearch.h"
#include "myAssert.h"
#include "paint.h"

#include <stdio.h>
#include <math.h>
#include <stdbool.h>

void printResult( Coefficients coefficients, SolveResult answer );

bool inputCoefficient( Coefficients* coefficients );

int main( int argc, char** argv ) {

    if ( checkOnFlag( argc, argv ) ) {
        return 0;
    }

    colorPrintf( BLINKING, PURPLE, "МЯУ\n\n");
    colorPrintf( NOMODE, YELLOW, "Введите коэффициенты квадратного уравнения( a, b и c соответсвенно)"
                                 " на следующей строке через пробел:\n\n");

    Coefficients coefficients = {0, 0, 0};
    SolveResult answer = { NAN, NAN, zeroRoot};

    if (!inputCoefficient( &coefficients) ) {
        return 0;
    }

    solveEquation( coefficients, &answer );
    printResult( coefficients, answer );

    colorPrintf( BLINKING, YELLOW, "\n\nCOMMIT GITHUB\n");

    return 0;
}

//-----------------------------------------------------------------------------------------------------
//!
//! @param [in] coefficients   coefficients - структура, содержащая коэффициенты квадратного уравнения.
//! @param [in] answer  answer - структура, содержащая корни уравнения и их количество.
//!
//! @note Выводит соответсвующие пояснение и решение.
//!
//-----------------------------------------------------------------------------------------------------
void printResult( Coefficients coefficients, SolveResult answer ) {

    colorPrintf( NOMODE, BLUE, "\n\na: %lg b: %lg c: %lg\n", coefficients.a, coefficients.b, coefficients.c );

    switch ( answer.countRoots ) {
        case zeroRoot:
            colorPrintf( NOMODE, RED, "Нет корней.");
            break;

        case twoRoot:
            colorPrintf( NOMODE, GREEN, "\nУравнение квадратное.\nМеньший корень: %lg\nБольший корень: %lg",
            answer.x1, answer.x2 );
            break;

        case oneRoot:
            colorPrintf( NOMODE, GREEN, "\nУравнение линейное.\nКорень уравнения: %lg", answer.x1 );
            break;

        case alotRoot:
            colorPrintf( NOMODE, GREEN, "\nУравнение имеет бесконечное количество корней.");
            break;

        case twoSameRoot:
            colorPrintf( NOMODE, GREEN,"\nУравнение квадратное.\nИмеет единственный корень: %lg", answer.x1 );
            break;

        default:
            colorPrintf( UNDERLINED, RED, "\nОшибка. Не определено количество корней.");
            break;
    }
}

//-----------------------------------------------------------------------------------------------------
//!
//! @param [in] *coefficients   *coefficients - указатель на структуру, получающую коэффициенты.
//!
//! @return tru при успешном считывании, false при безуспешном.
//!
//! @note Считывает коэффициенты с ввода пользователя в coefficients.
//!
//-----------------------------------------------------------------------------------------------------
bool inputCoefficient( Coefficients* coefficients) {

    myAssert( coefficients != NULL , 0 );

    if ( scanf("%lg %lg %lg", &( coefficients->a ), &( coefficients->b ), &( coefficients->c ) ) < 3 ) {
        colorPrintf( UNDERLINED, RED, "\nОшибка. Введен неверный формат квадратного уравнения.");
        return false;
    }

    if ( isfinite( coefficients->a ) == 0 || isfinite( coefficients->b ) == 0 ||
         isfinite( coefficients->c ) == 0 ) {
        return false;
    }

    return true;
}
