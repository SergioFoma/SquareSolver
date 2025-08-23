 #include "flagSearch.h"

 #include <string.h>

 //!-------------------------------------------------------------------------
 //!
 //! @param [in] argc   argc - ���������� ������� � �������.
 //! @param [in] **argv    **argv - ������ �� ���������� �� ��������� ������.
 //!
 //! @note � �������� ������ ���� "--Test". ��������� ��������� ������.
 //!
 //!--------------------------------------------------------------------------
 int flagSearch( int argc, char** argv) {

    int flag = 0;

    if ( argc == 1) return 0;

    for( int i = 0; i < argc; i++ ){

        if ( strcmp( argv[ i ], "result.exe") != 0 ) {

            flag = 1;
            break;
        }
    }

    return flag;

 }
