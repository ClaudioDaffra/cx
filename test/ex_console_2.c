
#include "../lib/console.h"

/*
    cl  test/ex_console_2.c lib/console.c lib\stdio.c   /Fex.exe
    gcc test\ex_console_2.c lib\console.c lib\stdio.c   -o x.exe
    gcc test/ex_console_2.c lib/console.c lib/stdio.c   -o x
    
*/

int main()
{
    consoleStart();

    consoleClear();

    printf ( "\n STREAM [%d]\n",(int)std_stream );

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

    consoleSetXY(1,1) ;

    printf ( "\n\nEND" );

    int x,y;
    consoleGetXY(&x,&y);
    printf ( "\n XY [%d,%d]\n",x,y );  
    
    return 0;
}
