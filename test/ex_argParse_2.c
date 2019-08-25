
#include "../lib/argParse.h"
#include "../lib/file.h"
#include "../lib/tools.h"
#include "global.h"
#include "error.h"
#include "lexer.h"
#include "token.h"
#include <wchar.h>
#include <stdio.h>

int main ( int argc , const char** argv ) 
{
    //*********
    //  ARGPARSE
    //*********
    
    argParseUsage ( usages ,
        "c12 [options] [[--] args]",
        "c12 [options]"
    ) ;

    argParseOption ( options ) 
    {
        OPT_HELP(),
        OPT_GROUP   ("Basic options"),
            OPT_STRING  ('i', "input"   , &g.fileInput  , "file input to read"      , NULL, 0, 0 ),
            OPT_STRING  ('o', "output"  , &g.fileOutput , "file output to write"    , NULL, 0, 0 ),
            OPT_STRING  ('d', "debug"   , &g.fileDebug  , "file debug"              , NULL, 0, 0 ),
            OPT_BOOLEAN ('l', "lexer"   , &g.fLexer     , "show lexer information"  , NULL, 0, 0 ),
        OPT_END()
    };    

    argparse_t argparse;

    argParseInit( &argparse, options, usages, 0);
    
    argParseDescribe ( &argparse, 
        "\nC intepreter.", 
        "\nby Claudio Daffra (2019)."
    );

    argParseStart ( &argparse ) ;

    // redireziona l'output del debug su un file
    
    if ( g.fileDebug != NULL )
    {
        // reopen stderr
        freopen( g.fileDebug , "w", stderr ) ;
    }

    //*********
    //  SCAN
    //*********
  
    console.setUTF8();

    lexer.include ( g.fileInput ) ;
    
    for(;;) // parser
    {
        lexer.getToken() ;
        if ( token.sym == sym_end ) break ;
        
            // ########### DEMO #include parser
            if ( wcscmp(token.text , L"X" )==0 )
            {
               lexer.include( "test\\a.txt" ) ;
               continue ;
            }
            if ( wcscmp(token.text , L"Y" )==0 )
            {
               lexer.include( "test\\b.txt" ) ;
               continue ;
            }            
            // ########### DEMO #include

            
        lexer.printToken();
       
    } ;
    
    lexer.end();
 
    //*********
    //  ERROR
    //*********

    err.printErrLog() ; 
    
    // C:\c12>bin\c12.exe -i "test\utf8.txt"
    
    //*********
    //  THE END
    //*********
    
    fwprintf ( stdout , L"\n\n§ thé ènd §\n\n"  ) ;
    
    return 0;
} 



/**/



