#include <myAssert.h>
#include <stdio.h>

void myAssert_( const char* func, const char* file, int line, const char *expr ) {

    printf("Ошибка. Передан нулевой указатель в функции %s , в файле %s , в строчке %d . Проверялось условие %s\n",
            func, file, line, expr);
}