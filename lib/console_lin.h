#ifndef cdCONSOLELIN
#define cdCONSOLELIN

    #ifdef __linux__
    #define _GNU_SOURCE 
    #endif

    #include <wchar.h>

    #if defined(__linux__)

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
         
        #define  consoleXY(x,y)    printf( "\e[%d;%df",y,x);
        #define wconsoleXY(x,y)   wprintf(L"\e[%d;%df",y,x);
        
    #endif

#endif



/**/


