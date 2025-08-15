#include <TXLib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define MAXSIZE 100

char myStack[ MAXSIZE ]; // ����
int Size = 0; // ������� �����

void push(char el);
char pop();
int getint( char number[], int k);

int main( void ) {

    printf("������� �����: ���� ������ �������� � �������, ������� ������ '^'\n\n���� ������ �������� ����� �� �����������  ����������, ������� ����� � ������ �����, � ����� ����������� ��� ��������\n\n");
    printf("������: 5 �������� �� x ����������� ������ 5x, x �������� � ������� 2 ������������ ������ 2^x\n\n");

    char Array[ MAXSIZE ];

    int C, i = 0, j; // ������� i � j ��� ������� � ���������� c ��� ����������

    while ( ( C = getchar() ) != '\n' && i < MAXSIZE) Array[i++] = C;

    int a = 1,b = 1,c  = 1; // ������������ ����������� ��������� ( �� ��������� 1)

    int sign = 1; // ���� �������������

    for ( j = 0; j < i; j++) {

        char number[ MAXSIZE ];
        int k = 0;

        if ( isdigit( Array[j] ) && Array[ j - 1] != '^' ) { // ��������� ��� ����� ����� ������� ����
            push( Array[j] );
        }


        if ( Array[j-1] != 'x' && (Array[j] == '+' || Array[j] == '-' || ( j == i - 1 && isdigit(Array[j]) ) ) ) { // ������� ������������ c

            while( Size > 0 ) number[ k++ ] = pop();
            if( k != 0 ) c = getint( number, k ) * sign;
            else c *= sign;

        }

        else if ( Array[j] == 'x' && Array[ j + 1 ] == '^') { // ������� ������������ a

            while( Size > 0 ) number[ k++ ] = pop();
            if( k != 0 ) a = getint( number, k ) * sign;
            else a *= sign;
        }

        else if( Array[j] == 'x') { // ������� ������������ b

            while( Size > 0 ) number[ k++ ] = pop();
            if( k != 0 ) b = getint( number, k ) * sign;
            else b *= sign;
        }

        if ( Array[j] == '-') sign = -1;
                                              // ������ ����, ���� ��� �����
        else if ( Array[j] == '+') sign = 1;
    }

    int D = b * b - 4 * a * c;

    if ( D < 0) {

        printf("�������������� ������ ���");

    }

    else if ( a == 0) printf("��������� �� ����������. ������� ����������� ����� ����");

    else {

        double x1 = ( - b - sqrt( D ) ) / (2 * a);

        double x2 = ( - b + sqrt( D ) ) / (2 * a);

        printf("a: %d b: %d c: %d\n", a, b, c);

        if ( x1 == x2) printf("����� ��������� � ����� %.1f", x1);

        else printf("������� ������ ���������: %.1f\n������� ������ ���������: %.1f", x1, x2);
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
    for ( i = 0; i < ( k / 2); i++) { // ���� ��� reverse
        int tmp = number[i];
        number[i] = number[ k - 1 - i];
        number[ k - 1 - i] = tmp;
    }

    int res = 0;
    for ( i = 0; i < k; i++) res = 10 * res + ( number[i] - '0'); // ������� ������ � �������� ������
    return res;

}
