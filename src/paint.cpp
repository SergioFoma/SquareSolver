#include "paint.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

const char* getColorLine( const char* color, const char* line, const char* cleanColor ) {
    size_t lineSize = sizeof( color ) + sizeof( line ) + sizeof( cleanColor );

    char* result = (char*)calloc( lineSize, sizeof( char ) );

    if ( result == NULL ) {
        colorPrintf("RED", "Ошибка. Память переполенена" );
        return "0";
    }
    char* addColor = strcpy( result, color );
    char* addLine = strcat( addColor, line );

    free( result );
    
    return (char*)strcat(addLine, cleanColor );
}

void colorPrintf( const char* color, const char* line ... ) {

    va_list args; // объявляем указатель
    va_start( args, line ); // связываем args с первым необязательным параметром. va_list как указатель

    if ( strcmp( color, "GREEN" ) == 0 ) {
        const char* colorLine = getColorLine( colorInGreen, line, colorReset );
        if( strcmp(colorLine, "0") != 0 ) {
            vprintf( colorLine , args );
        }
    }
    else if ( strcmp(color, "RED" ) == 0 ) {
        const char* colorLine = getColorLine( colorInRed, line, colorReset );
        if ( strcmp( colorLine, "0" ) != 0 ) {
            vprintf( colorLine, args );
        }
    }
    else if( strcmp( color, "BLUE" ) == 0 ) {
        const char* colorLine = getColorLine( colorInBlue, line, colorReset );
        if ( strcmp(colorLine, "0") != 0 ) {
            vprintf( colorLine, args );
        }
    }
    else if( strcmp( color, "PURPLE" ) == 0) {
        const char* colorLine = getColorLine( colorInPurple, line, colorReset );
        if ( strcmp( colorLine, "0" ) != 0 ) {
            vprintf( colorLine, args );
        }
    }
    else if( strcmp( color, "YELLOW") == 0 ) {
        const char* colorLine = getColorLine( colorInYellow, line, colorReset );
        if ( strcmp(colorLine, "0" ) != 0 ) {
            vprintf( colorLine, args );
        }
    }

    va_end( args );
}
