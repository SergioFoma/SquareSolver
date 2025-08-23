 #include "goTest.h"
 #include "test.h"

 #include <string.h>
 int goTest( int argc, char** argv ) {

    int flag = 0;

    for( int i = 0; i < argc; i++ ){

        if ( strcmp( argv[ i ], "--Test" ) == 0 ) {

            flag = 1;
            break;
        }
    }

    if ( flag ) {

        test();
        return 1;
    }
    else {

        return 0;
    }

 }
