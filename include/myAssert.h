#undef myAssert
#undef _myAssert

#ifdef NDEBUG // если не дебажная сборка
#define myAssert( arguments ) 1
#else
int _myAssert( const char* func, const char* file, int line, const char *expr );
#define myAssert( arguments ) ( ( arguments ) ? ( 1 ) : ( _myAssert( __func__, __FILE__, __LINE__, #arguments) ) )
#endif