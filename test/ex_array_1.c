

#include "../lib/marray.h"
#include "../lib/type.h"

/*

   cl  lib\gc.c  lib/fs.c test\ex_array_1.c   /Fex.exe        /EHsc /WX
   gcc lib\gc.c  lib/fs.c test\ex_array_1.c   -o   x.exe      -Wall -Wextra -pedantic
   gcc lib/gc.c  lib\fs.c test/ex_array_1.c   -o   x          -Wall -Wextra -pedantic
   
*/

int main ( void )
{
    gcStart();
    
    /**/

    // ................................................... arrayType
    
    printf ( "\n --- arrayType(double,a1);" ) ;
    
    arrayType(double,a1);

    // ................................................... arrayNew
        
    printf ( "\n --- arrayNew(a1,64);" ) ;
    
    arrayNew(a1,8);

    printf ( "\n --- itVector(v1) itv1 ;" ) ;

    // ................................................... iterator
    
    itArray(a1) ita1 ;
    
    printf ( "\n" );
    int ndx=1;
    for( ita1 = arrayBegin(a1) ; ita1 != arrayEnd(a1); ita1++ )  
    {    
        *ita1 = 1.2*ndx++;
        printf ( "[%.3e]" ,*ita1 ) ;
    }

    // ................................................... size
        
    printf ( "\n --- arraySize(v1);" ) ;

    printf ( "\na1 :: size %d.", (int)arraySize(a1) ); 

    // ................................................... front

    printf ( "\n --- arrayFront(a1);" ) ;
    
    printf ( "\na1 :: front [%.3e].", arrayFront(a1) ); 

    // ................................................... back

    printf ( "\n --- arrayBack(a1);" ) ;

    printf ( "\na1 :: back [%.3e].", arrayBack(a1) ); 
 
    // ................................................... copy

    printf ( "\n --- arrayDim(double,a2,4);" ) ;    

    arrayDim(double,a2,4);

    printf ( "\n --- arrayCopy( a2,a1 ) ;" ) ; 
        
    arrayCopy( a2,a1 ) ;

    itArray(a2) ita2 ;
    
    printf ( "\n" );
    for( ita2 = arrayBegin(a2) ; ita2 != arrayEnd(a2); ita2++ )  
    {    
        printf ( "[%.3e]" ,*ita2 ) ;
    }

    // ................................................... fill
    
    arrayFill(a2,12.34);

    printf ( "\n" );
    for( ita2 = arrayBegin(a2) ; ita2 != arrayEnd(a2); ita2++ ) printf ( "[%.3e]" ,*ita2 ) ; 
 
    // ................................................... array of array
 
    printf ( "\n --- arrayType( double*,aa ,2) ;" ) ;  
 
    typedef double* pdouble;

    arrayType( pdouble ,aa)[2];

    arrayNew( aa[0] , 2 ) ;
    arrayNew( aa[1] , 2 ) ;
/*
    aa[0].data[0] = &a1.data[0] ;
    aa[0].data[1] = &a1.data[1] ;
*/
    arrayPointerClone( aa[0] , a1 , 2 ) ;
/*
    aa[1].data[0] = &a2.data[0] ;
    aa[1].data[1] = &a2.data[1] ; 
*/
    arrayPointerClone( aa[1] , a2 , 2 ) ;
/*
    *(aa[0].data[0]) = 11.22 ;
    *(aa[1].data[0]) = 33.44 ;
*/
    arrayPointerData( aa[0] , 0 ) = 11.22 ;
    arrayPointerData( aa[1] , 0 ) = 33.44 ;
/*
    *(aa[0].data[1]) = 111.22 ;
    *(aa[1].data[1]) = 133.44 ;
*/
    arrayPointerData( aa[0] , 1 ) = 111.22 ;
    arrayPointerData( aa[1] , 1 ) = 133.44 ;


    printf ( "\n" );
    for( ita1 = arrayBegin(a1) ; ita1 != arrayEnd(a1); ita1++ ) printf ( "[%.3e]" ,*ita1 ) ;

    printf ( "\n" );
    for( ita2 = arrayBegin(a2) ; ita2 != arrayEnd(a2); ita2++ ) printf ( "[%.3e]" ,*ita2 ) ; 

    printf ( "\n" );

    // ................................................... array of void*

    typedef void* pvoid ;

    arrayType( pvoid ,av )[2];

    arrayNew( av[0] , 2 ) ;
    arrayNew( av[1] , 2 ) ;
/*
    av[0].data[0] = &a1 ;
    av[0].data[1] = &a2 ;
*/

    arrayData(av[0])[0] = &a1 ; // --> arrayType(double,a1);
    arrayData(av[0])[1] = &a2 ; // --> arrayType(double,a2);

/*
    printf ( "\n a1/%d ",  (int)(*   ((array_a1*) av[0].data[0])   ).size     ) ;
    printf ( "\n a2/%d ",  (int)(*   ((array_a1*) av[0].data[1])   ).size     ) ;
*/
    
    printf ( "\n # a1/%d ",  (int)arrayPointerVoidAt(av,0,0).size     ) ;
    printf ( "\n # a2/%d ",  (int)arrayPointerVoidAt(av,0,1).size     ) ;

    /**/

    // ................................................... arrayType
    
    printf ( "\n --- array sort ;" ) ;
    
    arrayDim( stringc_t ,as , 4 );

    arrayAt(as,0) = gcStrDup("daffra") ;
    arrayAt(as,1) = gcStrDup("claudio") ;
    arrayAt(as,2) = gcStrDup("lorenzo") ;
    arrayAt(as,3) = gcStrDup("barbara") ;

    arraySort( as , gcCompareStrC ) ;
    
    itArray(as) itas ;

    printf ( "\n" ) ;    
    for (itas=arrayBegin(as);itas!=arrayEnd(as);itas++) printf ( "[%s]",*itas );

    /**/
    
    gcStop();
    
    printf ("\n");
    return 0 ;
    
}

