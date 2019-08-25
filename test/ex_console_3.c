
#include "../lib/console.h"

/*
    cl  test/ex_console_3.c lib/console.c /Fex.exe
    gcc test\ex_console_3.c lib\console.c -o x.exe
    gcc test/ex_console_3.c lib/console.c -o x
    
*/

int main()
{
    wconsoleStart();

    console.backGround  = RED;
    console.foreGround  = GREEN;
    console.bold        = 1; 

    wconsoleSetTextAttr();

        wprintf ( L"xxxx" );    ;

    console.backGround  = BLACK;
    console.foreGround  = WHITE;
    console.reverse     =  1 ; 

    wconsoleSetTextAttr();
    
        wprintf ( L"yyyy" );    ;

    console.backGround  = CYAN;
    console.foreGround  = PINK;
    console.underline   = 1; 
    
    wconsoleSetTextAttr(); 
    
        wprintf ( L"zzzz" );    ;
 
    wconsoleStop();

    wprintf ( L"END" );

    return 0;
}
