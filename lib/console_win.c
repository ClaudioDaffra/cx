
#include "console_win.h"
 
 
void consoleStart(void)
{
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;

    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes; 
    
    console.backGround  = 0;
    console.foreGround  = 7;
    console.bold        = 0; 
    console.reverse     = 0;
    console.underline   = 0; 
}

WORD consoleStop(void) 
{    
    SetConsoleTextAttribute(hConsole, saved_attributes);  
} 

void consoleSetTextAttr(void)
{
    int fg = console.foreGround ;
    int bg = console.backGround ;
    int rv = console.reverse==0?0:0x4000;   // reverse
    int us = console.reverse==0?0:0x8000;   // unsderscore
    int bl = 0 ;// bold ??
    
    SetConsoleTextAttribute(hConsole,  
        ((bg & 0x0F) << 4) + (fg & 0x0F) 
        | rv
        | us
    );
} 


/**/


