
#ifndef CD_SMART_POINTER
#define CD_SMART_POINTER


struct smartPointer_s
{
	union{
		void*  const  	ptr	;
		void*  		 	var	;	
	};
} ;
 
typedef struct smartPointer_s * const smartPointer_t ;
 
struct smartPointer_s *  gcLocalSmartPointer( gc_t *gc , void* unsafePtr ) ;

#define sp(TYPE,PTR) *(TYPE*)PTR->ptr

#define gcSmartPointerMove(p1,p2)\
do{\
	gcFree(p1->var);\
	p1->var = p2->var;\
	p2->var=NULL;\
}while(0);


#define sptr(TYPE,ID) ((TYPE*)ID->ptr)

#define sptrData(TYPE,ID) ((TYPE*)ID->ptr)->data

	
//

#endif

