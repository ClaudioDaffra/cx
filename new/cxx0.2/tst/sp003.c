
#include "../src/cxx.h"
#include "../src/gcWrap.h"

// clear    ; gcc   src/gc.c src/sp.c tst/sp003.c  -o bin/x       -Wall -Wextra -pedantic 
// cls      & cl    src\gc.c src\sp.c  tst\sp003.c /Febin\x.exe   /WX /utf-8

			
int main(void)
{

	smartPointerTypeDef(int);
	
	smartPointer_int_t p0 = (smartPointer_int_t)gcMalloc(sizeof(struct smartPointer_int_s));

		spBegin(cd)
		
			smartPointerTypeDef(int);
			
			smartPointer_int_t p1 = (smartPointer_int_t)gcMalloc(sizeof(struct smartPointer_int_s));
			
			p1->var = (int*) gcMalloc( sizeof(int)*100 ) ;

			sptr(int,p1)[3]=4;
			
			printf ( "\nsmart pointer p1 e' %x\n" ,  (int*)p1->ptr  	);	
			printf ( "\nsmart pointer p1 e' %d\n" ,   sptr(int,p1)[3]	);
			
			smartPointerMove(p0,cd,p1);

		spEnd(cd)

	printf ( "\nsmart pointer p0 e' %d\n" ,   sptr(int,p0)[3]	);
			
    printf ( "\n") ;

    return 0;
}

