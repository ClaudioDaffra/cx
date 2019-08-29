
#include "../lib/stdio.h"
#include "../lib/console.h"

/*
    cl  test/ex_console_3.c lib/console.c  lib\stdio.c  /Fex.exe
    gcc test\ex_console_3.c lib\console.c  lib\stdio.c  -o x.exe
    gcc test/ex_console_3.c lib/console.c  lib/stdio.c  -o x
*/

int main()
{
    consoleSetUTF8();
    
    wconsoleClear();
    
    wprintf ( L"\nstream %d\n",std_stream );
    
    //

    wconsoleStart();

    console.backGround  = RED;
    console.foreGround  = GREEN;
    console.bold        = 1; 

    wconsoleSetTextAttr();

        wprintf ( L"汉字" );    ;

    console.backGround  = BLACK;
    console.foreGround  = WHITE;
    console.reverse     =  1 ; 

    wconsoleSetTextAttr();
    
        wprintf ( L"ひらがな" );    ;

    console.backGround  = CYAN;
    console.foreGround  = PINK;
    console.underline   = 1; 
    
    wconsoleSetTextAttr(); 
    
        wprintf ( L"большой " );    ;
 
    wconsoleStop();

    wconsoleSetXY(1,1) ;
    
    wprintf ( L"\n\nènd" );

    int x,y;
    wconsoleGetXY(&x,&y);
    wprintf ( L"\n XY [%d,%d]\n",x,y );  
    
    return 0;
}
