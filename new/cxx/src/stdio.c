
#include "cxx.h"

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wpedantic"
#endif

// ....................................................................... stdioSetUTF8

void stdioSetUTF8( stdio_t *stdio )
{
#ifdef _MSC_VER	
	// default value
	
	const wchar_t   _fontName[]	=	L"SimSun-ExtB"	;
	const SHORT 	_fontWeight	=	FW_NORMAL		;
	const SHORT		_fontSizeY	=	16				;
	const SHORT		_fontSizeX	=	0				;    
	const int		chcp		=	936				; 

	// set font

	stdio->info.cbSize       = sizeof(stdio->info)	;
	stdio->info.dwFontSize.Y = _fontSizeY				; // 16
	stdio->info.dwFontSize.X = _fontSizeX				; // 0    
	stdio->info.FontWeight   = _fontWeight			;

	wcscpy_s( 	stdio->info.FaceName, _countof(_fontName) , _fontName ) ;
	
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), false, &stdio->info);
	
	// set stream
	
	 _wsetlocale(LC_ALL , L"it_IT.UTF-8" );  // set locale wide string
	_setmode(_fileno(stdout), _O_U8TEXT);    // set Locale for stdio
	_setmode(_fileno(stderr), _O_U8TEXT);    // set Locale for stdio    
	_setmode(_fileno(stdin ), _O_U8TEXT);    // set Locale for stdio      

	// set CHCP : 936 1252 > win7 : 65001
	
	stdio->chcp = chcp ; 
	SetConsoleCP( chcp ) ;             
	SetConsoleOutputCP( chcp ); 

	// questo per evitare errori di conversione delle stringhe esadecimali
	setlocale ( LC_NUMERIC , "C" ) ;
	
	stdio->stream_stdout 	= stdioStreamUTF8 ;
	stdio->stream_stdin 	= stdioStreamUTF8 ;
	stdio->stream_stderr 	= stdioStreamUTF8 ;
	
#else
	
	setlocale ( LC_ALL, "it_IT.UTF-8");
	setlocale ( LC_NUMERIC , "C"     ) ;

	stdio->stream_stdout 	= stdioStreamUTF8 ;
	stdio->stream_stdin 	= stdioStreamUTF8 ;
	stdio->stream_stderr 	= stdioStreamUTF8 ;
	
#endif
} 

// ....................................................................... stdioSetMBS

void stdioSetMBS( stdio_t *stdio )
{
#ifdef _MSC_VER
    //const wchar_t*   _fontName=L"SimSun-ExtB";
    const wchar_t   _fontName[]=L"SimSun-ExtB";
    SHORT           _fontWeight=FW_NORMAL;
    SHORT           _fontSizeY=16;
    SHORT           _fontSizeX=0;    

    // set font
    
	stdio->info.cbSize       = sizeof(stdio->info);
	stdio->info.dwFontSize.Y = _fontSizeY; // 16
	stdio->info.dwFontSize.X = _fontSizeX; // 0    
	stdio->info.FontWeight   = _fontWeight;

    wcscpy_s( 	stdio->info.FaceName, _countof(_fontName) , _fontName ) ;
    
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), false, &stdio->info);
    int chcp=65001;            
    SetConsoleCP( chcp ) ;             
    SetConsoleOutputCP( chcp ); 
    
    setlocale ( LC_ALL,"it_IT.utf8"	) ;
    setlocale ( LC_NUMERIC , "C" 	) ; 
	
	stdio->stream_stdin 	= stdioStreamMBS ;
	stdio->stream_stdout 	= stdioStreamMBS ;
	stdio->stream_stderr 	= stdioStreamMBS ;
    
#else

	setlocale ( LC_ALL, "it_IT.UTF-8") ;
	setlocale ( LC_NUMERIC , "C" 	 ) ;

	stdio->stream_stdin 	= stdioStreamMBS ;
	stdio->stream_stdout 	= stdioStreamMBS ;
	stdio->stream_stderr 	= stdioStreamMBS ;
    
#endif
}
/* 
// ....................................................................... stdioPutw

int stdioPutw( stdio_t* stdio, wchar_t* string )
{
 #ifdef _MSC_VER
	switch ( stdio->stream_stdout )
	{

		case	stdioStreamMBS	:
				fprintf ( stdout , "%s" , (char*)cnvWStoS8(string) ) ;
			break ;	
			
		case	stdioStreamUTF8	:
				fwprintf ( stdout , L"%ls" , string ) ;
			break ;	
			
		default:
			break;
	}
#else
	fwprintf ( stdout , L"%ls" , string ) ;	 
#endif
	return 1 ;
}
*/
// ....................................................................... fstdioPutw

