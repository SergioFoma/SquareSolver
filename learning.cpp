#include <TXLib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define MAXSIZE 100

char myStack[ MAXSIZE ]; // Стек
int Size = 0; // Размера стека

void push(char el);

char pop();

int getint( char number[], int sizeNumber);

int getNumber( char number[], int sizeNumber, int parametr, int sign);

int main( void ) {

    printf("Правило ввода: Если хотите возвести в степень, введите символ '^'\n\nЕсли хотите умножить число на неизвестную  переменную, введите число с учетом знака, а затем переменнную без пробелов\n\n");
    printf("Пример: 5 умножить на x эквивалетно записи 5x, x возвести в степень 2 эквивалентно записи 2^x\n\n");

    char Array[ MAXSIZE ];

    int element = 0, sizeArray = 0, indexArray = 0; // индексы i и j для массива и переменная c для считывания

    while ( ( element = getchar() ) != '\n' && sizeArray < MAXSIZE) {

        Array[ sizeArray++ ] = element;
    }

    int a = 1, b = 1, c  = 1; // коэффициенты квадратного уравнения ( по умолчанию 1)

    int sign = 1; // Знак коэффициентов

    for (; indexArray < sizeArray; indexArray++) {

        char number[ MAXSIZE ];
        int sizeNumber = 0;

        if ( isdigit( Array[ indexArray ] ) && Array[ indexArray - 1] != '^' ) { // Добавляем все цифры кроме степени икса

            push( Array[ indexArray ] );
        }


        if ( Array[ indexArray-1 ] != 'x' && (Array[ indexArray ] == '+' || Array[ indexArray ] == '-' || ( indexArray == sizeArray - 1 && isdigit(Array[ indexArray ]) ) ) ) { // Подсчет коэффициента c

            c = getNumber( number, sizeNumber, c, sign);

        }

        else if ( Array[ indexArray ] == 'x' && Array[ indexArray + 1 ] == '^') { // Подсчет коэффициента a

            a = getNumber( number, sizeNumber, a, sign);
        }

        else if( Array[ indexArray ] == 'x') { // Подсчет коэффициента b

            b = getNumber( number, sizeNumber, b, sign );
        }

        if ( Array[ indexArray ] == '-') {
            sign = -1;
        }                                       // меняем знак, если его нашли

        else if ( Array[ indexArray ] == '+') {
            sign = 1;
        }
    }

    int D = b * b - 4 * a * c;

    if ( D < 0) {

        printf("Действительных корней нет");

    }

    else if ( a == 0) {

        printf("Уравнение не квадратное. Старший коэффициент равен нулю");
    }

    else {

        double x1 = ( - b - sqrt( D ) ) / (2 * a);

        double x2 = ( - b + sqrt( D ) ) / (2 * a);

        printf("a: %d b: %d c: %d\n", a, b, c);

        if ( x1 == x2) {
            printf("Корни совпадают и равны %.1f", x1);
        }

        else {
            printf("Меньший корень уравнения: %.1f\nБольший корень уравнения: %.1f", x1, x2);
        }
    }
    return 0;
}

void push( char el) {
    myStack[ Size++] = el;
}
char pop() {
    return myStack[ --Size ];
}
int getint( char number[], int sizeNumber ) {

    int indexNumber = 0;
    for ( ; indexNumber < ( sizeNumber / 2); indexNumber++) { // цикл для reverse
        int tmp = number[ indexNumber ];
        number[ indexNumber ] = number[ sizeNumber - 1 - indexNumber];
        number[ sizeNumber - 1 - indexNumber] = tmp;
    }

    int result = 0;
    for ( indexNumber = 0; indexNumber < sizeNumber; indexNumber++) {
        
        result = 10 * result + ( number[ indexNumber ] - '0'); // перевод строки в числовый формат
    }
    return result;

}
int getNumber( char number[], int sizeNumber, int parametr, int sign) {

    while( Size > 0 ) {
        number[ sizeNumber++ ] = pop();
    }
    if( sizeNumber != 0 ) return ( getint( number, sizeNumber ) * sign );
    else return ( parametr *= sign );

}

