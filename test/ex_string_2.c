
#include "../lib/string.h"
#include "../lib/gc.h"
#include "../lib/stdio.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

/*

    cl  lib\gc.c lib\fs.c lib\string.c test\ex_string_2.c /Fex.exe   /WX  /EHsc 
    gcc lib\gc.c lib\fs.c lib\string.c test\ex_string_2.c -o x.exe   -Wall -Wextra -pedantic
    gcc lib/gc.c lib/fs.c lib/string.c test/ex_string_2.c -o x       -Wall -Wextra -pedantic

*/ 



int main ( void )
{
    gcStart();

    /**/

    // no more memory leak #1 , check with valgrind.

    char* temp2=gcMalloc( sizeof(char)*10 );
    char* temp3=gcMalloc( sizeof(char)*10 );
    strcpy ( temp3, "claudio" );
    temp2 =  strdup (  temp3 ) ; // automatic save pointer (wrapper) gcStrDup
 
    /**/

    // ...................................... stringFromStrC

    printf ("\n\n --- stringFromStrC ( s1 , \"claudio Daffra\" ) ;\n") ;
 
    stringType(s1) ;
 
    iterator(s1) its1 ;
   
    stringNew(s1,128);
    
    stringFromStrC ( s1 , "claudio Daffra" ) ;

    char* temp1 = stringToStrC(s1)  ; // no more LEAK #2

    printf ( "\nstring s1    size[%d] "     ,   (int)s1.size                );
    printf ( "\nchar*  temp1 [%s]"          ,   temp1                       );
    printf ( "\nchar*  temp1 size [%d]"     ,   (int)(int)strlen(temp1)     );
    printf ( "\nDEBUG s1 [%d] [%s]"         ,   (int)strlen(str(s1)),str(s1));     
 
    // ...................................... stringFromStrC
   
    printf ( "\nfind %c = pos %d",'c' , (int)stringFindChar(s1,'c') );
    printf ( "\nfind %c = pos %d",'x' , (int)stringFindChar(s1,'x') );
 
    // ...................................... stringFindStrC
    // ...................................... stringFindString
  
    stringType(s2);

    stringFromStrC ( s2 , "Daffra" ) ;

    printf ( "\n find 'daffra' in 'claudio Daffra' = %p",stringFindStrC(s1,"Daffra")    );
    printf ( "\n find 'daffra' in 'claudio Daffra' = %p",stringFindString(s1,s2)        );

    stringFromStrC ( s2 , "xxx" ) ;
    printf ( "\n find 'xxx' in 'claudio Daffra' = %p", stringFindStrC(s1,"xxx")   );
    printf ( "\n find 'xxx' in 'claudio Daffra' = %p", stringFindString(s1,s2)  );
 
    // ...................................... stringReplaceStrC
    
    printf ("\n\n --- #1 stringReplaceStrC(ID,\"a\",\"@\") ;\n") ; 
 
    stringReplaceStrC(s1,"a","@") ;
    
    printf ( "\ns1 = [%s]\n",stringToStrC(s1) ) ;
 
    // ...................................... stringReplaceString
    
    printf ("\n\n --- #2 stringReplaceString(ID,\"@\",\"*\") ;\n") ;
    
    stringType(pattern) ;
    stringFromStrC(pattern,"@") ;

    stringType(replace) ;
    stringFromStrC(replace,"*") ;

    stringReplaceString( s1 , pattern  , replace  );

    printf ( "\ns1 = [" );    
    stringPrint(s1);
    printf ( "]\n" );
    
    // ...................................... free 
    
    //free(temp1);
    gcFree(temp2);
    //free(temp3);
    //free(temp4);
  
    /**/

    gcStop();

    printf ("\n");
    return 0 ;
}
