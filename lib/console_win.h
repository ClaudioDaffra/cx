#ifndef cdCONSOLEWIN
#define cdCONSOLEWIN

    #ifdef __linux__
    #define _GNU_SOURCE 
    #endif

    #include <windows.h>

    HANDLE hConsole         ;
    WORD saved_attributes   ;
     
    typedef enum consoleColor_e
    {
        BLACK       =   0x0000,
        RED         =   0x0004, 
        GREEN       =   0x0002,
        YELLOW      =   0x0006,
        BLUE        =   0x0001,
        BLU         =   0x0001,
        MAGENTA     =   0x0005,
        PURPLE      =   0x0005,
        CYAN        =   0x0003,
        LIGHTGRAY   =   0x0007,    
        DARKGRAY    =   0x0080,
        LIGHTRED    =   0x0084, 
        LIGHTGREEN  =   0x0082,
        LIGHTYELLOW =   0x0086,
        LIGHTBLUE   =   0x0081,
        LIGHTBLU    =   0x0081,
        LIGHTMAGENTA=   0x0085,
        PINK        =   0x0085,
        LIGHTCYAN   =   0x0083,
        WHITE       =   0x0087, 

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

    void consoleStart(void) ;
    #define wconsoleStart       consoleStart 
    
    WORD consoleStop(void) ;
    #define wconsoleStop        consoleStop
    
    void consoleSetTextAttr(void) ;
    #define wconsoleSetTextAttr consoleSetTextAttr

    void consoleXY(int x, int y) ;
    #define wconsoleXY          consoleXY
    
#endif



/**/


