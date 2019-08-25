
#include "../lib/tree.h"
#include "../lib/gc.h"
#include "../lib/stdio.h"

/*

    cl  lib\tree.c lib\gc.c lib\fs.c  test\ex_tree_1.c /Fex.exe   /WX   /EHsc 
    gcc lib\tree.c lib\gc.c lib\fs.c  test\ex_tree_1.c -o x.exe   -Wall -Wextra -pedantic
    gcc lib/tree.c lib/gc.c lib/fs.c  test/ex_tree_1.c -o x       -Wall -Wextra -pedantic

*/


void callbackRoot1 ( void* p ) 
{
    printf("\n callback :: tree Node Root1 : %p -> [%s].", p, (const char*) treeData(p)   ); 
}

int main(void)
{
    gcStart() ;
    
	// ------------------------------------------------------------------------------------ new

    //tree_t *root1 	= tree.new ( treeSingleKey ,treeOrdered,gcCompareStrC ) ; 

    treeType(root1);

    treeSingleOrderedNew(root1,gcComparepStrC);

	// ------------------------------------------------------------------------------------ insert	

    root1=tree.insert ( root1 , "a" ) ;	 
		  tree.insert ( root1 , "b" ) ;
		  tree.insert ( root1 , "b" ) ;     // <- single / multi key     
		  tree.insert ( root1 , "f" ) ;	   // <- ordered or not
		  tree.insert ( root1 , "g" ) ;	
		  tree.insert ( root1 , "c" ) ;
		  tree.insert ( root1 , "d" ) ;          

	// ------------------------------------------------------------------------------------ find
    
    tree_t 	*p=NULL;

    char *data = "c";

	p = tree.find( root1 , data	) ;
	
	if ( p  != NULL ) 	
		printf ( "\n\n TROVATO root1 : {%10s}  " , (const char*)data  ) ;	
	else				
		printf ( "\n\n NON trovato");

	// ------------------------------------------------------------------------------------ remove
    printf("\n\n [*] remove : %s ",data);
    root1 = tree.remove(root1, data);

    // ------------------------------------------------------------------------------------ iterator print
        
    printf ("\n----------------------------------\n" ) ;
    
    itTree(it) ;
    
    for ( treeBegin(it,root1) ; treeEnd(it) ; treeNext(it) ) 
    {
        printf("\n tree Node Root1, Min [[[%s]]] " ,   (const char*) itTreedata(it)    );  
          
    }    

	// ------------------------------------------------------------------------------------ tree NODE MAX	
	p=tree.Max(root1);
    
    printf("\n tree Node Root1, Max %s ",  (const char*)p->data   ); 

	// ------------------------------------------------------------------------------------ tree NODE MIN	
	p=tree.Min(root1);
    
    printf("\n tree Node Root1, Min %s ",  (const char*)p->data   ); 

	// ------------------------------------------------------------------------------------ tree HEIGHT	
    printf("\n tree Node Height %d Size %zu", tree.height(root1) , tree.size(root1)    ); 

	// ------------------------------------------------------------------------------------ inOrder	
	tree.inOrder( root1,callbackRoot1 ) ;


    printf ("\n----------------------------------\n" ) ;

    for ( treeBegin(it,root1) ; treeEnd(it) ; treeNext(it) ) 
    {
        printf("\n tree Node Root1, Min [[[%s]]] " ,   (const char*) itTreedata(it)    );  
      
    }
 
        
	// ------------------------------------------------------------------------------------ delete	

	tree.delete ( root1 ) ;

    printf ( "\n" );

    //
    
    gcStop();
        
    return 0;
}


/*

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
     tree Node Root1, Max e : 4
     tree Node Root1, Min a : 1
     tree Node Height 0 Size 4
     callback Root1 :  tree Node Root1  0x151410 = a :  1
     callback Root1 :  tree Node Root1  0x1514f0 = b :  5
     callback Root1 :  tree Node Root1  0x151480 = d :  2
     callback Root1 :

*/ 
 

