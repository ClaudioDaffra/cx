
#include "../src/cxx.h"
#include "../src/gcWrap.h"

// clear    ; gcc   src/gc.c src/sp.c tst/sp002.c  -o bin/x       -Wall -Wextra -pedantic 
// cls      & cl    src\gc.c src\sp.c tst\sp002.c /Febin\x.exe   /WX /utf-8


int main(void)
{
    //

	smartPointer_t p1 = (smartPointer_t)gcLocalSmartPointer( gc , new(sizeof(int)*100)  );

	sp(int,p1)=10;

	printf ( "\nsmart pointer p1 e' %d\n" ,sp(int,p1) );

	smartPointer_t p2 = (smartPointer_t)gcLocalSmartPointer( gc , new(sizeof(int)*100)  );
 
	sp(int,p2)=12;
	
	printf ( "\nsmart pointer p2 e' %d\n" ,sp(int,p2) );
   
    printf ( "\n") ;


	gcSmartPointerMove(p1,p2);


	if (p1->ptr != NULL)
		printf ( "\nsmart pointer p1 e' %d\n" ,sp(int,p1) );
    else
		printf ( "\nsmart pointer p1 e' NULL \n"  );		
 

	if (p2->ptr != NULL )
		printf ( "\nsmart pointer p2 e' %d\n" ,sp(int,p2) );
    else
		printf ( "\nsmart pointer p2 e' NULL \n"  );	
	
    printf ( "\n") ;


    return 0;
}

