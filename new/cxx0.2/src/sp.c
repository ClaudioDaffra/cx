
#include "cxx.h"


// ....................................................................... gcLocalSmartPointerMalloc


struct smartPointer_s * const gcLocalSmartPointer( gc_t *gc , void* unsafePtr )
{
    if ( unsafePtr==0 ) return NULL ;

	struct smartPointer_s * sp = (struct smartPointer_s*) gcLocalMalloc ( gc,sizeof(smartPointer_t) );
	
	if (sp != NULL )
	{
		sp->SMART_POINTER_ID = (void*) unsafePtr ;
	}
	else
	{
		sp->SMART_POINTER_ID  = NULL ;
	}

    return (struct smartPointer_s * const) sp ;
}
