
#include "../lib/type.h"
#include "../lib/stdio.h"

/*

    cl  test\ex_types_1.c   /Fex.exe    /EHsc /WX
    gcc test\ex_types_1.c   -o x.exe    -Wall -Wextra -pedantic 
    gcc test/ex_types_1.c   -o x        -Wall -Wextra -pedantic  

*/

int main ( void )
{
    u8_t    uc  = u8MAX ;
    i8_t    sc  = i8MAX ;
    u16_t   u16 = u16MAX ;
    i16_t   i16 = i16MAX ;
    u32_t   u32 = u32MAX ;
    i32_t   i32 = i32MAX ;
    u64_t   u64 = u64MAX ;
    i64_t   i64 = i64MAX ;

    r32_t   f = r32MAX;
    r64_t   d = r64MAX;
    r80_t   ld =r80MAX ;

    u80_t   ull = u80MAX ;
    i80_t   ill = i80MAX ;

    size_t  z   = sizeMAX;

    c8_t c = 'a' ;

    printf ( $nl " byte 8  :: " $u8()  " " $i8()    ,uc,sc      ) ;
    printf ( $nl " byte 16 :: " $u16() " " $i16()   ,i16,u16    ) ;
    printf ( $nl " byte 32 :: " $u32() " " $i32()   ,i32,u32    ) ;

    printf ( $nl " byte 64 :: " $u64() " " $i64()   ,u64,i64    ) ;

    printf ( $nl " real 32 :: " $e32()              ,f          ) ;
    printf ( $nl " real 64 :: " $e64()              ,d          ) ;
    printf ( $nl " real 80 :: " $e80()              ,ld         ) ; 

    printf ( $nl " byte 80 :: " $u80()              ,ull        ) ;   
    printf ( $nl " byte 80 :: " $i80()              ,ill        ) ;   

    printf ( $nl " size_t :: " $z()                 ,z          );
    printf ( $nl " char   :: " $c8()                ,c          );

    printf ( $nl " i80+suffix " $i80() , _i80(123)  ) ;      //  printf ( "\n" "%" "lld" , 123llu ) ;
    printf ( $nl " r80+suffix " $r80() , _r80(1.2)  ) ;      //  printf ( "\n" "%" "Le"  , 456.789L ) ;
    printf ( $nl " s80+suffix " $i80() , _i80(-456) ) ;      //  printf ( "\n" "%" "lld" , -456ll ) ;
    
    printf ("\n");
    
 return 0 ;
}

/*

    C:\mc>x

     byte 8  :: 255 127
     byte 16 :: 32767 -1
     byte 32 :: 2147483647 -1
     byte 64 :: 4294967295 2147483647
     real 32 :: 3.402823e+038
     real 64 :: 1.797693e+308
     real 80 :: 1.189731e+4932
     byte 80 :: 18446744073709551615
     byte 80 :: 9223372036854775807
     size_t :: 18446744073709551615
     char   :: a
     i80+suffix 123
     r80+suffix 1.200000
     s80+suffix -456

    C:\mc>

*/















