#undef myAssert // отмена объявления макроса.
#undef myAssert_ // TODO not needed

// TODO do not use _name
// use name_ instead

#ifdef NDEBUG // если не дебажная сборка
#define myAssert( arguments, value ) ( (void)0 )
#else
void myAssert_( const char* func, const char* file, int line, const char *expr );

#define myAssert( arguments, value )\
    if ( !arguments ) {\
        myAssert_(_func_, _FILE_, _LINE_, #arguments);\
        return value;\
    }\
    else {\
        ( void )0;\
    }

#endif

// # превращает в строку: printf("Value of %s is %d", #value, value);

/*

А еще параметр можно приклеить к чему-то еще, чтобы получился новый идентификатор.
Для этого между параметром и тем, с чем мы его склеиваем, нужно поставить '##':

#define PRINT_VALUE (number) printf("%d", value_##number);
int value_one = 10, value_two = 20;
PRINT_VALUE(one)  // -> 10
PRINT_VALUE(two)  // -> 20

*/
