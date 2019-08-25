
#include "../lib/console.h"

/*
    cl  test/ex_console_2.c lib/console.c /Fex.exe
    gcc test\ex_console_2.c lib\console.c -o x.exe
    gcc test/ex_console_2.c lib/console.c -o x
    
*/

int main()
{
    consoleStart();

    console.backGround  = RED;
    console.foreGround  = GREEN;
    console.bold        = 1; 

    consoleSetTextAttr();

        printf ( "xxxx" );    ;

    console.backGround  = BLACK;
    console.foreGround  = WHITE;
    console.reverse     =  1 ; 

    consoleSetTextAttr();
    
        printf ( "yyyy" );    ;

    console.backGround  = CYAN;
    console.foreGround  = PINK;
    console.underline   = 1; 
    
    consoleSetTextAttr(); 
    
        printf ( "zzzz" );    ;
 
    consoleStop();

    printf ( "END" );

    return 0;
}
