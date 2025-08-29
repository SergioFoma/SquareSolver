#include <myAssert.h>
#include <stdio.h>
#include <assert.h>
#include "paint.h"

void myAssert_( const char* func, const char* file, int line, const char *expr ) {
    
    assert( func != NULL );
    assert( file != NULL );
    assert( expr != NULL );

    colorPrintf( "RED", "Ошибка. Передан нулевой указатель в функции %s , в файле %s , в строчке %d . Проверялось условие %s\n", 
                  func, file, line, expr);
}