
#include "../lib/singleList.h"

/*
    cl  lib\singleList.c lib\gc.c  lib\fs.c test\ex_singleList_2.c /Fex.exe /EHsc
    gcc lib\singleList.c lib\gc.c  lib\fs.c test\ex_singleList_2.c -o x.exe
    gcc lib/singleList.c lib/gc.c  lib/fs.c test/ex_singleList_2.c -o x

*/

int main()
{
    gcStart();

    //

    singleListType(singleList);
    
 
    singleListNew(singleList,gcCompareInt);
    
    
    int a=1,b=3,c=2;


    singleListPushBack(singleList,&a) ;
    singleListPushBack(singleList,&b) ;
    singleListPushBack(singleList,&c) ;

    singleListDisplay(singleList, "(%d)",*(int*) );
    
    singleListSort(singleList);

    singleListDisplay(singleList, "(%d)",*(int*) );
    
    //

    gcStop();
    printf("\n");
    return 0;
}

/*


*/



