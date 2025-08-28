 #include "flagSearch.h"
 #include "myAssert.h"

 #include <string.h>

 int flagSearch( int argc, char** argv, const char* flag) {

    myAssert( flag != NULL, 0 );
    myAssert ( argv != NULL, 0 );

    for( int indexArgv = 0; indexArgv< argc; indexArgv++ ){

        myAssert( argv[ indexArgv ] != NULL, 0);

        if ( strcmp( argv[ indexArgv ], flag) == 0 ) {

            return indexArgv;
        }
    }

    return 0;

 }

