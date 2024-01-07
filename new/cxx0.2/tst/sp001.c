
#include "../src/cxx.h"
#include "../src/gcWrap.h"

// clear    ; gcc   src/gc.c src/sp.c tst/sp001.c  -o bin/x       -Wall -Wextra -pedantic 
// cls      & cl    src\gc.c src\sp.c tst\sp001.c /Febin\x.exe   /WX /utf-8


int main(void)
{
    //

	smartPointerTypeDef(int);

	smartPointer_t(int) p1 = (smartPointer_t(int)) gcUniquePointer ( new ( sizeof(int)*100  ) );
 
	*sp(p1) = 10 ;

	printf ( "\nsmart pointer p1 in 0 e' %d\n" ,*sp(p1) );

	smartPointer_t(int) p2 = (smartPointer_t(int)) gcUniquePointer ( new ( sizeof(int)*100  ) );

	//p1=p2; const !
	
	*sp(p2) = 11 ;	

	printf ( "\nsmart pointer p1 in 0 e' %d\n" ,*sp(p1) );
	printf ( "\nsmart pointer p2 in 0 e' %d\n" ,*sp(p2) );
   
    printf ( "\n") ;


    return 0;
}
