

#include "../src/cxx.h"

// clear ; gcc src/gc.c src/stdio.c tst/stdio002.c -o bin/x -Wall -pedantic -Wextra

// cls & cl src\gc.c src\stdio.c tst\stdio002.c /Febin\x.exe /WX /utf-8

int main(void)
{	
	stdio_t std ;

	stdioSetMBS(&std);

	// ------------------------------------------------------------------------------	EX 1

	FILE *fi = fopen("tst/file.utf8.txt", "r");

	if ( fi!=NULL ) 
	{ 
		//FILE *fo = fopen("utf8out.txt", "w+");
		
		unsigned char stringona[4096];
		unsigned char *ps = stringona ;
		*ps='\0';
		
		int fPush=1;
		
		while (!feof(fi))
		{
			unsigned char *mbs ;

			mbs=fileGetUTF8Char(fi); // fgetu

			printf("(%d %s)",strlen(mbs) ,mbs ) ;

		}
	}
	else
	{
		printf ( "\n file :: tst/file/utf8.txt -> not found");
	}

	// ------------------------------------------------------------------------------	EX 2

	char *pstream = "木月ВГ";
	
	printf ( "\n");
	printf ( "\n cnv(%s)",pstream);
 	printf ( "\n");
	
	char *buffer;

	buffer=stringGetUTF8Char(pstream);	// strgetu
	printf ( "\n[%s]\n",  buffer );
	pstream+=strlen(buffer);

	buffer=stringGetUTF8Char(pstream);
	printf ( "\n[%s]\n",  buffer );
	pstream+=strlen(buffer);

 
	printf ( "\n[%s]\n",  getUTF8CharFromPString(&pstream) ); // pstrgetu
	
	printf ( "\n[%s]\n",  pstrgetu(&pstream) ); 

	// ------------------------------------------------------------------------------	EX 3
 
	printf ( "\n");
	printf ( "\nUTF-8 	(hex)	0xF0 0x9F 0x8D 0x8C ");
	printf ( "\nUTF-16 	(hex)	0xD83C 0xDF4C		");
	printf ( "\nUTF-32 	(hex)	0x0001F34C			");
	printf ( "\n");
 
	//char * cnv1 = "\u00df\u6c34\U0001F34C"; // or u8"ß水🍌"
	//char * cnv2 = "ß水🍌"; // or u8"ß水🍌"	
	
	char mbs[] = "🍌" ;  
	
	char32_t c32 = cnv_mbc_to_utf32(mbs);
	printf("\nmbs %s", mbs);
	printf("c32: 0x%08x \n", c32);
 

	char16_t c16x2[2];
	
	cnv_mbc_to_utf16(mbs,c16x2);
	printf("\nmbs %s", mbs);
	printf("c16: 0x%08x 0x%08x \n", c16x2[0],c16x2[1]);
	
	
	printf ( "\nfrom c16x2 toMBS {%s} ",cnv_utf16_to_mbc(c16x2) ) ;
	
	return 0 ;
}

// cl stdio.c /Fex.exe /utf-8