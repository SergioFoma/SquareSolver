#include <TXLib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define MAXSIZE 100

char myStack[ MAXSIZE ]; // Стек
int Size = 0; // Размера стека

void push(char el);
char pop();
int getint( char number[], int k);

int main( void ) {

    printf("Правило ввода: Если хотите возвести в степень, введите символ '^'\n\nЕсли хотите умножить число на неизвестную  переменную, введите число с учетом знака, а затем переменнную без пробелов\n\n");
    printf("Пример: 5 умножить на x эквивалетно записи 5x, x возвести в степень 2 эквивалентно записи 2^x\n\n");

    char Array[ MAXSIZE ];

    int C, i = 0, j; // индексы i и j для массива и переменная c для считывания

    while ( ( C = getchar() ) != '\n' && i < MAXSIZE) Array[i++] = C;

    int a = 1,b = 1,c  = 1; // коэффициенты квадратного уравнения ( по умолчанию 1)

    int sign = 1; // Знак коэффициентов

    for ( j = 0; j < i; j++) {

        char number[ MAXSIZE ];
        int k = 0;

        if ( isdigit( Array[j] ) && Array[ j - 1] != '^' ) { // Добавляем все цифры кроме степени икса
            push( Array[j] );
        }


        if ( Array[j-1] != 'x' && (Array[j] == '+' || Array[j] == '-' || ( j == i - 1 && isdigit(Array[j]) ) ) ) { // Подсчет коэффициента c

            while( Size > 0 ) number[ k++ ] = pop();
            if( k != 0 ) c = getint( number, k ) * sign;
            else c *= sign;

        }

        else if ( Array[j] == 'x' && Array[ j + 1 ] == '^') { // Подсчет коэффициента a

            while( Size > 0 ) number[ k++ ] = pop();
            if( k != 0 ) a = getint( number, k ) * sign;
            else a *= sign;
        }

        else if( Array[j] == 'x') { // Подсчет коэффициента b

            while( Size > 0 ) number[ k++ ] = pop();
            if( k != 0 ) b = getint( number, k ) * sign;
            else b *= sign;
        }

        if ( Array[j] == '-') sign = -1;
                                              // меняем знак, если его нашли
        else if ( Array[j] == '+') sign = 1;
    }

    int D = b * b - 4 * a * c;

    if ( D < 0) {

        printf("Действительных корней нет");

    }

    else if ( a == 0) printf("Уравнение не квадратное. Старший коэффициент равен нулю");

    else {

        double x1 = ( - b - sqrt( D ) ) / (2 * a);

        double x2 = ( - b + sqrt( D ) ) / (2 * a);

        printf("a: %d b: %d c: %d\n", a, b, c);

        if ( x1 == x2) printf("Корни совпадают и равны %.1f", x1);

        else printf("Меньший корень уравнения: %.1f\nБольший корень уравнения: %.1f", x1, x2);
    }
    return 0;
}

void push( char el) {
    myStack[ Size++] = el;
}
char pop() {
    return myStack[ --Size ];
}
int getint( char number[], int k ) {

    int i;
    for ( i = 0; i < ( k / 2); i++) { // цикл для reverse
        int tmp = number[i];
        number[i] = number[ k - 1 - i];
        number[ k - 1 - i] = tmp;
    }

    int res = 0;
    for ( i = 0; i < k; i++) res = 10 * res + ( number[i] - '0'); // перевод строки в числовый формат
    return res;
}
