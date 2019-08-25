
/*

    g++ demo\d_vector_1.cpp -o xpp.exe      -Wall -Wextra -pedantic -O3
    g++ demo/d_vector_1.cpp -o xpp          -Wall -Wextra -pedantic -O3

*/

#include <vector>
#include <stdio.h>

/*
    055 054 052 std::vector
    021 020 020 mvector
    38% faster
*/


int main ( void )
{
    std::vector<int> v ;
    

    int ITERATION_MAX       = 10 * 1000 * 1000;
    int countErase          = 0 ;

    int i ;
    for (  i=0; i<ITERATION_MAX; i++ )
    {

        v.push_back(i);
 
        if ( ++countErase>10 )  v.erase (v.begin()+0);
 
        if ( ++countErase>20 )  v.insert(v.begin()+0,i);
 
        if (    ITERATION_MAX > 25 )   countErase = 0 ; 
 
    }

     printf ( "\n %d ",i ) ;   
    return 0 ;
}
