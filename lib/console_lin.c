
#include "console.h"

#if defined(__linux__)

    void consoleStart(void)
    {
        console.backGround  = 39;
        console.foreGround  = 49;
        console.bold        = 0; 
        console.reverse     = 0;
        console.underline   = 0; 
    }

    void consoleSetTextAttr(void)
    {
        // ............................................ set color
        char buffer[128] ;
     
        sprintf ( buffer, "\033[%d;%dm"
            ,(int)(console.foreGround   )
            ,(int)(console.backGround+10)
        );

        printf ( "%s",buffer );
        // ............................................ set bold
        if ( console.bold == 1 )
             printf ( "\e[2m" );
        else
             printf ( "\e[22m" );

        // ............................................ set reverse
        if ( console.reverse == 1 )
             printf ( "\e[7m" );
        else
             printf ( "\e[27m" );

        // ............................................ set underline
        if ( console.underline == 1 )
             printf ( "\e[4m" );
        else
             printf ( "\e[24m" );
    }

    void consoleStop(void)
    {
        console.backGround  = 39;
        console.foreGround  = 49;
        console.bold        = 0; 
        console.reverse     = 0;
        console.underline   = 0; 
        consoleSetTextAttr();
        printf("\033[0m");
    }

    void wconsoleSetTextAttr(void)
    {
        // ............................................ set color
        wchar_t buffer[128] ;
     
        swprintf ( buffer, 128, L"\033[%d;%dm"
            ,(int)(console.foreGround   )
            ,(int)(console.backGround+10)
        );

        wprintf ( L"%ls",buffer );
        // ............................................ set bold
        if ( console.bold == 1 )
             wprintf ( L"\e[2m" );
        else
             wprintf ( L"\e[22m" );

        // ............................................ set reverse
        if ( console.reverse == 1 )
             wprintf ( L"\e[7m" );
        else
             wprintf ( L"\e[27m" );

        // ............................................ set underline
        if ( console.underline == 1 )
             wprintf ( L"\e[4m" );
        else
             wprintf ( L"\e[24m" );
    }

    void wconsoleStop(void)
    {
        console.backGround  = 39;
        console.foreGround  = 49;
        console.bold        = 0; 
        console.reverse     = 0;
        console.underline   = 0; 
        consoleSetTextAttr();
        wprintf(L"\033[0m");
    }
    
#endif



/**/

