
#include "../lib/gc.h"
#include "../lib/stdio.h"
#include "../lib/string.h"
#include <stdio.h>
#include <stdint.h>

/*

    cl  lib\gc.c lib\fs.c lib\string.c test\ex_string_1.c /Fex.exe   /WX /EHsc  
    gcc lib\gc.c lib\fs.c lib\string.c test\ex_string_1.c -o x.exe   -Wall -Wextra -pedantic
    gcc lib/gc.c lib/fs.c lib/string.c test/ex_string_1.c -o x       -Wall -Wextra -pedantic

*/


int main ( void )
{
    gcStart();

    /**/
 
    // ...................................................... stringType
    printf ("\n\n --- stringType(s1); \n");   
    stringType(s1);

    // ...................................................... stringNew
    printf ("\n\n --- stringNew(s1,128); \n");      
    stringNew(s1,128);
    
    printf ( "\nDEBUG [%d] [%s]",(int)strlen(str(s1)),str(s1) );

    // ...................................................... pushBack
    printf ("\n\n --- pushBack for ( int i=0;i<10;i++)\n");  
    for ( int i=0;i<10;i++)
    {
        stringPushBack( s1, (char)'a'+i );
        printf ( "[%c]",stringAt(s1,i) );
    }

    printf ( "\nDEBUG [%d] [%s]",(int)strlen(str(s1)),str(s1) );

    // ...................................................... popback
    printf ("\n\n ---stringPopBack(s1);\n"); 
    stringPopBack(s1);

    printf ( "\nDEBUG [%d] [%s]",(int)strlen(str(s1)),str(s1) );
    
    stringPushBack( s1, (char)'X' );    

    printf ( "\nDEBUG [%d] [%s]",(int)strlen(str(s1)),str(s1) );
    

    // ......................................................  size, capacity
    printf ( "\nsize %zu capacity %zu \n",stringSize(s1),stringCapacity(s1) );

    // ...................................................... iterator
    printf ("\n\n --- iterator\n");  
 
    iterator(s1) its1 ;

    printf ("\ns1:");     
    for ( its1=stringBegin(s1);its1!=stringEnd(s1);its1++)
    {
        printf ( "(%c)",*its1 );
    }        
    printf ("\ns1:");     
    for ( its1=stringRBegin(s1);its1!=stringREnd(s1);its1--)
    {
        printf ( "(%c)",*its1 );
    }    
 
    // ...................................................... shrinkToFit
    printf ("\n\n --- stringShrinkToFit(s1);\n"); 
    stringShrinkToFit(s1);
    printf ( "\nstringShrinkToFit(s1) size %zu capacity %zu \n",stringSize(s1),stringCapacity(s1) );
    for ( its1=stringBegin(s1);its1!=stringEnd(s1);its1++) printf ( "(%c)",*its1 );
    printf ( "\nDEBUG [%d] [%s]",(int)strlen(str(s1)),str(s1) );    
 
    // ......................................................  reserve
    printf ("\n\n --- stringReserve(s1,16);\n");
    stringReserve(s1,16);
    printf ( "\nstringReserve(s1,16) : size %zu capacity %zu \n",stringSize(s1),stringCapacity(s1) );
    for ( its1=stringBegin(s1);its1!=stringEnd(s1);its1++) printf ( "(%c)",*its1 );
    printf ( "\nDEBUG [%d] [%s]",(int)strlen(str(s1)),str(s1) );     
 
    // ......................................................  insert at val 
    printf ("\n\n --- stringInsertAtVal(s1,3,'x');\n");
    stringInsertAtVal(s1,3,'x');
    printf ( "\nstringInsertAtVal(s1,3,'x'); : size %zu capacity %zu \n",stringSize(s1),stringCapacity(s1) );
    for ( its1=stringBegin(s1);its1!=stringEnd(s1);its1++) printf ( "(%c)",*its1 );
    printf ( "\nDEBUG [%d] [%s]",(int)strlen(str(s1)),str(s1) );     

    // ...................................... erase at
    printf ("\n\n --- s1 tringEraseAt(s1,3);\n");  
    stringEraseAt(s1,3);
    printf ("\n");    
    for ( its1=stringBegin(s1);its1!=stringEnd(s1);its1++) printf ( "(%c)",*its1 );
    printf ( "\ns1 erase at 3 : size %zu capacity %zu \n",stringSize(s1),stringCapacity(s1) );
    printf ( "\nDEBUG [%d] [%s]",(int)strlen(str(s1)),str(s1) );      

    // ...................................... erase at N
    printf ("\n\n --- stringEraseAtN(s1,3,2);\n");  
    stringEraseAtN(s1,3,2);
    printf ("\n");    
    for ( its1=stringBegin(s1);its1!=stringEnd(s1);its1++) printf ( "(%c)",*its1 );
    printf ( "\ns1 erase at 3 x 2 : size %d capacity %d \n",(uint32_t)stringSize(s1),(uint32_t)stringCapacity(s1) );
    printf ( "\nDEBUG [%d] [%s]",(int)strlen(str(s1)),str(s1) );     
 
    // ...................................... resize
    printf ("\n\n --- stringResize(s1,20,'-');\n");  
    stringResize(s1,20,'-');
    printf ("\n");    
    for ( its1=stringBegin(s1);its1!=stringEnd(s1);its1++) printf ( "(%c)",*its1 );
    printf ( "\nv : size %d capacity %d \n",(uint32_t)stringSize(s1),(uint32_t)stringCapacity(s1) );
    printf ( "\nDEBUG [%d] [%s]",(int)strlen(str(s1)),str(s1) );     

    printf ("\n\n --- stringResize(s1,12,'-');\n"); 
    stringResize(s1,12,'-');
    printf ("\n");    
    for ( its1=stringBegin(s1);its1!=stringEnd(s1);its1++) printf ( "(%c)",*its1 );
    printf ( "\ns1 : size %zu capacity %zu \n",stringSize(s1),stringCapacity(s1) );
    printf ( "\nDEBUG [%d] [%s]",(int)strlen(str(s1)),str(s1) );     
 
    // ...................................... copy
    printf ("\n\n --- stringCopy(s2,s1 );\n")

    stringType(s2) ;
    stringNew(s2,128);  
  
    stringCopy(s2,s1 );
    printf ("\n");
    iterator(s2) its2 ; 

    for ( its2=stringBegin(s2);its2!=stringEnd(s2);its2++) printf ( "(%c)",*its2 );
    printf ( "\ns2 : size %zu capacity %zu \n",stringSize(s2),stringCapacity(s2) );
    printf ( "\nDEBUG s2 [%d] [%s]",(int)strlen(str(s2)),str(s2) );   
     
    // ...................................... append
    printf ("\n\n --- stringType(s3) ;\n") ;
    printf ("\n\n --- stringAppend(s3,s1 );\n")

    stringType(s3) ;
    //stringNew(s2,128);    
    stringAppend(s3,s1 );
    printf ("\n");
    iterator(s3) its3 ;    
    for ( its3=stringBegin(s3);its3!=stringEnd(s3);its3++) printf ( "(%c)",*its3 );
    printf ( "\ns3 : size %d capacity %d \n",(uint32_t)stringSize(s3),(uint32_t)stringCapacity(s3) );
    printf ( "\nDEBUG s3 [%d] [%s]",(int)strlen(str(s3)),str(s3) );   
 
    // ...................................... insert string at
    printf ("\n\n --- stringType(s3) ;\n") ;

    stringInsertAtString(s3, 9 , s1 ); // dal 10 in poi ( 0-9 )
    printf ("\n");
    for ( its3=stringBegin(s3);its3!=stringEnd(s3);its3++) printf ( "(%c)",*its3 );
    printf ( "\ns3 : size %d capacity %d \n",(uint32_t)stringSize(s3),(uint32_t)stringCapacity(s3) );
    printf ( "\nDEBUG s3 [%d] [%s]",(int)strlen(str(s3)),str(s3) ); 
    
    // ...................................... stringInsertAtstringFromN(v1, POS1, v2 , POS2 , N)
    stringInsertAtStringFromN(s1, 2, s2 , 2 , 5 );
    printf ("\n");
    for ( its1=stringBegin(s1);its1!=stringEnd(s1);its1++) printf ( "(%c)",*its1 );
    printf ( "\ns1 : size %zu capacity %zu \n",stringSize(s1),stringCapacity(s1) );
    printf ( "\nDEBUG s1 [%d] [%s]",(int)strlen(str(s1)),str(s1) );  

    /* 
        s1 = (a)(b) *** (c)(f)(g)(h)(i)(X)(-)(-)(-)(-)
        s3 = (a)(b) [[[ (c)(f)(g)(h)(i) ]]] (X)(-)(-)(-)(-)
        s3 = (a)(b) ... (c)(f)(g)(h)(i) ... (c)(f)(g)(h)(i)(X)(-)(-)(-)(-)
    */
    
    // ...................................... front back   
    printf ( "\n front [%c] , back [%c] ",stringFront(s3),stringBack(s3) );
   
    /**/

//    stringFree(s1);

    //stringFree(s2);
    //stringFree(s3);

    /**/

    gcStop();

    printf ("\n");
    return 0 ;
}
    
