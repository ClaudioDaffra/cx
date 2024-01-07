#include "../src/cxx.h"



/*
    1)  clear   ; gcc src/gc.c tst/vector003.c  -o   bin/x      -Wall -Wextra -pedantic

    2)  cls     & cl src\gc.c tst\vector003.c   /Febin\x.exe    /WX /utf-8  
*/


int main ( void )
{
    gcStart() ;
   
    // .................................... vector typedef 
 
    printf ( "--- vectorType(int,v1); \n" );

    // vector_ID_d            :    TYPE
    // ID_d                   :    TYPE    
    // vector_ID_s            :    struct vector_ID_s
    // vector_ID_t            :    vector_ID_s
    // vector_ID_p            :    vector_ID_t*
     
    vectorTypeDef(int,v1);
    
    printf ( "vector : data size %zu , struct size %zu , struct size %zu,  struct * size %zu\n"
        ,sizeof(vector_v1_d),sizeof(struct vector_v1_s),sizeof(vector_v1_t),sizeof(vector_v1_p) );

    // .................................... vector new
    
    vector_v1_t    v1 ;
    
    vectorAlloc(v1,8) ;

    // .................................... vector size capacity empty
    
    printf ( "vector : size %zu capacity %zu empty %d.\n",vectorSize(v1),vectorCapacity(v1),vectorEmpty(v1)    ) ; 
           
    // .................................... vector push back

    printf ( "--- vectorPushBack( v1 ,10 item ) ; \n" );
    
    for(int i=0;i<10;i++) vectorPushBack( v1 ,i*10 ) ;

    // .................................... iterator
    
    printf ( "--- iterator vector ; \n" );
    
    for ( itVector(v1) it = vectorBegin(v1); it<vectorEnd(v1); it++) 
    {
        printf ( "(%02d)",*it );
    }

    // .................................... iterator
    
    printf ( "\n--- iterator ; \n" );
    
    for ( iterator(v1) it = vectorBegin(v1); it<vectorEnd(v1); it++) 
    {
        printf ( "(%02d)",*it );
    }

    // .................................... distance

    printf ( "\n difference %zu\n",itDistance(vectorBegin(v1),vectorEnd(v1)) )  ;

    // .................................... dealloc
    
    printf ( "\n--- dealloc v1\n" ) ;  
      
    vectorDealloc(v1);

    // .................................... vector type    

    vectorType(int); // for int* -> typedef int* pint ;
    
    vector_int_t v3, *v4 = new(vector_int_t);
    
    vectorAlloc(v3,8);
    
    vectorAlloc(*v4,8);
    
    delete(v4);    

    // .................................... vector of vector
        
    // vectorType(float);                  // vector_float_t
 
    vectorTypeDef( float       , x1 ) ;    // vector_x1_t   -> vettore di float
    
    vectorTypeDef( vector_x1_t , x2 ) ;    // vector_x2_t   ->  vettore di vettore di float

    vectorTypeDef( vector_x2_t , x3 ) ;    // vector_x3_t   ->  vettore di vettore di vettore di float 
 
    // define vector contain vector
    
        vector_x3_t    x3 ;  // [8,8,8];

        const size_t dim=8;
        
        x3.data                         = (void*) gcMalloc ( sizeof(x3_d) * dim ) ;
        x3.size=0;
        x3.capacity=dim;
        
        x3.data[2].data                 = (void*) gcMalloc ( sizeof(x2_d) * dim ) ;
        x3.data[2].size=0;
        x3.data[2].capacity=dim;
            
        x3.data[2].data[4].data         = (void*) gcMalloc ( sizeof(x1_d) * dim) ;
        x3.data[2].data[4].size=0;
        x3.data[2].data[4].capacity=dim;
                
        x3.data[2].data[4].data[6] = 3.1 ;
        
        printf("\n --> %g.\n",x3.data[2].data[4].data[6] );

    // define vector contain vector

        vector_x3_t    y3 ;  // [8,8,8];

        vectorAllocVector(x3_d,y3                   ,8    );
        vectorAllocVector(x2_d,vectorX(y3,2)        ,8    );
        vectorAllocVector(x1_d,vectorXY(y3,2,4)     ,8    );
        
        vectorXYZ(y3,2,4,6)=4.6;
        
        printf("\n --> %g.\n",vectorXYZ(y3,2,4,6) );
        
    // ...................................... stop
    
    gcStop() ;

    printf ("\n");
    
    return 0 ;
}



/**/
