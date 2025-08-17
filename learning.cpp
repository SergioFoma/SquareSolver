#include <TXLib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

double getInt( char* number, int* sizeNumber, int numberSign, double parametr, int maxArraySize);

int correctInput( char* inputString, int inputIndex );

double getDiscriminant( double a, double b, double c );

void getRoots( double D, double  a, double b );

int main( ) {

    printf("Правило ввода: Если хотите возвести в степень, введите символ '^'\n\n"
    "Если хотите умножить число на неизвестную  переменную, введите число с учетом знака, а затем переменнную без пробелов\n\n"
    "Пример: 5 умножить на x эквивалетно записи 5x, x возвести в степень 2 эквивалентно записи x^2\n\n");

    const int maxArraySize = 100; // Максимальная длина строки( константа )

    char inputString[ maxArraySize ] = {};

    scanf("%s", inputString);

    int inputSize = strlen( inputString) ; // размер строки ввода

    if( inputSize == 0) {

        printf("\nВведена пустая строка.");
        return 0;
    }

    double a = 1, b = 1, c  = 1; // коэффициенты квадратного уравнения ( по умолчанию 1)

    int numberSign = 1; // Знак коэффициентов

    char number[ maxArraySize ] = {}; // массив для коэффициентов
    int sizeNumber = 0;

    for (int inputStringIndex = 0; inputStringIndex < inputSize; inputStringIndex++) {

        if( !correctInput( inputString, inputStringIndex ) ) { // Проверка на корректность ввода

            return 0;
        }


        if ( (isdigit( inputString[ inputStringIndex ] ) || inputString[ inputStringIndex] == '.')
        && inputString[ inputStringIndex - 1] != '^' ) { // Добавляем все цифры кроме степени икса

            number[ sizeNumber++ ] = inputString[ inputStringIndex ];
        }

        if ( inputString[ inputStringIndex-1 ] != 'x' && inputString[ inputStringIndex - 2] != '^' && (inputString[ inputStringIndex ] == '+'
        || inputString[ inputStringIndex ] == '-'
        || ( inputStringIndex == inputSize - 1 && isdigit(inputString[ inputStringIndex ]) ) ) ) { // Подсчет коэффициента c

            c = getInt( number, &sizeNumber, numberSign, c, maxArraySize );

        }

        else if ( inputString[ inputStringIndex ] == 'x' && inputString[ inputStringIndex + 1 ] == '^') { // Подсчет коэффициента a

            a = getInt( number, &sizeNumber, numberSign, a, maxArraySize );

        }

        else if( inputString[ inputStringIndex ] == 'x') { // Подсчет коэффициента b

            b = getInt( number, &sizeNumber, numberSign, b, maxArraySize );

        }

        if ( inputString[ inputStringIndex] == '-') {

            numberSign = -1;
        }                                       // меняем знак, если его нашли

        else if ( inputString[ inputStringIndex ] == '+') {

            numberSign = 1;
        }

    }

    double D = getDiscriminant( a, b, c );

    getRoots( D, a, b);

}

double getInt( char* number, int* sizeNumber, int numberSign, double parametr, int maxArraySize ) {

    if ( (*sizeNumber) == 0) {

        return parametr * numberSign;
    }

    double result = 0.0, power = 1.0;
    int indexNumber = 0;

    for( ; isdigit( *( number + indexNumber ) ) && indexNumber < (*sizeNumber); indexNumber++) {

        result = result * 10.0 + ( *(number + indexNumber) - '0' );

    }

    if ( *(number + indexNumber) == '.' ) {

        indexNumber++;

    }

    for( ; isdigit( *( number + indexNumber ) ) && indexNumber < (*sizeNumber); indexNumber++) {

        result = result * 10.0 + ( *(number + indexNumber) - '0' );
        power *= 10.0;
    }

    number[ maxArraySize ] ={};
    *sizeNumber = 0;

    return numberSign * result / power;

}

int correctInput( char* inputString, int inputIndex ) {

    int countX = 0, countXX = 0;

    if ( *(inputString + inputIndex) == 'x') {

        ++countX;
    }

    else if( *(inputString + inputIndex) == '^') {

        ++countXX;
    }

    if ( !( isdigit( *(inputString + inputIndex) ) ) && ( *(inputString + inputIndex) != 'x' )
    && ( *(inputString + inputIndex) != '+') && (*(inputString + inputIndex) != '-')
    && (*(inputString + inputIndex) != '^') && ( *(inputString + inputIndex) != '.' ) ) {

        printf("\nОшибка. Введен неверный символ: %c\n", *(inputString + inputIndex) );
        return 0;
    }

    else if ( *( inputString + inputIndex) == 'x' && isdigit( *(inputString + inputIndex + 1) ) ) {

        printf("\nОшибка. Введен неверный формат квадратного уравнения. Коэффициенты должны быть до x.\n");
        return 0;
    }

    else if( ( *( inputString + inputIndex ) == '+' || *( inputString + inputIndex ) == '-' || *(inputString + inputIndex) == '.')
    && ( *( inputString + inputIndex + 1 ) == '+' || *( inputString + inputIndex + 1) == '-' || *(inputString + inputIndex + 1) == '.' ) ) {

        printf("\nОшибка. Введен лишний символ %c\n", *( inputString + inputIndex + 1) );
        return 0;
    }

    else if ( countX > 2 || countXX > 1 ) {

        printf("\nОшибка. Введен неверный формат квадратного уравнения.\n");
        return 0;
    }

    else if( *(inputString + inputIndex) == '^' && *(inputString + inputIndex + 1) != '2') {

        printf("\nОшибка. Уравнение не второй степени.");
        return 0;
    }

    else if( *(inputString + inputIndex) == '^'&& *(inputString + inputIndex - 1) != 'x') {

        printf("\nОшибка. Введен неверный формат квадратного уравнения.\n");
        return 0;
    }

    return 1;
}

double getDiscriminant( double a, double b, double c ) {

    printf("a: %.1f b: %.1f c: %.1f\n", a, b, c);

    if ( a == 0 ) return -1.0;

    else if (  b * b - 4 * a * c  >= 0.0 ) return  b * b - 4 * a * c;

    else return -2.0;

}

void getRoots( double D, double a, double b) {

    if ( D == -1.0 ) printf("Уравнение не квадратное. Старший коэффициент равен нулю");

    else if ( D == -2.0 ) printf("Нет корней.");

    double x1 = ( - b - sqrt( D ) ) / ( 2 * a );

    double x2 = ( - b + sqrt( D ) ) / ( 2 * a );

    ( x1 == x2) ? printf("Корни совпадают и равны %.1f", x1) :
    printf("Меньший корень уравнения: %.1f\nБольший корень уравнения: %.1f\n", x1, x2);
}
