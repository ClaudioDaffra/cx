
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

    // consoleXY, wconsoleXY


    int consoleGetXY(int *y, int *x) 
    {
        char buf[30]={0};
        int ret, i, pow;
        char ch;

        *y = 0; *x = 0;

        struct termios term, restore;

        tcgetattr(0, &term);
        tcgetattr(0, &restore);
        term.c_lflag &= ~(ICANON|ECHO);
        tcsetattr(0, TCSANOW, &term);

        write(1, "\033[6n", 4);

        for( i = 0, ch = 0; ch != 'R'; i++ )
        {
                ret = read(0, &ch, 1);
                if ( !ret ) 
                {
                    tcsetattr(0, TCSANOW, &restore);
                    fprintf(stderr, "getpos: error reading response!\n");
                    return 1;
                }
                buf[i] = ch;
                //printf("buf[%d]: \t%c \t%d\n", i, ch, ch);
        }

        if (i < 2) 
        {
            tcsetattr(0, TCSANOW, &restore);
            printf("i < 2\n");
            return(1);
        }

        for( i -= 2, pow = 1; buf[i] != ';'; i--, pow *= 10)
        *x = *x + ( buf[i] - '0' ) * pow;

        for( i-- , pow = 1; buf[i] != '['; i--, pow *= 10)
        *y = *y + ( buf[i] - '0' ) * pow;

        tcsetattr(0, TCSANOW, &restore);
        return 0;
    }

     
#endif



/**/

