#ifndef cdIterator
#define cdIterator

    #ifdef __linux__
    #define _GNU_SOURCE 
    #endif

    #include <stddef.h>

    #define iterator(OBJ,ID)     OBJ##DataType ## ID*  
     
    #define itBegin(ID)         ((ID).data)
    #define itEnd(ID)           ((ID).data + (ID).size) 

    #define itRBegin(ID)        ((ID).data + (ID).size -1)
    #define itREnd(ID)          ((ID).data - 1)

    #define itNext(ID)          (ID++)
    #define itPrev(ID)          (ID--)    
    #define itRNext(ID)         (ID--)    
    
    #define itAdvance(ID,NUM)   (ID+=NUM)
    
    #define itDistance(OBJ,ID,p1,p2,dist)\
        do {\
            ptrdiff_t ptrdiff = ( ((OBJ##DataType ## ID*)p2) - ((OBJ##DataType ## ID*)p1 ) );\
            dist=ptrdiff;\
        } while(0);
    
#endif


/**/


