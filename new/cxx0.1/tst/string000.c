
#include "../src/cxx.h"


// cls      &   cl  src\gc.c src\stdio.c src\string.c tst\string000.c    /Febin\x.exe     /utf-8 /WX

// clear    ;   gcc src/gc.c src/string.c tst/string000.c    -o bin/x -Wall   -Wextra -pedantic

 


// *****    
// MAIN
// *****    

int main ( void )
{
    gcStart();
     

    //

    fwprintf ( stdout , L" - WIDE\n");    

    fwprintf ( stdout , L"L - claudio 1\n" , "" );

    fwprintf( stdout ,  L"L - claudio 2\n","" );
    
    fprintf ( stdout ,  "L - %ls" , L"claudio 3\n" ) ;
/*
    fwprintf ( stdout , L"الْأَبْجَدِيَّة الْعَرَبِيَّة‎\n" );

    fwprintf ( stdout , L" - MBS\n");    
    
    fwprintf ( stdout , "s - 2claudio\n" );
    
    fwprintf ( stdout , "2الْأَبْجَدِيَّة الْعَرَبِيَّةn" );

    fwprintf ( stdout , L" - WIDE\n");    
    
    fwprintf ( stdout , L"tián 田 \"field\", jiāng 畕 \n" );
    
    fwprintf ( stdout , L"الْأَبْجَدِيَّة الْعَرَبِيَّ//ة‎ \n" );    

    fwprintf ( stdout , L"الْأَبْجَدِيَّة الْعَرَبِيَّة‎ \n" );
    
    fwprintf ( stdout , L"⟨б⟩, ⟨в⟩, ⟨г⟩, ⟨д⟩, ⟨ж⟩, ⟨з⟩, ⟨к⟩, ⟨л⟩, ⟨м⟩, ⟨н⟩, ⟨п⟩, ⟨р⟩, ⟨с⟩, ⟨т⟩, ⟨ф⟩, ⟨х⟩, ⟨ц⟩, ⟨ч⟩, ⟨ш⟩, ⟨щ⟩)‎ \n" );

    fwprintf ( stdout , L"א‎ב‎ג‎ד‎ה‎ו‎ז‎ח‎ט‎י‎ך‎\n" );    
    
    fwprintf ( stdout , L"èéò@ç°§£€\n" );    

    fwprintf ( stdout , L"èéò@ç°§£€\n" );

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
    
    fwprintf ( stdout ,x ) ; fwprintf ( stdout ,"\n" ) ;

    fwprintf ( stdout, "\nthat's al folks !\n");
    


 // ......................................................................

    wstringTypeDef(wchar_t,s1) ;

    wstring_s1_t s1 ;

    wstringAlloc(s1,8);
    
    wstringFormat( s1,L"%f\n" ,1.2 ) ;
    fwprintf( stdout , s1.data ) ;
    
    fwprintf ( stdout , L"%f\n" ,1.21 ) ;
    
    fwprintf ( stdout , "%f\n" ,5.43 ) ;
    fwprintf ( stdout , "ok\n" ) ;
    
    fwprintf ( stdout , L"wide the end .\n" );
    fwprintf ( stdout ,  "s8 the end 2.\n" ); 
    
 // ......................................................................

        //fwprintf( stdout , L"\n" ) ;
        
        char32_t wc[] = U"zß水🍌"; // or "z\u00df\u6c34\U0001f34c"
        
        size_t wc_sz = sizeof wc / sizeof *wc;
        
    fwprintf ( stdout , L"%zu UTF-32 code units: [ ", wc_sz);
        
        for (size_t n = 0; n < wc_sz; ++n) wprintf( L"%#x ", wc[n]);

/*
        fwprintf( stdout , L"\n{ \n" ) ;

        wchar_t *STR = cnvS32toWS( wc ) ;

        fwprintf( stdout , STR ) ;

        fwprintf( stdout , L" } \n" ) ;

        wprintf ( L"%ls....\n",wc ) ;
*/
 
 // ......................................................................


    fwprintf( stdout , L" ( string000.c ) \n" ) ;

 // ......................................................................

    gcStop();
    
    return 0 ;
}