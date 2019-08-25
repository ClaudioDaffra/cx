
#include <stdio.h>
#include "../lib/bitset.h"
#include "../lib/type.h"

/*
    cl  test\ex_bitset_1.c  /Fex.exe    /WX /EHsc 
    gcc test\ex_bitset_1.c  -o x.exe    -Wall -Wextra -pedantic
    gcc test/ex_bitset_1.c  -o x        -Wall -Wextra -pedantic    
*/


int main ( void )
{
    struct
    {
        union
        {
            struct 
            {
                unsigned a          : 4 ; // 0123
                unsigned unused0    : 1 ; // 4
                unsigned c          : 3 ; // 567
            } al ;
            uint8_t ah ;
        } ;
        
    } b ;

    // -----------------------------

    b.ah = 0x00 ;

    // -----------------------------    

    printf ( "\n%d",b.al.unused0 );                 // 0

    bitSet  (b.al.unused0,0); 
    bitClear(b.al.unused0,0); 
    bitFlip (b.al.unused0,0);  

    printf ( "\n%d",bitGet(b.al.unused0,0) );       // 1

    // -----------------------------

    printf ( "\n%d",b.al.c );                       // 0

    bitSet(b.al.c,2);   

    printf ( "\n%d",bitGet(b.al.c,2) );             // 1

    // -----------------------------

    uint32_t x = 0x12345678 ;

    printf ("\n");
    printf ( "\n%x"  , byteGet(x,4)    ) ;
    printf ( "\n%x"  , byteGet(x,3)    ) ;
    printf ( "\n%x"  , byteGet(x,2)    ) ;
    printf ( "\n%x"  , byteGet(x,1)    ) ;

    // -----------------------------

    byteSet ( x,2,0xcc ) ;

    printf ("\n");
    printf ( "\n%x"  , byteGet(x,4)    ) ;
    printf ( "\n%x"  , byteGet(x,3)    ) ;
    printf ( "\n%x"  , byteGet(x,2)    ) ;
    printf ( "\n%x"  , byteGet(x,1)    ) ;

    // -----------------------------

    #define LOG_NO_ERRORS         0  // 0 no ERRORS
    #define LOG_ERRORS            1  // 2^0, bit 0
    #define LOG_WARNINGS          2  // 2^1, bit 1
    #define LOG_NOTICES           4  // 2^2, bit 2
    #define LOG_INCOMING          8  // 2^3, bit 3
    #define LOG_OUTGOING         16  // 2^4, bit 4
    #define LOG_LOOPBACK         32  // and so on...

    unsigned f ; // FLAGS

    f = LOG_NO_ERRORS ;     // no error

    bitMaskSet ( f , LOG_ERRORS ) ;
    bitMaskSet ( f , LOG_NOTICES ) ;    
    bitMaskSet ( f , LOG_OUTGOING ) ; 

    // 1
    // 0
    // 1
    // 0

    printf ("\n");

    printf ( "\n LOG ERRORS     ? %u ",bitMaskGet( f , LOG_ERRORS    ) );
    printf ( "\n LOG_LOOPBACK   ? %u ",bitMaskGet( f , LOG_LOOPBACK  ) );

    printf ( "\n LOG_ERRORS && LOG_OUTGOING   ? %u ", bitMaskGet( f , LOG_ERRORS|LOG_OUTGOING  ) );  
    printf ( "\n LOG_ERRORS && LOG_WARNINGS   ? %u ", bitMaskGet( f , LOG_ERRORS|LOG_WARNINGS  ) );    

    // 1
    // 1
    // 0
    // 1

    printf ("\n");

    bitMaskClear(f,LOG_OUTGOING);
    bitMaskFlip (f,LOG_LOOPBACK);

    printf ( "\n LOG ERRORS     ? %u ",bitMaskGet( f , LOG_ERRORS    ) );
    printf ( "\n LOG_LOOPBACK   ? %u ",bitMaskGet( f , LOG_LOOPBACK  ) );

    printf ( "\n LOG_ERRORS && LOG_OUTGOING   ? %u ", bitMaskGet( f , LOG_ERRORS|LOG_OUTGOING  ) );  
    printf ( "\n LOG_ERRORS && LOG_WARNINGS   ? %u ", bitMaskGet( f , LOG_ERRORS|LOG_WARNINGS  ) );    

    // field set

    uint32_t x2 = 0x00000000 ;

    bitFieldSet(x2,0xAB,0,16 ) ;

    printf ( "\n {%x} " , bitFieldGet(x2,0,16) ) ;

    // byte swap

    printf ( "\n" ) ;

    uint64_t   u64 = 0x0102030405060708;
    uint32_t   u32 = 0x01020304;
    uint16_t   u16 = 0xabcd ;

    printf("\n byteSwap of "$x64()" = "$x64()   , (uint64_t)u64   , (uint64_t)byteSwap_u64(u64)  );
    printf("\n byteSwap of "$x32()" = "$x32()   , u32   , byteSwap_u32(u32)  );
    printf("\n byteSwap of "$x16()" = "$x16()   , u16   , byteSwap_u16(u16)  );   

    //
    
    printf ( "\n" ); 
    return 0 ;
}
