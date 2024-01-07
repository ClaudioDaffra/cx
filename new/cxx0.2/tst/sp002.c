
#include "../src/cxx.h"
#include "../src/gcWrap.h"

// clear    ; gcc   src/gc.c src/sp.c tst/sp002.c  -o bin/x       -Wall -Wextra -pedantic 
// cls      & cl    src\gc.c src\sp.c tst\sp002.c /Febin\x.exe   /WX /utf-8

/*
void* gcSmartPointerMove( const void* dest, const void *source )
{
	dest = source ;
	gc
}
*/

#define gcSmartPointerMove(DEST,SOURCE)\
do{\
*((struct smartPointer_s *)DEST)	=	*((struct smartPointer_s *)SOURCE); \
\
gcFree(SOURCE);\
\
} while(0);

int main(void)
{
    //

	smartPointerTypeDef(int);

	smartPointer_t(int) p1 = (smartPointer_t(int)) gcUniquePointer ( new ( sizeof(int)*100  ) );
 
	*sp(p1) = 10 ;

	printf ( "\n#1 smart pointer %z / p1 in 0 e' %d\n" ,(size_t)p1,*sp(p1) );

	smartPointer_t(int) p2 = (smartPointer_t(int)) gcUniquePointer ( new ( sizeof(int)*100  ) );

    printf ( "\n") ;

	gcSmartPointerMove(p2,p1) ;
	
	printf ( "\n#2 smart pointer %z / p1 in 0 e' %d\n" ,(size_t)p1,*sp(p1) );
	printf ( "\n#3 smart pointer %z / p2 in 0 e' %d\n" ,(size_t)p2,*sp(p2) );

	printf ( "\n" ,*sp(p2) );
	
    return 0;
}
