 #include "flagSearch.h"
 #include "myAssert.h"
 #include "test.h"

 #include <string.h>

 int flagSearch( int argc, char** argv, const char* flag) {

    myAssert( flag != NULL, 0 )
    myAssert ( argv != NULL, 0 )

    for( int indexArgv = 0; indexArgv< argc; indexArgv++ ){

        myAssert( argv[ indexArgv ] != NULL, 0);

        if ( strcmp( argv[ indexArgv ], flag) == 0 ) {
            return indexArgv;
        }
    }
    return 0;
 }

  int checkOnFlag( int argc, char** argv, const char* flag ) {
    
    int indexFlag = 0;

    if ( ( indexFlag = flagSearch( argc, argv, flag ) ) != 0) {
        
        if ( strcmp( flag, "--Test" ) == 0 ) {
            testFromFunction();
            return 1;
        }
        else if ( strcmp( flag, "--file-test") == 0 ) {
            if ( indexFlag < argc - 1) {
                testFromFile( argv[ indexFlag + 1 ] );
            }
            else {
                printf( "RED", "Не введено имя тестирующего файла." );
            }
            return 1;
        }
    }

    return 0;
 }

