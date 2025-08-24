 #include "flagSearch.h"

 #include <string.h>
 #include <assert.h>

 int flagSearch( int argc, char** argv, const char* flag) {

    assert( flag != NULL );
    assert ( argv != NULL );
    for ( int check = 0; check < argc; check++) {

        assert( argv[ check ] );
    }

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

