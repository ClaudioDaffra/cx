#include "cxx.h"


// ....................................................................... stdioSetUTF8

void stdioSetUTF8( stdio_t *stdio )
{
#ifdef _MSC_VER

    // default value
    
    const wchar_t   _fontName[] =    L"SimSun-ExtB"     ;
    const SHORT     _fontWeight =    FW_NORMAL          ;
    const SHORT     _fontSizeY  =    16                 ;
    const SHORT     _fontSizeX  =    0                  ;
    //const int        chcp       =    936                ;
	const int        chcp       =    65001                ;
	
    // set font

    stdio->info.cbSize       = sizeof(stdio->info)      ;
    stdio->info.dwFontSize.Y = _fontSizeY               ; // 16
    stdio->info.dwFontSize.X = _fontSizeX               ; // 0    
    stdio->info.FontWeight   = _fontWeight              ;

    wcscpy_s(     stdio->info.FaceName, _countof(_fontName) , _fontName ) ;
    
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), false, &stdio->info);
    
    // set stream
 
     _wsetlocale(LC_ALL , L"it_IT.UTF-8"    );      // set locale wide string
    _setmode(_fileno(stdout), _O_U8TEXT     );      // set Locale for stdio
    _setmode(_fileno(stderr), _O_U8TEXT     );      // set Locale for stdio    
    _setmode(_fileno(stdin ), _O_U8TEXT     );      // set Locale for stdio      

    // set CHCP : 936 1252 > win7 : 65001
    
    stdio->chcp = chcp ; 
    SetConsoleCP( chcp ) ;             
    SetConsoleOutputCP( chcp ); 

    // questo per evitare errori di conversione delle stringhe esadecimali
    setlocale ( LC_NUMERIC , "C" ) ;
    
    stdio->stream_stdout    = stdioStreamUTF8 ;
    stdio->stream_stdin     = stdioStreamUTF8 ;
    stdio->stream_stderr    = stdioStreamUTF8 ;
    
#else
    
    setlocale ( LC_ALL, "it_IT.UTF-8") ;
    setlocale ( LC_NUMERIC , "C"     ) ;

    stdio->stream_stdout    = stdioStreamUTF8 ;
    stdio->stream_stdin     = stdioStreamUTF8 ;
    stdio->stream_stderr    = stdioStreamUTF8 ;
    
#endif
} 

// ....................................................................... stdioSetMBS

void stdioSetMBS( stdio_t *stdio )
{
#ifdef _MSC_VER
    //const wchar_t*   _fontName=L"SimSun-ExtB";
    const wchar_t   _fontName[]	=	L"SimSun-ExtB"	;
    SHORT           _fontWeight	=	FW_NORMAL		;
    SHORT           _fontSizeY	=	16				;
    SHORT           _fontSizeX	=	0				;    

    // set font
    
    stdio->info.cbSize       = sizeof(stdio->info);
    stdio->info.dwFontSize.Y = _fontSizeY; // 16
    stdio->info.dwFontSize.X = _fontSizeX; // 0    
    stdio->info.FontWeight   = _fontWeight;

    wcscpy_s(     stdio->info.FaceName, _countof(_fontName) , _fontName ) ;
    
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), false, &stdio->info);
	
    int chcp=65001;            
    SetConsoleCP( chcp ) ;             
    SetConsoleOutputCP( chcp ); 
    
    setlocale ( LC_ALL, "it_IT.UTF-8") ;
    setlocale ( LC_NUMERIC , "C"     ) ; 
    
    stdio->stream_stdin		= stdioStreamMBS ;
    stdio->stream_stdout	= stdioStreamMBS ;
    stdio->stream_stderr	= stdioStreamMBS ;
    
#else

    setlocale ( LC_ALL, "it_IT.UTF-8") ;
    setlocale ( LC_NUMERIC , "C"      ) ;

    stdio->stream_stdin     = stdioStreamMBS ;
    stdio->stream_stdout	= stdioStreamMBS ;
    stdio->stream_stderr	= stdioStreamMBS ;
    
#endif
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
  
    char *tmp=gcStrDup(fileName); // questo per evitare seg fault
    
    for (uint32_t i=0;i<strlen(fileName);i++ )
    {
       // printf ( "(%c)",fileName[i] ) ;
       if ( tmp[i]=='\\' ) tmp[i] = '/' ;
    }

    _ccs        = _ccs      ;
    buffer[0]   = L'\0'     ;
    _fileName   = _fileName ;

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
    
    gcMapPut ( map , (void*)pf , gcFCloseDtor, GC_FAST );
 
    return pf ;
}
 

static unsigned char std_utf8_num_most_significant_ones[] = 
{
    /* 80 */   1, 1, 1, 1, 1, 1, 1, 1,   1, 1, 1, 1, 1, 1, 1, 1,
    /* 90 */   1, 1, 1, 1, 1, 1, 1, 1,   1, 1, 1, 1, 1, 1, 1, 1,
    /* A0 */   1, 1, 1, 1, 1, 1, 1, 1,   1, 1, 1, 1, 1, 1, 1, 1,
    /* B0 */   1, 1, 1, 1, 1, 1, 1, 1,   1, 1, 1, 1, 1, 1, 1, 1,
    /* C0 */   2, 2, 2, 2, 2, 2, 2, 2,   2, 2, 2, 2, 2, 2, 2, 2,
    /* D0 */   2, 2, 2, 2, 2, 2, 2, 2,   2, 2, 2, 2, 2, 2, 2, 2,
    /* E0 */   3, 3, 3, 3, 3, 3, 3, 3,   3, 3, 3, 3, 3, 3, 3, 3,
    /* F0 */   4, 4, 4, 4, 4, 4, 4, 4,   5, 5, 5, 5, 6, 6, 7, 8
};

