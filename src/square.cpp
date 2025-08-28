#include <TXLib.h>
#include <stdio.h>
#include <math.h>

#include "solver.h"
#include "test.h"
#include "flagSearch.h"

void printResult( Coefficients coefficients, SolveResult answer );

int inputCoefficient( Coefficients* coefficients );

int main( int argc, char **argv ) {

    int indexFlag = 0;

    if ( ( indexFlag = flagSearch( argc, argv, "--Test" ) ) != 0  ) {
        testFromFunction();
        return 0;
    }
    else if ( ( indexFlag = flagSearch( argc, argv, "--file-test" ) ) != 0 ) {
        if ( indexFlag < argc - 1) {
            testFromFile( argv[ indexFlag + 1 ] );
        }
        else {
            printf( "Не введено имя тестирующего файла." );
        }
        return 0;
    }

    printf("МЯУ\n\n"
           "Введите коэффициенты квадратного уравнения( a, b и c соответсвенно)"
           " на следующей строке через пробел: \n\n");

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
//! @param [in] *coefficients   *coefficients - указатель на структуру, получающую коэффициенты.
//!
//! @result 1 при успешном считывании, 0 при безуспешном.
//!
//! @note Считывает коэффициенты с ввода пользователя в coefficients.
//!
//-----------------------------------------------------------------------------------------------------
int inputCoefficient( Coefficients* coefficients) {

    assert( coefficients != NULL );

    if ( scanf("%lg %lg %lg", &( coefficients->a ), &( coefficients->b ), &( coefficients->c ) ) < 3 ) {
        printf("\nОшибка. Введен неверный формат квадратного уравнения.");
        return 0;
    }

    if ( isfinite( coefficients->a ) == 0 || isfinite( coefficients->b ) == 0 ||
         isfinite( coefficients->c ) == 0 ) {
        return 0;
    }

    return 1;
}
