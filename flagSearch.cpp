 #include "flagSearch.h"

 #include <string.h>

 int flagSearch( int argc, char** argv, const char* flag) {

    int resultSearch = 0;

    if ( argc == 1) return 0;

    for( int i = 0; i < argc; i++ ){

        if ( strcmp( argv[ i ], flag) == 0 ) {

            resultSearch = 1;
            break;
        }
    }

    return resultSearch;

 }

 