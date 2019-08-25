
#include "../lib/map.h"
#include "../lib/gc.h"
#include "../lib/stdio.h"

/*

    cl  lib\map.c lib\gc.c lib\fs.c test\ex_map_1.c /Fex.exe /WX /EHsc   
    gcc lib\map.c lib\gc.c lib\fs.c test\ex_map_1.c -o x.exe -Wall -Wextra -pedantic
    gcc lib/map.c lib/gc.c lib\fs.c test/ex_map_1.c -o x     -Wall -Wextra -pedantic

*/

void callbackRoot1 ( void* p ) 
{
	printf ( "\n callback Root1 : ");
    printf("\n map Node Root1, %p -> %s : %d", p, (const char*) mapFirst(p) ,*(int*) mapSecond(p) ); 
}

int main(void)
{
    gcStart() ;
    
	// ------------------------------------------------------------------------------------ new

    //map_t *root1 	= map.new ( mapMultiKey ,mapOrdered ,gcCompareStrC ) ; 

    mapType(root1);

    mapMultiOrderedNew(root1,gcComparepStrC);

	// ------------------------------------------------------------------------------------ insert	

    root1=map.insert ( root1 ,  "a"	,	gcIntDup(1)  ) ;	 
		  map.insert ( root1 ,  "b"	,	gcIntDup(2)  ) ;
		  map.insert ( root1 ,  "e"	,	gcIntDup(5)  ) ;
		  map.insert ( root1 ,  "e"	,	gcIntDup(8)  ) ;    // single key  e=8 not insert       
		  map.insert ( root1 ,  "f"	,	gcIntDup(6)  ) ;	
		  map.insert ( root1 ,  "c"	,	gcIntDup(3)  ) ;    // ordered not
		  map.insert ( root1 ,  "d"	,	gcIntDup(4)  ) ;          

	// ------------------------------------------------------------------------------------ find
    
    map_t 	*p=NULL;

    char *key = "c";

	p = map.find( root1 , key	) ;
	
	if ( p  != NULL ) 	
		printf ( "\n\n TROVATO root1 : {%10s}{%3d} " , (const char*)key ,*((int*)p->second)	) ;	
	else				
		printf ( "\n\n NON trovato");

	// ------------------------------------------------------------------------------------ remove
    printf("\n\n [*] remove : %s ",key);
    root1 = map.remove(root1, key);

    // ------------------------------------------------------------------------------------ iterator print
        
    printf ("\n----------------------------------\n" ) ;
    
    itMap(it) ;
    
    for ( mapBegin(it,root1) ; mapEnd(it) ; mapNext(it) ) 
    {
        printf("\n map Node Root1, Min [[[%s]]] " ,   (const char*) itMapFirst(it)    );  
        printf(" [[[%d]]]  "                      ,   *(int*) itMapSecond(it)         );             
    }    

	// ------------------------------------------------------------------------------------ map NODE MAX	
	p=map.Max(root1);
    
    printf("\n map Node Root1, Max %s : %d",  (const char*)p->first ,*((int*)p->second) ); 

	// ------------------------------------------------------------------------------------ map NODE MIN	
	p=map.Min(root1);
    
    printf("\n map Node Root1, Min %s : %d",  (const char*)p->first ,*((int*)p->second) ); 

	// ------------------------------------------------------------------------------------ map HEIGHT	
    printf("\n map Node Height %d Size %zu", map.height(root1) , map.size(root1)    ); 

	// ------------------------------------------------------------------------------------ inOrder	
	map.inOrder( root1,callbackRoot1 ) ;


    printf ("\n----------------------------------\n" ) ;

    for ( mapBegin(it,root1) ; mapEnd(it) ; mapNext(it) ) 
    {
        printf("\n map Node Root1, Min [[[%s]]] " ,   (const char*) itMapFirst(it)    );  
        printf(" [[[%d]]]  "                      ,   *(int*) itMapSecond(it)         );             
    }
 
        
	// ------------------------------------------------------------------------------------ delete	

	map.delete ( root1 ) ;

    printf ( "\n" );

    //
    
    gcStop();
        
    return 0;
}


/*

    E:\c--\test>x.exe

    root1 : {         a}{  1}
    root1 : {         b}{  5}
    root1 : {         c}{  2}
    root1 : {         d}{  3}
    root1 : {         e}{  4}

    TROVATO root1 : {         c}{  2}

    [*] remove : c

    root1 : {         a}{  1}
    root1 : {         b}{  5}
    root1 : {         d}{  2}
    root1 : {         e}{  4}
    map Node Root1, Max e : 4
    map Node Root1, Min a : 1
    map Node Height 0 Size 4
    callback Root1 :  map Node Root1  0x151410 = a :  1
    callback Root1 :  map Node Root1  0x1514f0 = b :  5
    callback Root1 :  map Node Root1  0x151480 = d :  2
    callback Root1 :

*/ 
 







