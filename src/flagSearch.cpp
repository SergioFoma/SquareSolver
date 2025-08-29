 #include "flagSearch.h"
 #include "myAssert.h"
 #include "test.h"
 #include "paint.h"

 #include <string.h>

int flagSearch( int argc, char** argv, const char* flag ) {

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

int  checkOnFlag( int argc, char** argv ) {

    int indexOfFlag = 0;
    if ( ( indexOfFlag = flagSearch( argc, argv, "--Test" ) ) != 0 ) {
        testFromFunction();
        return 1;
    }
    else if ( ( indexOfFlag = flagSearch( argc, argv, "--file-test" ) ) != 0 ) {
        if( argc > 2 ) {
            testFromFile( argv[ indexOfFlag + 1] );
        }
        else {
            colorPrintf( UNDERLINED, RED, "Не указано имя тестирующего файла.");
        }
        return 1;
    }
    return 0;
 }