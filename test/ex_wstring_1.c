
#include "../lib/gc.h"
#include "../lib/wstring.h"
#include <stdio.h>
#include <stdint.h>

/*
 
    cl  lib\gc.c  lib\fs.c lib\wstring.c test\ex_wstring_1.c /Fex.exe /WX    /EHsc  
    gcc lib\gc.c  lib\fs.c lib\wstring.c test\ex_wstring_1.c -o x.exe -Wall -Wextra -pedantic
    gcc lib/gc.c  lib/fs.c lib/wstring.c test/ex_wstring_1.c -o x     -Wall -Wextra -pedantic

*/

int main ( void )
{
    gcStart();

    /**/
 
    // ...................................................... wstringType
    wprintf (L"\n\n --- wstringType(s1); \n");   
    wstringType(s1);
 
    // ...................................................... wstringNew
    wprintf (L"\n\n --- wstringNew(s1,128); \n");      
    wstringNew(s1,128);

    wprintf ( L"\nDEBUG [%d] [%ls]",(int)wcslen(wstr(s1)),wstr(s1) );
        
    // ...................................................... pushBack
    wprintf (L"\n\n --- pushBack for ( int i=0;i<10;i++) \n");  
    for ( int i=0;i<10;i++)
    {
        wstringPushBack( s1, (wchar_t)'a'+i );
        wprintf ( L"[%lc]",wstringAt(s1,i) );
    }
    
    wprintf ( L"\nDEBUG [%d] [%ls]",(int)wcslen(wstr(s1)),wstr(s1) );    
  
    // ...................................................... popback
    wprintf (L"\n\n ---wstringPopBack(s1);\n"); 
    wstringPopBack(s1);

    wprintf ( L"\nDEBUG [%d] [%ls]",(int)wcslen(wstr(s1)),wstr(s1) ); 
    
    wstringPushBack( s1, (wchar_t)L'X' );    

    wprintf ( L"\nDEBUG [%d] [%ls]",(int)wcslen(wstr(s1)),wstr(s1) );    

    // ......................................................  size, capacity
    wprintf (L"\nsize %zu capacity %zu \n",wstringSize(s1),wstringCapacity(s1) );
 
    // ...................................................... iterator
    wprintf (L"\n\n --- iterator\n");  
 
    iterator(s1) its1 ;

    wprintf (L"\ns1:");     
    for ( its1=wstringBegin(s1);its1!=wstringEnd(s1);its1++)
    {
        wprintf ( L"(%lc)",*its1 );
    }        
    wprintf (L"\ns1:");     
    for ( its1=wstringRBegin(s1);its1!=wstringREnd(s1);its1--)
    {
        wprintf ( L"(%lc)",*its1 );
    }    

    // ...................................................... shrinkToFit
    wprintf (L"\n\n --- wstringShrinkToFit(s1);\n"); 
    wstringShrinkToFit(s1);
    wprintf ( L"\nwstringShrinkToFit(s1) size %zu capacity %zu \n",wstringSize(s1),wstringCapacity(s1) );
    for ( its1=wstringBegin(s1);its1!=wstringEnd(s1);its1++) wprintf ( L"(%lc)",*its1 );
    wprintf ( L"\nDEBUG [%d] [%ls]",(int)wcslen(wstr(s1)),wstr(s1) );     

    // ......................................................  reserve
    wprintf (L"\n\n --- wstringReserve(s1,16);\n");
    wstringReserve(s1,16);
    wprintf ( L"\nwstringReserve(s1,16) : size %zu capacity %zu \n",wstringSize(s1),wstringCapacity(s1) );
    for ( its1=wstringBegin(s1);its1!=wstringEnd(s1);its1++) wprintf ( L"(%lc)",*its1 );
    wprintf ( L"\nDEBUG [%d] [%ls]",(int)wcslen(wstr(s1)),wstr(s1) );      

    // ......................................................  insert at val 
    wprintf (L"\n\n --- wstringInsertAtVal(s1,3,'x');\n");
    wstringInsertAtVal(s1,3,L'x');
    wprintf ( L"\nwstringInsertAtVal(s1,3,'x'); : size %zu capacity %zu \n",wstringSize(s1),wstringCapacity(s1) );
    for ( its1=wstringBegin(s1);its1!=wstringEnd(s1);its1++) wprintf ( L"(%lc)",*its1 );
    wprintf ( L"\nDEBUG [%d] [%ls]",(int)wcslen(wstr(s1)),wstr(s1) );        
 
    // ...................................... erase at
    wprintf (L"\n\n --- s1 tringEraseAt(s1,3);\n");  
    wstringEraseAt(s1,3);
    wprintf (L"\n");    
    for ( its1=wstringBegin(s1);its1!=wstringEnd(s1);its1++) wprintf ( L"(%lc)",*its1 );
    wprintf ( L"\ns1 erase at 3 : size %zu capacity %zu \n",wstringSize(s1),wstringCapacity(s1) );
    wprintf ( L"\nDEBUG [%d] [%ls]",(int)wcslen(wstr(s1)),wstr(s1) );     

    // ...................................... erase at N
    wprintf (L"\n\n --- wstringEraseAtN(s1,3,2);\n");  
    wstringEraseAtN(s1,3,2);
    wprintf (L"\n");    
    for ( its1=wstringBegin(s1);its1!=wstringEnd(s1);its1++) wprintf ( L"(%lc)",*its1 );
    wprintf ( L"\ns1 erase at 3 x 2 : size %zu capacity %zu \n",wstringSize(s1),wstringCapacity(s1) );
    wprintf ( L"\nDEBUG [%d] [%ls]",(int)wcslen(wstr(s1)),wstr(s1) );       

    // ...................................... resize
    wprintf (L"\n\n --- wstringResize(s1,20,'-');\n");  
    wstringResize(s1,20,'-');
    wprintf (L"\n");    
    for ( its1=wstringBegin(s1);its1!=wstringEnd(s1);its1++) wprintf ( L"(%lc)",*its1 );
    wprintf ( L"\nv : size %zu capacity %zu \n",wstringSize(s1),wstringCapacity(s1) );
    wprintf ( L"\nDEBUG [%d] [%ls]",(int)wcslen(wstr(s1)),wstr(s1) );      
 
    wprintf (L"\n\n --- wstringResize(s1,12,'-');\n"); 
    wstringResize(s1,12,'-');
    wprintf (L"\n");    
    for ( its1=wstringBegin(s1);its1!=wstringEnd(s1);its1++) wprintf ( L"(%lc)",*its1 );
    wprintf ( L"\ns1 : size %zu capacity %zu \n",wstringSize(s1),wstringCapacity(s1) );
    wprintf ( L"\nDEBUG [%d] [%ls]",(int)wcslen(wstr(s1)),wstr(s1) );    
 
    // ...................................... copy
    wprintf (L"\n\n --- wstringCopy(s2,s1 );\n")

    wstringType(s2) ;
    wstringNew(s2,128);  
  
    wstringCopy(s2,s1 );
    wprintf (L"\n");
    iterator(s2) its2 ; 

    for ( its2=wstringBegin(s2);its2!=wstringEnd(s2);its2++) wprintf ( L"(%lc)",*its2 );
    wprintf ( L"\ns2 : size %zu capacity %zu \n",wstringSize(s2),wstringCapacity(s2) );
    wprintf ( L"\nDEBUG s2 [%d] [%ls]",(int)wcslen(wstr(s1)),wstr(s1) );    
 
    // ...................................... append
    wprintf (L"\n\n --- wstringType(s3) ;\n") ;
    wprintf (L"\n\n --- wstringAppend(s3,s1 );\n")

    wstringType(s3) ;
    //wstringNew(s2,128);    
    wstringAppend(s3,s1 );
    wprintf (L"\n");
    iterator(s3) its3 ;    
    for ( its3=wstringBegin(s3);its3!=wstringEnd(s3);its3++) wprintf ( L"(%lc)",*its3 );
    wprintf ( L"\ns3 : size %zu capacity %zu \n",wstringSize(s3),wstringCapacity(s3) );
    wprintf ( L"\nDEBUG s3 [%d] [%ls]",(int)wcslen(wstr(s1)),wstr(s1) );      
 
    // ...................................... insert wstring at
    wprintf (L"\n\n --- wstringType(s3) ;\n") ;

    wstringInsertAtwstring(s3, 9 , s1 );
    wprintf (L"\n");
    for ( its3=wstringBegin(s3);its3!=wstringEnd(s3);its3++) wprintf ( L"(%lc)",*its3 );
    wprintf ( L"\ns3 : size %zu capacity %zu \n",wstringSize(s3),wstringCapacity(s3) );
 
    // ...................................... wstringInsertAtwstringFromN(v1, POS1, v2 , POS2 , N)
    wstringInsertAtwstringFromN(s1, 2, s2 , 2 , 5 );
    wprintf (L"\n");
    for ( its1=wstringBegin(s1);its1!=wstringEnd(s1);its1++) wprintf ( L"(%lc)",*its1 );
    wprintf ( L"\ns1 : size %zu capacity %zu \n",wstringSize(s1),wstringCapacity(s1) );
 
    /* 
        s1 = (a)(b) *** (c)(f)(g)(h)(i)(X)(-)(-)(-)(-)
        s3 = (a)(b) [[[ (c)(f)(g)(h)(i) ]]] (X)(-)(-)(-)(-)
        s3 = (a)(b) ... (c)(f)(g)(h)(i) ... (c)(f)(g)(h)(i)(X)(-)(-)(-)(-)
    */
    
    // ...................................... front back   
    wprintf ( L"\n front [%lc] , back [%lc] ",wstringFront(s3),wstringBack(s3) );
    
    wstringFree(s1);
    //wstringFree(s2);
    //wstringFree(s3);
 
    /**/

    gcStop();

    wprintf (L"\n");
    return 0 ;
}
    
