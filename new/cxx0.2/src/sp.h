
#ifndef CD_SMART_POINTER
#define CD_SMART_POINTER


#define SMART_POINTER_ID_INTERNAL MERGE(smartPointerName,1)
#define SMART_POINTER_ID 		  SMART_POINTER_ID_INTERNAL

 
typedef struct smartPointer_s
{
	const void*  SMART_POINTER_ID ;
} smartPointer_t ;
 
#define smartPointerTypeDef(TYPE)\
typedef struct MERGE( MERGE( smartPointer_,TYPE) , _s )  \
{\
	TYPE*  SMART_POINTER_ID ;\
} MERGE( MERGE( smartPointer_, TYPE) , _t )  ;


struct smartPointer_s * const gcLocalSmartPointer( gc_t *gc , void* unsafePtr ) ;

#define  gcUniquePointer(PTR) gcLocalSmartPointer( gc , PTR )

#define smartPointer_t(TYPE) MERGE(MERGE(smartPointer_,TYPE),_t) * const

#define sp(PTR) PTR->SMART_POINTER_ID

#endif

