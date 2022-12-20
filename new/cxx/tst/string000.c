
#include "../src/cxx.h"


// cls      &   cl  src\gc.c src\stdio.c src\string.c tst\string000.c    /Febin\x.exe     /utf-8 /WX

// clear    ;   gcc src/gc.c src/stdio.c src/string.c tst/string000.c    -o bin/x -Wall   -Wextra -pedantic

 


// *****    
// MAIN
// *****    

int main ( void )
{
    gcStart();
     
    stdio_t stdio ;
 
    stdioSetUTF8( &stdio );

    //

    fwprintf ( stdout , L" - WIDE\n");    

    stdioPutw ( &stdio , L"L - claudio 1\n" , "" );

    stdioPutw( &stdio ,L"L - claudio 2\n","" );
    
    fprintf ( stdout , "L - %ls" , L"claudio 3\n" ) ;

    stdioPutw ( &stdio , L"الْأَبْجَدِيَّة الْعَرَبِيَّة‎\n" );

    fwprintf ( stdout , L" - MBS\n");    
    
    stdioPuts ( &stdio , "s - 2claudio\n" );
    stdioPuts ( &stdio , "2الْأَبْجَدِيَّة الْعَرَبِيَّةn" );

    fwprintf ( stdout , L" - WIDE\n");    
    
    stdioPutw ( &stdio , L"tián 田 \"field\", jiāng 畕 \n" );
    stdioPutw ( &stdio , L"الْأَبْجَدِيَّة الْعَرَبِيَّ//ة‎ \n" );    

    stdioPutw ( &stdio , L"الْأَبْجَدِيَّة الْعَرَبِيَّة‎ \n" );
    stdioPutw ( &stdio , L"⟨б⟩, ⟨в⟩, ⟨г⟩, ⟨д⟩, ⟨ж⟩, ⟨з⟩, ⟨к⟩, ⟨л⟩, ⟨м⟩, ⟨н⟩, ⟨п⟩, ⟨р⟩, ⟨с⟩, ⟨т⟩, ⟨ф⟩, ⟨х⟩, ⟨ц⟩, ⟨ч⟩, ⟨ш⟩, ⟨щ⟩)‎ \n" );

    stdioPutw ( &stdio , L"א‎ב‎ג‎ד‎ה‎ו‎ז‎ח‎ט‎י‎ך‎\n" );    
    stdioPutw ( &stdio , L"èéò@ç°§£€\n" );    

    stdioPutw ( &stdio , L"èéò@ç°§£€\n" );

    // convert
    
    char* str3 = "claudio daffra";    
    
    fwprintf ( stdout, L"cnvPTRtoS8 %ls.\n", cnvPTRtoWS(str3) ) ;
        
    fwprintf ( stdout,  L"- DBL_MAX [%g]\n",DBL_MAX    );
    fwprintf ( stdout,  L"- cnvR64toWS(DBL_MAX) %ls \n", cnvR64toWS(DBL_MAX)        ) ; 

    fwprintf ( stdout, L"- FLT_MAX [%g]\n",FLT_MAX   );
    fwprintf ( stdout, L"- cnvR32toWS(FLT_MAX ) %ls \n", cnvR32toWS(FLT_MAX)    ) ; 
        
    fwprintf ( stdout, L"LLONG_MAX [%lld][",LLONG_MAX   );; 

    fwprintf ( stdout, L"LONG_MAX [%lld]\n",LONG_MAX   );

    fwprintf ( stdout, L"SHRT_MAX [%ld]\n",(long)SHRT_MAX    );

    fwprintf ( stdout, L"INT_MAX [%d]\n",INT_MAX   );
            

    char* x = cnvWStoS8(L"你好吗") ;
    stdioPuts ( &stdio ,x ) ; stdioPuts ( &stdio ,"\n" ) ;

    stdioPuts ( &stdio, "\nthat's al folks !\n");
    


 // ......................................................................

    wstringTypeDef(wchar_t,s1) ;

    wstring_s1_t s1 ;

    wstringAlloc(s1,8);
    
    wstringFormat( s1,L"%f\n" ,1.2 ) ;
    stdioPutw( &stdio , s1.data ) ;
    
    stdioPrintw ( &stdio , L"%f\n" ,1.21 ) ;
    
    stdioPrints ( &stdio ,  "%f\n" ,5.43 ) ;
    stdioPrints ( &stdio ,  "ok\n" ) ;
    
    fstdioPrintw ( &stdio, stdout, L"wide the end .\n" );
    fPrints ( stdout, "s8 the end 2.\n" ); 
    
 // ......................................................................

        //stdioPutw( &stdio , L"\n" ) ;
        
        char32_t wc[] = U"zß水🍌"; // or "z\u00df\u6c34\U0001f34c"
        
        size_t wc_sz = sizeof wc / sizeof *wc;
        
        wprintf( L"%zu UTF-32 code units: [ ", wc_sz);
        
        for (size_t n = 0; n < wc_sz; ++n) wprintf( L"%#x ", wc[n]);

/*
        stdioPutw( &stdio , L"\n{ \n" ) ;

        wchar_t *STR = cnvS32toWS( wc ) ;

        stdioPutw( &stdio , STR ) ;

        stdioPutw( &stdio , L" } \n" ) ;

        wprintf ( L"%ls....\n",wc ) ;
*/
 
 // ......................................................................


    stdioPutw( &stdio , L" ( string000.c ) \n" ) ;

 // ......................................................................

    gcStop();
    
    return 0 ;
}