static unsigned char std_utf8_lead_byte_data_mask[] = 
{
   0x7F, 0, 0x1F, 0x0F, 0x07, 0x03, 0x01
};

static int32_t std_utf8_min_by_len[] = 
{
   -1, 0x00, 0x80, 0x800, 0x10000ULL
};

// mbs must be capable of accommodating at least 4 bytes.
// Returns 0 on EOF or read error.

int std_read_one_utf8_char_from_file(FILE* stream, unsigned char* mbs) 
{
   int lead = getc(stream);
   
   if (lead == EOF)
      return 0;

   mbs[0] = lead;
   if (lead < 0x80)
      return 1;

   unsigned len = std_utf8_num_most_significant_ones[ lead - 0x80 ];
   
   if (len == 1 || len > 6)
      goto read_one_utf8_char_end;

   unsigned char mask = std_utf8_lead_byte_data_mask[len];
   uint32_t cp = lead & mask;
   
   for (int i=1; i<len; ++i) 
   {
      int ch = getc(stream);  
	  // Premature EOF or error.
      if (ch == EOF)
         goto read_one_utf8_char_end;
      if ((ch & 0xC0) != 0x80) 
	  {  
		 // Premature end of character.
         ungetc(ch, stream);
         goto read_one_utf8_char_end;
      }
      cp = (cp << 6) | (ch & 0x3F);
      if (i < 4)
         mbs[i] = ch;
   }

   if ( len > 4 
   ||   cp < std_utf8_min_by_len[len] 
   || ( cp >= 0xD800 && cp < 0xE000 ) 
   ||   cp >= 0x110000 )
      goto read_one_utf8_char_end;

   return len;

read_one_utf8_char_end:

   // Return U+FFFD.
   mbs[0] = 0xEF;
   mbs[1] = 0xBF;
   mbs[2] = 0xBD;
   
   return 3;
}

// ............................................................ fileGetUTF8Char	fgetu

unsigned char* fileGetUTF8Char(FILE *fi) 
{
	unsigned char mbs[5] ;
	int len;
	
	len=std_read_one_utf8_char_from_file(fi,   mbs) ;
	mbs[len]=0;
	
	return gcStrDup(mbs);
}

unsigned char* fgetu(FILE *fi) 
{
	return fileGetUTF8Char(fi);
}

// ............................................................ fileUngetUTF8Char	fungetu

void fileUngetUTF8Char(FILE *fi,unsigned char *mbs) 
{
	for(int i=strlen(mbs);i>0;i--)
	{
		ungetc(mbs[i-1],fi);
	}
}

void fungetu(FILE *fi,unsigned char *mbs) 
{
	fileUngetUTF8Char(fi,mbs);
}
 
//...................................................................... std_number_of_bytes_in_char

static int std_number_of_bytes_in_char(unsigned char val)
{
    if (val < 128)
    {
        return 1;
    }
    else if (val < 224) {
        return 2;
    } else if (val < 240) {
        return 3;
    } else {
        return 4;
    }
    return  0;
}

//...................................................................... stringGetUTF8Char	strgetu

char *stringGetUTF8Char( char *pstream )
{
	char buffer[5];
	int len = std_number_of_bytes_in_char(*pstream) ;

	for(int i=0;i<len;i++) buffer[i]=*pstream++;
	buffer[len]=0;

	return gcStrDup(buffer);	
}

char *strgetu( char *pstream )
{
	return stringGetUTF8Char( pstream )	;
}

//...................................................................... getUTF8CharFromPString	pstrgetu

char *getUTF8CharFromPString( char **pstream )
{
	char buffer[5];
	int len = std_number_of_bytes_in_char(**pstream) ;

	for(int i=0;i<len;i++) buffer[i]= (*pstream)[i];
	buffer[len]=0;

    (*pstream) += strlen(buffer);
 
	return gcStrDup(buffer);	
}

char *pstrgetu( char **pstream )
{
	return getUTF8CharFromPString( pstream )	;
}

//...................................................................... cnv_mbc_to_utf32

char32_t cnv_mbc_to_utf32(char mbs[])
{
	char32_t c32;

	mbstate_t ss = {0} ;  // initial state
	mbrtoc32(&c32, mbs, MB_CUR_MAX, &ss);

	return c32 ;
}

//...................................................................... cnv_mbc_to_utf16

void cnv_mbc_to_utf16(char mbs[],char16_t c16x2[] )
{
	char16_t c16;

	mbstate_t ss = {0} ; // initial state
	
	int len ;

	len = mbrtoc16(&c16, mbs, MB_CUR_MAX, &ss);
	c16x2[0] = c16 ;

	len = mbrtoc16(&c16, mbs, MB_CUR_MAX, &ss);
	c16x2[1] = c16 ;

}

//...................................................................... cnv_utf16_to_mbc

char* cnv_utf16_to_mbc(char16_t c16x2[] )
{
	mbstate_t st = {0};

	char out[5];
	out[0]=out[1]=out[2]=out[3]=out[4]=0;   
	int rc=0, in=0;
	rc = c16rtomb(out, in, &st);

	return gcStrDup(out);
}
 