/*


    claudio@ubuntu:~/cx$ valgrind --leak-check=full ./x
    ==31688== Memcheck, a memory error detector
    ==31688== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
    ==31688== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
    ==31688== Command: ./x
    ==31688== 

     --- arrayType(double,a1);
     --- arrayNew(a1,64);
     --- itVector(v1) itv1 ;
    [1.200e+00][2.400e+00][3.600e+00][4.800e+00][6.000e+00][7.200e+00][8.400e+00][9.600e+00]
     --- arraySize(v1);
    a1 :: size 8.
     --- arrayFront(a1);
    a1 :: front [1.200e+00].
     --- arrayBack(a1);
    a1 :: back [9.600e+00].
     --- arrayDim(double,a2,4);
     --- arrayCopy( a2,a1 ) ;
    [1.200e+00][2.400e+00][3.600e+00][4.800e+00][6.000e+00][7.200e+00][8.400e+00][9.600e+00]
    [1.234e+01][1.234e+01][1.234e+01][1.234e+01][1.234e+01][1.234e+01][1.234e+01][1.234e+01]
     --- arrayType( double*,aa ,2) ;
    [1.122e+01][1.112e+02][3.600e+00][4.800e+00][6.000e+00][7.200e+00][8.400e+00][9.600e+00]
    [3.344e+01][1.334e+02][1.234e+01][1.234e+01][1.234e+01][1.234e+01][1.234e+01][1.234e+01]

     # a1/8 
     # a2/8 
    ==31688== 
    ==31688== HEAP SUMMARY:
    ==31688==     in use at exit: 0 bytes in 0 blocks
    ==31688==   total heap usage: 15 allocs, 15 frees, 1,416 bytes allocated
    ==31688== 
    ==31688== All heap blocks were freed -- no leaks are possible
    ==31688== 
    ==31688== For counts of detected and suppressed errors, rerun with: -v
    ==31688== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
    claudio@ubuntu:~/cx$

*/


/**/



