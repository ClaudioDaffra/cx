#ifndef cdCONSOLELIN
#define cdCONSOLELIN

    #ifdef __linux__
    #define _GNU_SOURCE 
    #endif

    #include <wchar.h>

    #if defined(__linux__)

        #include <stdio.h>
        #include <termios.h>
        #include <unistd.h>

        typedef enum consoleColor_e
        {
            BLACK       =   30,
            RED         =   31,
            GREEN       =   32,
            YELLOW      =   33,
            BLUE        =   34,
            BLU         =   34,
            MAGENTA     =   35,
            PURPLE      =   35,
            CYAN        =   36,
            LIGHTGRAY   =   37,
            DARKGRAY    =   90,
            LIGHTRED    =   91,
            LIGHTGREEN  =   92,
            LIGHTYELLOW =   93,
            LIGHTBLUE   =   94,
            LIGHTMAGENTA=   95,
            PINK        =   95,
            LIGHTCYAN   =   96,
            WHITE       =   97
        } consoleColor_t ;

        typedef struct console_s
        {
            consoleColor_t backGround;
            consoleColor_t foreGround;
            int bold;
            int reverse;
            int underline;
        } console_t ;
         
        console_t console;  
        
        void consoleStop(void) ;
        void wconsoleStop(void) ;   
        
        void     consoleStart(void) ;
        #define  wconsoleStart consoleStart  
        
        void consoleSetTextAttr(void) ;
        void wconsoleSetTextAttr(void) ;
         
        #define  consoleSetXY(x,y)    printf( "\e[%d;%df",y,x);
        #define wconsoleSetXY(x,y)   wprintf(L"\e[%d;%df",y,x);
        
        #define  consoleClear(...)    printf ( "\033c");/*__VA_ARGS__*/
        #define wconsoleClear(...)   wprintf (L"\033c");/*__VA_ARGS__*/

        int consoleGetXY(int *y, int *x) ;
        #define wconsoleGetXY   consoleGetXY

    #endif

#endif



/**/


