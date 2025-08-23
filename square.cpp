#include <TXLib.h>
#include <stdio.h>
#include "solver.h"
#include "test.h"
#include "goTest.h"

#include <math.h>

void printResult( Coefficients coefficients, SolveResult answer );

int inputCoefficient( Coefficients* coefficients );

int main( int argc, char **argv ) {


    if ( goTest( argc, argv ) ) {

        return 0;
    }

    printf("������� ������������ ����������� ���������( a, b � c �������������)"
           " �� ��������� ������ ����� ������: \n\n");

    Coefficients coefficients = {0, 0, 0};

    if (!inputCoefficient( &coefficients) ) {

        return 0;
    }

    SolveResult answer = solveEquation( coefficients );
    printResult( coefficients, answer );

    return 0;
}

//-----------------------------------------------------------------------------------------------------
//!
//! @param [in] coefficients   coefficients - ���������, ���������� ������������ ����������� ���������.
//! @param [in] answer  answer - ���������, ����������� ����� ��������� � �� ����������.
//!
//! @note ������� �������������� ��������� � �������.
//!
//-----------------------------------------------------------------------------------------------------

void printResult( Coefficients coefficients, SolveResult answer ) {

    printf("\na: %lg b: %lg c: %lg\n", coefficients.a, coefficients.b, coefficients.c );

    switch ( answer.countRoots ) {

        case zeroRoot:

            printf("\n��� ������.");
            break;

        case twoRoot:

            printf("\n��������� ����������.\n������� ������: %lg\n������� ������: %lg",
            answer.x1, answer.x2 );
            break;

        case oneRoot:

            printf("\n��������� ��������.\n������ ���������: %lg", answer.x1 );
            break;

        case alotRoot:

            printf("\n��������� ����� ����������� ���������� ������.");
            break;

        case twoSameRoot:

            printf("\n��������� ����������.\n����� ������������ ������: %lg", answer.x1 );
            break;

        default:

            printf("\n������. �� ���������� ���������� ������.");
            break;
    }
}

int inputCoefficient( Coefficients* coefficients) {


    if ( scanf("%lg %lg %lg", &( (*coefficients).a ), &( (*coefficients).b ), &( (*coefficients).c ) ) < 3 ) {

        printf("\n������. ������ �������� ������ ����������� ���������.");
        return 0;
    }

    if ( !isfinite( (*coefficients).a ) || !isfinite( (*coefficients).b ) ||
         !isfinite( (*coefficients).c) ) {

            return 0;
    }


    return 1;

}
