
#include "../lib/singleList.h"

/*
    cl  lib\singleList.c lib\gc.c  lib/fs.c test\ex_singleList_1.c /Fex.exe /EHsc
    gcc lib\singleList.c lib\gc.c  lib/fs.c test\ex_singleList_1.c -o x.exe
    gcc lib/singleList.c lib/gc.c  lib/fs.c test/ex_singleList_1.c -o x
*/

int main()
{
    gcStart();

    //

    singleListType(singleList);
 
    //  ................................................. empty
    printf ("\n ... empty ");   
      
    printf ( "\n ? %d\n", singleListEmpty(singleList) );
    
    singleListNew(singleList,gcCompareStrC);
 
    //  ................................................. push back

    printf ("\n ... pushBack ");  
    
    singleListPushBack(singleList, gcStrDup ("a") );
    singleListPushBack(singleList, gcStrDup ("e") );
    singleListPushBack(singleList, gcStrDup ("f") );

    singleListDisplay(singleList, "(%s)",(char*) );

    printf ( "\nsize::[%d]\n",(int)singleListSize(singleList) );
 
    //  ................................................. push front

    printf ("\n ... pushFront ");
    
    singleListPushFront(singleList, gcStrDup ("b") );
    singleListPushFront(singleList, gcStrDup ("c") );
  
    singleListDisplay(singleList, "(%s)",(char*) );  

    //  ................................................. insert 

    printf ("\n ... InsertAfter ");  
    
    singleListInsertAfter (singleList, gcStrDup ("e"), gcStrDup ("e_") ); 
    
    printf ("\n ... InsertBefore ");  
    
    singleListInsertBefore(singleList, gcStrDup ("e"), gcStrDup ("_e") );
    
    singleListDisplay(singleList, "(%s)",(char*) ); 

    //  ................................................. remove 

    printf ("\n ... remove ");  
    
    singleListRemove(singleList, gcStrDup("b") );
    
    singleListDisplay(singleList, "(%s)",(char*) ); 

    //  ................................................. remove after

    printf ("\n ... remove after ");
    
    singleListRemoveAfter(singleList, gcStrDup("e") );

    //  ................................................. remove before

    printf ("\n ... remove before ");  
    
    singleList = singleListRemoveBefore(singleList, gcStrDup("e") );
    
    singleListDisplay(singleList, "(%s)",(char*) ); 
 
    //  ................................................. reverse

    printf ("\n ... reverse ");    
    
    singleListReverse(singleList);
  
    singleListDisplay(singleList, "(%s)",(char*) ); 

    //  ................................................. front back
    
    printf ("\n ... front back ");  
    
    printf ( "\nfront %s",(char*) (singleListFront(singleList))->data );
    printf ( "\nback  %s",(char*) (singleListBack (singleList))->data );
    printf ( "\nempty %d", singleListEmpty(singleList) );
 
    //  ................................................. iterator
   
    itSingleList(it);
    
    printf ("\n ... iterator ");
    for ( it=singleListBegin(singleList) ; it != singleListEnd(); it = singleListNext(it)  )
    {
        printf ( "{%s}",(char*)it->data) ;
    }

    //  ................................................. sort
 
    printf ("\n ... sort "); ;  
    
    singleListSort(singleList);
    
    printf ( ""); ;    
    for ( singleList_t it=singleListBegin(singleList) ; it != singleListEnd(); it = singleListNext(it)  )
    {
        printf ( " {%s}",(char*)it->data) ;
    }  
 
    //  ................................................. front back

    printf ("\n ... pop Front Back");  
    
    singleListPopFront(singleList);

    singleListPopBack(singleList);
    
    printf ("\n ... front back "); ; 
    
    for ( singleList_t it=singleListBegin(singleList) ; it != singleListEnd(); it = singleListNext(it)  )
    {
        printf ( "{%s}",(char*)it->data) ;
    }    
 
    //  ................................................. singleList splice

    printf ("\n ... splice "); ;
    
    singleList_t splice = NULL ;
    
    singleListPushBack(singleList , gcStrDup("1") ) ;
    singleListPushBack(singleList , gcStrDup("2") ) ;

    printf ("\n ... SPLICE before : singleList .") ;
    for ( singleList_t it=singleListBegin(singleList) ; it != singleListEnd(); it = singleListNext(it)  )
    {
        printf ( "{%s}",(char*)it->data) ;
    } 
    
    splice = singleListSplice ( singleList,1,2 ); 
    
    printf ("\n ... SPLICE after  : splice     .") ;
    for ( singleList_t it=singleListBegin(splice) ; it != singleListEnd(); it = singleListNext(it)  )
    {
        printf ( "{%s}",(char*)it->data) ;
    } 

    //  ................................................. singleList copy

    printf ("\n ... copy ");  
    
    singleList_t copy = NULL ;
    
    copy = singleListCopy ( singleList ); 
    
    for ( singleList_t it=singleListBegin(copy) ; it != singleListEnd(); it = singleListNext(it)  )
    {
        printf ( "{%s}",(char*)it->data) ;
    } 

    //  ................................................. singleList append
    printf ("\n ... append ");  

    singleListAppend(copy,singleList );
    
    for ( singleList_t it=singleListBegin(copy) ; it != singleListEnd(); it = singleListNext(it)  )
    {
        printf ( "{%s}",(char*)it->data) ;
    }        

    //  ................................................. find
    printf ("\n ... find "); 

    printf ("\n ... e  ? [%p]. ",singleListFind(copy,gcStrDup("e") ) ); 
    
    //  ................................................. free
   
    singleListFree(singleList);

    //

    gcStop();
    printf("");
    return 0;
}



/**/

