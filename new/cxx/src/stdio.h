
#ifndef cdSTDIO
#define cdSTDIO
 
    #define stdioStreamUTF8    -1
    #define stdioStreamANSI     0
    #define stdioStreamMBS      1

    // questo per evitare warning comparazione ( signed wchar_t / unsigned wchar_t )
    #define _WEOF (wchar_t)WEOF

    // (not standard ) : error: use of undeclared identifier 'errno_t'
    typedef int errno_t;

    typedef struct stdio_s
    {
        #if defined(cdWINDOWS)    
            CONSOLE_FONT_INFOEX     info            ; 
        #else
            int                     info            ;
        #endif            
        int                         chcp            ;
        int                         stream_stdout   ;
        int                         stream_stdin    ;
        int                         stream_stderr   ;
    } stdio_t ;

    void     stdioSetUTF8    ( stdio_t *stdio )     ;
    void     stdioSetMBS     ( stdio_t *stdio )     ;
    
    //int     stdioPuts        ( stdio_t* stdio, char* string        ) ;
    //int     stdioPutw        ( stdio_t* stdio, wchar_t* string     ) ;

    int     fstdioPuts        ( stdio_t* stdio, FILE* file,char* string     ) ;
    int     fstdioPutw        ( stdio_t* stdio, FILE* file,wchar_t* string  ) ;

    // .................................................... file stdio print w/s

    #define fstdioPrintw(STDIO,FOUT,FORMAT,...)\
    do{\
    wchar_t* strTemp=NULL;\
    strTemp=wsFormat_( FORMAT , ##__VA_ARGS__ );\
    fstdioPutw( STDIO , FOUT,strTemp  ) ;\
    }while(0);
     
    #define fstdioPrints(STDIO,FOUT,FORMAT,...)\
    do{\
    char* strTemp=NULL;\
    strTemp=s8Format_( FORMAT , ##__VA_ARGS__ );\
    fstdioPuts( STDIO , FOUT,strTemp  ) ;\
    }while(0);

    // .................................................... stdio print w/s

    #define stdioPrintw(FOUT,FORMAT,...) fstdioPrintw(&stdio,stdout,FORMAT, ##__VA_ARGS__)
    #define stdioPrints(FOUT,FORMAT,...) fstdioPrints(&stdio,stdout,FORMAT, ##__VA_ARGS__)

    // .................................................... fprint w/s
/*
    #define fstdioPrintw(STDIO,FOUT,FORMAT,...) fstdioPrintw(STDIO,FOUT,FORMAT, ##__VA_ARGS__)
    #define fstdioPrints(STDIO,FOUT,FORMAT,...) fstdioPrints(STDIO,FOUT,FORMAT, ##__VA_ARGS__)
*/
    #define fPrintw(FOUT,FORMAT,...) fstdioPrintw(&stdio,FOUT,FORMAT, ##__VA_ARGS__)
    #define fPrints(FOUT,FORMAT,...) fstdioPrints(&stdio,FOUT,FORMAT, ##__VA_ARGS__)

    // .................................................... fprint w/s

    //#define stdioPutw(STDIO,FORMAT,...) fstdioPrintw(STDIO,stdout,FORMAT, ##__VA_ARGS__)
    #define stdioPuts(STDIO,FORMAT,...) fstdioPrints(STDIO,stdout,FORMAT, ##__VA_ARGS__)


#define stdioPutw(STDIO,FORMAT,...)\
    do{\
    wchar_t* strTemp=NULL;\
    strTemp=wsFormat_( FORMAT , ##__VA_ARGS__ );\
    fstdioPutw( STDIO , stdout ,strTemp  ) ;\
    }while(0);


/*    
    #define fPutw(STDIO,fout,FORMAT,...) fstdioPrintw(STDIO,fout,FORMAT, ##__VA_ARGS__)    
    #define fPuts(STDIO,fout,FORMAT,...) fstdioPrints(STDIO,fout,FORMAT, ##__VA_ARGS__)
*/

int         cdFileWOpen       ( FILE** pf, char* fileName, const char* flag , const char* ccs ) ;
#define     stdFileWOpen        cdFileWOpen

    /**/

FILE*         gcLocalFileOpenW    (gc_t *map , char* fileName , const char* flag , const char* ccs ) ;
#define     gcFileOpenW(FN,FG,CCS)         gcLocalFileOpenW(gc,FN,FG,CCS)


    
#endif



/**/

