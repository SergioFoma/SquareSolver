#include <TXLib.h>
#include "solver.h"
#include "test.h"
#include "flagSearch.h"
#include "myAssert.h"

#include <stdio.h>
#include <math.h>


void printResult( Coefficients coefficients, SolveResult answer );

int inputCoefficient( Coefficients* coefficients );

int main( int argc, char** argv ) {

    if ( checkOnFlag( argc, argv, "--Test") ) {
        return 0;
    }
    else if( checkOnFlag( argc, argv, "--file-test" ) ) {
        return 0;
    }

    printf("\033[35;40mМЯУ\n\n\033[0m"
           "\033[33;40mВведите коэффициенты квадратного уравнения( a, b и c соответсвенно)"
           " на следующей строке через пробел:\n\n\033[0m");

    Coefficients coefficients = {0, 0, 0};
    SolveResult answer = { NAN, NAN, zeroRoot};

    if (!inputCoefficient( &coefficients) ) {
        return 0;
    }

    solveEquation( coefficients, &answer );
    printResult( coefficients, answer );

    printf("\n\nCOMMIT GITHUB\n");

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

    printf("\n\033[34;40ma: %lg b: %lg c: %lg\n\033[0m", coefficients.a, coefficients.b, coefficients.c );

    switch ( answer.countRoots ) {
        case zeroRoot:
            printf("\n\033[32;40mНет корней.\033[0m");
            break;

        case twoRoot:
            printf("\n\033[32;40mУравнение квадратное.\nМеньший корень: %lg\nБольший корень: %lg\033[0m",
            answer.x1, answer.x2 );
            break;

        case oneRoot:
            printf("\n\033[32;40mУравнение линейное.\nКорень уравнения: %lg\033[0m", answer.x1 );
            break;

        case alotRoot:
            printf("\n\033[32;40mУравнение имеет бесконечное количество корней.\033[0m");
            break;

        case twoSameRoot:
            printf("\n\033[32;40mУравнение квадратное.\nИмеет единственный корень: %lg\033[0m", answer.x1 );
            break;

        default:
            printf("\n\033[31;40mОшибка. Не определено количество корней.\033[0m");
            break;
    }
}

//-----------------------------------------------------------------------------------------------------
//!
//! @param [in] *coefficients   *coefficients - указатель на структуру, получающую коэффициенты.
//!
//! @return 1 при успешном считывании, 0 при безуспешном.
//!
//! @note Считывает коэффициенты с ввода пользователя в coefficients.
//!
//-----------------------------------------------------------------------------------------------------
int inputCoefficient( Coefficients* coefficients) {

    myAssert( coefficients != NULL, 0 )

    if ( scanf("%lg %lg %lg", &( coefficients->a ), &( coefficients->b ), &( coefficients->c ) ) < 3 ) {
        printf("\n\033[31;40mОшибка. Введен неверный формат квадратного уравнения.\033[0m");
        return 0;
    }

    if ( isfinite( coefficients->a ) == 0 || isfinite( coefficients->b ) == 0 ||
         isfinite( coefficients->c ) == 0 ) {
        return 0;
    }

    return 1;
}
