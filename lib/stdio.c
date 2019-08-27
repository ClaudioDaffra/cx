

#include "stdio.h"
 

#include <wchar.h>
#include <stdlib.h>

#define MAX_FILE_PATH 255

#ifdef  __linux__
    #undef MAX_FILE_PATH
    #define MAX_FILE_PATH 4096
#endif

#define MAX_ATTR 15 

// .................................................................... stream

console_stream_t std_stream = console_stream_ansi; 

// .................................................................... setUTF8

#if defined(_WIN32) || defined(_WIN64) 

    void cdConsolesetUTF8(void)
    {
        const wchar_t*      _fontName=L"SimSun-ExtB";
        uint32_t            _fontWeight=FW_NORMAL;
        uint32_t            _fontSizeY=16;
        uint32_t            _fontSizeX=0;    

        // set font
        
        CONSOLE_FONT_INFOEX info ;
        info.cbSize       = sizeof(info);
        info.dwFontSize.Y = _fontSizeY; // 16
        info.dwFontSize.X = _fontSizeX; // 0    
        info.FontWeight   = _fontWeight;
        wcscpy(info.FaceName, _fontName);
        SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), false, &info);
        
        // set stream
        
         _wsetlocale(LC_ALL , L"it_IT.UTF-8" );  // set locale wide string
        _setmode(_fileno(stdout), _O_U8TEXT);    // set Locale for console
        _setmode(_fileno(stderr), _O_U8TEXT);    // set Locale for console    
        _setmode(_fileno(stdin ), _O_U8TEXT);    // set Locale for console      

        // set CHCP : 936 1252 > win7 : 65001
        
        int chcp=936;                
        SetConsoleCP( chcp ) ;             
        SetConsoleOutputCP( chcp ); 

        // questo per evitare errori di conversione delle stringhe esadecimali
        setlocale ( LC_NUMERIC , "C" ) ;
        std_stream = console_stream_wide ;    
    } 
 
#else
   
    void cdConsolesetUTF8(void) 
    {
        setlocale(LC_ALL, "");

        // questo per evitare errori di conversione delle stringhe esadecimali   
        setlocale ( LC_NUMERIC , "C" ) ;
        std_stream = console_stream_wide ;
    }

#endif



/**/


