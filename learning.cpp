#include <TXLib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

void push(char el, char* myStack, int* stackSize);

char pop( char* myStack, int* stackSize);

int getint( char number[], int sizeNumber);

int getNumber( char number[], int sizeNumber, int parametr, int numberSign, char* myStack, int* stackSize);

int correctInput( char* inputString, int* inputSize);

int main( void ) {

    printf("Правило ввода: Если хотите возвести в степень, введите символ '^'\n\n"
    "Если хотите умножить число на неизвестную  переменную, введите число с учетом знака, а затем переменнную без пробелов\n\n"
    "Пример: 5 умножить на x эквивалетно записи 5x, x возвести в степень 2 эквивалентно записи 2^x\n\n");

    const int maxArraySize = 100; // Максимальная длина строки( константа )

    char myStack[ maxArraySize ]; // Стек
    int stackSize = 0; // Размера стека

    char inputString[ maxArraySize ];

    int inputRead = 0, inputSize = 0, inputStringIndex = 0; // переменная для сяитывания, размер строки ввода и далее индекс для этой строки

    while ( ( inputRead = getchar() ) != '\n' && inputSize < maxArraySize) {

        inputString[ inputSize++ ] = inputRead;

        if ( inputSize == maxArraySize) {
            printf("Введенная строка имеет максимально возможною длинну. Больше символов ввести нельзя\n\n");
        }
    }

    if ( !correctInput( inputString, &inputSize) ) {
        return 0;
    }

    int a = 1, b = 1, c  = 1; // коэффициенты квадратного уравнения ( по умолчанию 1)

    int numberSign = 1; // Знак коэффициентов

    for (; inputStringIndex < inputSize; inputStringIndex++) {

        char number[ maxArraySize ];
        int sizeNumber = 0;

        if ( isdigit( inputString[ inputStringIndex ] ) && inputString[ inputStringIndex - 1] != '^' ) { // Добавляем все цифры кроме степени икса

            push( inputString[ inputStringIndex ], myStack, &stackSize );
        }


        if ( inputString[ inputStringIndex-1 ] != 'x' && (inputString[ inputStringIndex ] == '+' || inputString[ inputStringIndex ] == '-' || ( inputStringIndex == inputSize - 1 && isdigit(inputString[ inputStringIndex ]) ) ) ) { // Подсчет коэффициента c

            c = getNumber( number, sizeNumber, c, numberSign, myStack, &stackSize);

        }

        else if ( inputString[ inputStringIndex ] == 'x' && inputString[ inputStringIndex + 1 ] == '^') { // Подсчет коэффициента a

            a = getNumber( number, sizeNumber, a, numberSign, myStack, &stackSize);
        }

        else if( inputString[ inputStringIndex ] == 'x') { // Подсчет коэффициента b

            b = getNumber( number, sizeNumber, b, numberSign, myStack, &stackSize);
        }

        if ( inputString[ inputStringIndex] == '-') {

            numberSign = -1;
        }                                       // меняем знак, если его нашли

        else if ( inputString[ inputStringIndex ] == '+') {

            numberSign = 1;
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

void push( char el, char* myStack, int* stackSize) {
    *( myStack + (*stackSize) ) = el;
    (*stackSize)++;
}
char pop( char* myStack, int* stackSize) {
    (*stackSize)--;
    return *( myStack + (*stackSize) );
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
int getNumber( char number[], int sizeNumber, int parametr, int numberSign, char* myStack, int* stackSize) {

    while( *stackSize > 0 ) {

        number[ sizeNumber++ ] = pop( myStack, stackSize );
    }

    if( sizeNumber != 0 ) return ( getint( number, sizeNumber ) * numberSign );
    else return ( parametr *= numberSign );
}
int correctInput( char* inputString, int*inputSize) {

    if ( *inputSize == 0 ) {

        printf("\nОшибка. Введена пустая строка.\n");
        return 0;
    }

    int inputIndex = 0, countX = 0, countXX = 0;
    for ( ; inputIndex < *inputSize; inputIndex++) {

        if ( *(inputString + inputIndex) == 'x') {

            ++countX;
        }

        else if( *(inputString + inputIndex) == '^') {

            ++countXX;
        }

        if ( !( isdigit( *(inputString + inputIndex) ) ) && ( *(inputString + inputIndex) != 'x' ) && ( *(inputString + inputIndex) != '+') && (*(inputString + inputIndex) != '-') && (*(inputString + inputIndex) != '^')) {

            printf("\nОшибка. Введен неверный символ: %c.\n", *(inputString + inputIndex) );
            return 0;
        }

        else if ( *( inputString + inputIndex) == 'x' && isdigit( *(inputString + inputIndex + 1) ) ) {

            printf("\nОшибка. Введен неверный формат квадратного уравнения. Коэффициенты должны быть до x.\n");
            return 0;
        }

        else if( ( *( inputString + inputIndex ) == '+' || *( inputString + inputIndex ) == '-') && ( *( inputString + inputIndex + 1 ) == '+' || *( inputString + inputIndex + 1) == '-' ) ) {

            printf("\nОшибка. Введен лишний символ %c.\n", *( inputString + inputIndex + 1) );
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

    }
    return 1;
}
