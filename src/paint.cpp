#include "paint.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

const char* getColorString( Colors color ) {
    switch (color) {
        case PURPLE:
            return colorInPurple;
            break;
        case YELLOW:
            return colorInYellow;
            break;
        case GREEN:
            return colorInGreen;
            break;
        case BLUE:
            return colorInBlue;
            break;
        case RED:
            return colorInRed;
            break;
        default:
            return "";
            break;
    }
}

const char* getStyleString( Styles style ) {
    switch( style ) {
        case BOLD:
            return makeBold;
            break;
        case FADED:
            return makeFaded;
            break;
        case ITALICS:
            return makeItalics;
            break;
        case UNDERLINED:
            return makeUnderlined;
            break;
        case BLINKING:
            return makeBlinking;
            break;
        case CROSSEDOUT:
            return makeCrossedOut;
            break;
        case NOMODE:
            return "\033[";
            break;
        default:
            return "\033[";
            break;
    }
}

void colorPrintf( Styles style, Colors color,  const char* line ... ) {

    va_list args; // объявляем указатель
    va_start( args, line ); // связываем args с первым необязательным параметром. va_list как указатель

    printf("%s", getStyleString( style ) );
    printf("%s", getColorString(color));
    vprintf(line, args);
    printf("%s", colorReset );

    va_end( args );
}
