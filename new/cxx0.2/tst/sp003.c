
#include "../src/cxx.h"
#include "../src/gcWrap.h"

// clear    ; gcc   src/gc.c src/sp.c tst/sp003.c  -o bin/x       -Wall -Wextra -pedantic 
// cls      & cl    src\gc.c src\sp.c  tst\sp003.c /Febin\x.exe   /WX /utf-8

#define typeDef(TYPE)\
typedef struct MERGE(type_,MERGE(TYPE,_s))\
{\
	TYPE* data;\
} MERGE(type_,MERGE(TYPE,_t)) ;\

#define typeAlloc(ID,SIZE) (ID)->data = gcMalloc(SIZE);

int main(void)
{
    //
	
	typeDef(int) ;

	type_int_t* pint = (type_int_t*)gcMalloc(sizeof(type_int_t));

	typeAlloc(pint,sizeof(int)*100);

	pint->data[3] = 10 ;

	printf ( "\nsmart pointer p2 e' %d\n" ,  pint->data[3] 							);
	
	// 
	
	smartPointer_t   p1 = (smartPointer_t)gcLocalSmartPointer( gc , pint ) ;

	printf ( "\nsmart pointer p2 e' %d\n" ,   ((type_int_t*)p1->ptr)->data[3]   	);

	printf ( "\nsmart pointer p2 e' %d\n" ,   sptr(type_int_t,p1)->data[3]   		);

	printf ( "\nsmart pointer p2 e' %d\n" ,   sptrData(type_int_t,p1)[3]   			);
	
	// 
	
    printf ( "\n") ;

    return 0;
}