int fstdioPutw( stdio_t* stdio, FILE* file,wchar_t* string )
{
 #ifdef _MSC_VER
	switch ( stdio->stream_stdout )
	{
		case	stdioStreamMBS	:
				fprintf ( file , "%s" , (char*)cnvWStoS8(string) ) ;
			break ;	
			
		case	stdioStreamUTF8	:
				fwprintf ( file , L"%ls" , string ) ;
			break ;	
			
		default:
			break;
	}
#else
	fwprintf ( file , L"%ls" , string ) ;	 
#endif
	return 1 ;
}
/*
// ....................................................................... stdioPuts

int stdioPuts( stdio_t* stdio, char* string )
{
 #ifdef _MSC_VER
	switch ( stdio->stream_stdout )
	{

		case	stdioStreamMBS	:
				fprintf ( stdout , "%s" , string ) ;
			break ;	
			
		case	stdioStreamUTF8	:
				fwprintf ( stdout , L"%ls" , (wchar_t*)cnvS8toWS(string) ) ;
			break ;	
			
		default:
			break;
	}
#else
	fwprintf( stdout , L"%s" , string ) ;
#endif
	return 1 ;
}
*/
// ....................................................................... fstdioPuts

int fstdioPuts( stdio_t* stdio, FILE* file,char* string )
{
 #ifdef _MSC_VER
	switch ( stdio->stream_stdout )
	{

		case	stdioStreamMBS	:
				fprintf ( file , "%s" , string ) ;
			break ;	
			
		case	stdioStreamUTF8	:
				fwprintf ( file , L"%ls" , (wchar_t*)cnvS8toWS(string) ) ;
			break ;	
			
		default:
			break;
	}
#else
	fwprintf( file , L"%s" , string ) ;
#endif
	return 1 ;
}
 
// .................................................................... open file wide stream

int cdFileWOpen( 
    FILE** pf,
    char* fileName, 
    const char* flag , 
    const char* ccs  
) 
{
    wchar_t buffer[128] ;
    buffer[0]=L'\0';

    wchar_t* _fileName  = cnvS8toWS ( fileName  ) ;
    wchar_t* _flag      = cnvS8toWS ( (char*)flag  ) ;
    wchar_t* _ccs       = cnvS8toWS ( (char*)ccs  ) ;

    if (_fileName==NULL) return 3 ;

    if ( wcslen(_flag)+wcslen(_ccs) > 14 )
    {
        return 2 ;
    }

    wcscat (buffer,_flag);
    wcscat (buffer,L",");
    wcscat (buffer,_ccs);   

#if defined(_WIN32) || defined(_WIN64)  

    wchar_t *tmpw=wcsdup(_fileName); // questo per evitare seg fault
    
    for (uint32_t i=0;i<wcslen(_fileName);i++ )
    {
       // printf ( "(%c)",fileName[i] ) ;
       if ( tmpw[i]==L'/' ) tmpw[i] = L'\\' ;
    }
    
    errno_t err=_wfopen_s( pf,tmpw  , buffer  );

    free(tmpw); 
    
    if ( err ) 
    {
        fwprintf(stdout,L"\n? Error Open File : [%ls] for [%ls].",_fileName,_flag);  
        return 1;
    }
    
#else
  
    char *tmp=strdup(fileName); // questo per evitare seg fault
    
    for (uint32_t i=0;i<strlen(fileName);i++ )
    {
       // printf ( "(%c)",fileName[i] ) ;
       if ( tmp[i]=='\\' ) tmp[i] = '/' ;
    }

    #ifdef __APPLE__
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wself-assign"
    // per evitare unused parameter in linux
    #endif

    _ccs        = _ccs      ;
    buffer[0]   = L'\0'     ;
    _fileName   = _fileName ;

    #ifdef __APPLE__
    #pragma GCC diagnostic pop
    #endif
 
    *pf = fopen ( tmp , flag ) ;
    if ( *pf==NULL )
    {
        fwprintf(stdout,L"\n? Error Open File : [%ls] for [%ls].",_fileName,_flag);
        return 0;
    }
    
    free(tmp); // bug fix seg fault
    
#endif

    return 1 ;
}

// .................................................................... gc local file open wide


FILE* gcLocalFileOpenW(gc_t *map , char* fileName , const char* flag , const char* ccs )
{
	FILE* pf = NULL ;

	cdFileWOpen ( &pf, fileName , flag , ccs ) ;
	
    hash_map_put(   map, (void*)pf , (void*)gcFCloseDtor, HM_FAST);
	
    HM_DEBUG_PRINTF ( "gcOpen pf==%p , dtor==%p \n",pf,gcFCloseDtor ) ;
    
    return pf ;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#pragma GCC diagnostic pop
#pragma GCC diagnostic pop
#endif


