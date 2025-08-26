 #include "flagSearch.h"

 #include <string.h>
 #include <assert.h>

 int flagSearch( int argc, char** argv, const char* flag) {

    assert( flag != NULL );
    assert ( argv != NULL );

    for( int indexArgv = 0; indexArgv< argc; indexArgv++ ){

        assert( argv[ indexArgv ] != NULL);

        if ( strcmp( argv[ indexArgv ], flag) == 0 ) {

            return indexArgv;
        }
    }

    return 0;

 }

