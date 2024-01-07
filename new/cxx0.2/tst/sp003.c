
#include "../src/cxx.h"
#include "../src/gcWrap.h"

// clear    ; gcc   src/gc.c tst/sp003.c  -o bin/x       -Wall -Wextra -pedantic 
// cls      & cl    src\gc.c tst\sp003.c /Febin\x.exe   /WX /utf-8
 
typedef struct smartPointer_s
{
	void *unsafePtr;
	unsigned char type 	 		;
	unsigned char typeAlloc  	;
	unsigned char ptrAlloc  	;
} smartPointer_t ;

typedef struct smartPointer_s *   		pSmartPointer_t ;
 
typedef struct smartPointer_s * const  pcSmartPointer_t ;

pcSmartPointer_t gcLocalSmartPointer( gc_t *gc , size_t ptrSize )
{
	smartPointer_t 	* sp 		= (smartPointer_t*) gcLocalMalloc ( gc,sizeof(smartPointer_t) );

	if (sp != NULL )
	{
		sp->type 		= 1	;
		sp->typeAlloc 	= 1	;
		sp->ptrAlloc	= 0	;	
		
		void * unsafePtr = (void*) gcLocalMalloc ( gc,ptrSize );
		if (unsafePtr != NULL )
		{
			sp->unsafePtr = (void*) unsafePtr ;
			sp->ptrAlloc	= 1	;	
		}
		else
		{
			return (pcSmartPointer_t) NULL ;
		}
	}
	else
	{
		return (pcSmartPointer_t) NULL ;
	}

    return (pcSmartPointer_t)sp ;
}

#define spPtr( TYPE , ID ) (TYPE*)(ID->unsafePtr)



int main(void)
{
	pcSmartPointer_t p1 = (pcSmartPointer_t) gcLocalSmartPointer(gc,sizeof(int)*100) ;
	
	*spPtr(int,p1)=10;

	pcSmartPointer_t p2 = (pcSmartPointer_t) gcLocalSmartPointer(gc,sizeof(int)*100) ;
	
	*spPtr(int,p2)=*spPtr(int,p1);

	
    return 0;
}
