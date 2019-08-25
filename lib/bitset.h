
#ifndef cdBitSet
#define cdBitSet

    #ifdef __linux__
    #define _GNU_SOURCE 
    #endif

    #include <stdint.h>
    #include <assert.h>

    // ***    
    // bit
    // ***
    
    // ................................................................ BIT OP

    // a=target variable, b=bit number to act upon 0-n

    #define bitSet(a,b)     (   (a) |=  (1ULL<<(b))  )
    #define bitGet(a,b)     (!!((a) &   (1ULL<<(b))  ))
    #define bitClear(a,b)   (   (a) &= ~(1ULL<<(b))  )
    #define bitFlip(a,b)    (   (a) ^=  (1ULL<<(b))  )

    // ................................................................ BIT MASK OP

    // x=target variable, y=mask

    #define bitMaskSet(x,y)        (  (x) |=   (y)          )
    #define bitMaskGet(x,y)        ( ((x) &    (y) ) == (y) )
    #define bitMaskClear(x,y)      (  (x) &= (~(y) )        )
    #define bitMaskFlip(x,y)       (  (x) ^=   (y)          )

    // ................................................................ BYTE GET

    #define byteGet(X,N)  (((x>>(N-1)*8))&0xff)

    // ................................................................ BYTE SET

    #define byteSet(X,NDX,V) (((unsigned char*)&X)[NDX]=(unsigned char)V)

    // ................................................................ field SET

    // https://www.coranac.com/documents/working-with-bits-and-bitfields/

    #define BIT(n)                  ( 1<<(n) )

    //! Create a bitmask of length  len.
    #define BIT_MASK(len)           ( BIT(len)-1 )

    //! Create a bitfield mask of length  starting at bit  start.
    #define BF_MASK(start, len)     ( BIT_MASK(len)<<(start) )

    //! Prepare a bitmask for insertion or combining.
    #define BF_PREP(x, start, len)  ( ((x)&BIT_MASK(len)) << (start) )

    //! Extract a bitfield of length  len starting at bit  start from  y.
    #define BF_GET(y, start, len)   ( ((y)>>(start)) & BIT_MASK(len) )

    //! Insert a new bitfield value  x into  y.
    #define BF_SET(y, x, start, len)    \
        ( y= ((y) &~ BF_MASK(start, len)) | BF_PREP(x, start, len) )

    #define bitFieldSet BF_SET
    #define bitFieldGet BF_GET
    
    // ****    
    // real
    // ****

    // ............................................................. LITTLE/BIG ENDIAN ?

    #ifdef _MSC_VER

        #include <Windows.h>

        #if REG_DWORD == REG_DWORD_LITTLE_ENDIAN    
            #define LITTLE_ENDIAN
            #undef  BIG_ENDIAN
        #else
            #define BIG_ENDIAN
            #undef  LITTLE_ENDIAN
        #endif   

    #endif

    #ifdef __GNUC__

         #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__   
            #define LITTLE_ENDIAN
            #undef  BIG_ENDIAN
        #else
            #define BIG_ENDIAN
            #undef  LITTLE_ENDIAN
        #endif   

    #endif

    // ............................................................. float 

    union ieee754_float
    {
        float real;

        // This is the IEEE 754 single-precision format.  
        struct
        {
            #ifdef	BIG_ENDIAN
            unsigned int negative:1;
            unsigned int exponent:8;
            unsigned int mantissa:23;
            #endif	// Big endian. 

            #ifdef LITTLE_ENDIAN
            unsigned int mantissa:23;
            unsigned int exponent:8;
            unsigned int negative:1;
            #endif	// Little endian.  
        } ieee;

        // This format makes it easier to see if a NaN is a signalling NaN.  
        struct
        {
            #ifdef BIG_ENDIAN
            unsigned int negative:1;
            unsigned int exponent:8;
            unsigned int quiet_nan:1;
            unsigned int mantissa:22;
            #endif 

            #ifdef	LITTLE_ENDIAN
            unsigned int mantissa:22;
            unsigned int quiet_nan:1;
            unsigned int exponent:8;
            unsigned int negative:1;
            #endif 
        } ieee_nan;

    };

    // Added to exponent. 
    #define IEEE754_FLOAT_BIAS	0x7f 

    // ................................................................................ double

    union ieee754_double
    {
        double real;

        // This is the IEEE 754 double-precision format.  
        struct
        {
            #ifdef	BIG_ENDIAN
                unsigned int negative:1;
                unsigned int exponent:11;
                // Together these comprise the mantissa.  
                unsigned int mantissa0:20;
                unsigned int mantissa1:32;
            #endif

            #ifdef	LITTLE_ENDIAN
                #ifdef _MSC_VER
                    unsigned int mantissa1:32;
                    unsigned int mantissa0:20;
                    unsigned int exponent:11;
                    unsigned int negative:1;  
                #else
                    # if	__FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__
                    unsigned int mantissa0:20;
                    unsigned int exponent:11;
                    unsigned int negative:1;
                    unsigned int mantissa1:32;
                    # else
                    // Together these comprise the mantissa.  
                    unsigned int mantissa1:32;
                    unsigned int mantissa0:20;
                    unsigned int exponent:11;
                    unsigned int negative:1;
                    # endif
                #endif
            #endif
        } ieee;

        // This format makes it easier to see if a NaN is a signalling NaN.  
        struct
        {
            #ifdef	BIG_ENDIAN
                unsigned int negative:1;
                unsigned int exponent:11;
                unsigned int quiet_nan:1;
                // Together these comprise the mantissa.  
                unsigned int mantissa0:19;
                unsigned int mantissa1:32;
            #else
                #ifdef _MSC_VER
                    unsigned int mantissa1:32;
                    unsigned int mantissa0:19;
                    unsigned int quiet_nan:1;
                    unsigned int exponent:11;
                    unsigned int negative:1;
                #else
                    # if	__FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__
                    unsigned int mantissa0:19;
                    unsigned int quiet_nan:1;
                    unsigned int exponent:11;
                    unsigned int negative:1;
                    unsigned int mantissa1:32;
                    # else
                    // Together these comprise the mantissa.  
                    unsigned int mantissa1:32;
                    unsigned int mantissa0:19;
                    unsigned int quiet_nan:1;
                    unsigned int exponent:11;
                    unsigned int negative:1;
                    # endif
                #endif
            #endif
        } ieee_nan;

    };

    #define IEEE754_DOUBLE_BIAS	0x3ff // Added to exponent.  

    // ................................................................................ long double

    union ieee854_long_double
    {
        long double real;

        // This is the IEEE 854 double-extended-precision format.  
        struct
        {
            #ifdef	BIG_ENDIAN
                unsigned int negative:1;
                unsigned int exponent:15;
                unsigned int empty:16;
                unsigned int mantissa0:32;
                unsigned int mantissa1:32;
            #endif

            #ifdef	LITTLE_ENDIAN
                #ifdef _MSC_VER
                    unsigned int mantissa1:32;
                    unsigned int mantissa0:32;
                    unsigned int exponent:15;
                    unsigned int negative:1;
                    unsigned int empty:16;                
                #else
                    # if	__FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__
                    unsigned int exponent:15;
                    unsigned int negative:1;
                    unsigned int empty:16;
                    unsigned int mantissa0:32;
                    unsigned int mantissa1:32;
                    # else
                    unsigned int mantissa1:32;
                    unsigned int mantissa0:32;
                    unsigned int exponent:15;
                    unsigned int negative:1;
                    unsigned int empty:16;
                    # endif
                #endif
            #endif
        } ieee;

        // This is for NaNs in the IEEE 854 double-extended-precision format.  
        struct
        {
            #ifdef	BIG_ENDIAN
                unsigned int negative:1;
                unsigned int exponent:15;
                unsigned int empty:16;
                unsigned int one:1;
                unsigned int quiet_nan:1;
                unsigned int mantissa0:30;
                unsigned int mantissa1:32;
            #endif

            #ifdef	LITTLE_ENDIAN
                #ifdef _MSC_VER
                    unsigned int mantissa1:32;
                    unsigned int mantissa0:30;
                    unsigned int quiet_nan:1;
                    unsigned int one:1;
                    unsigned int exponent:15;
                    unsigned int negative:1;
                    unsigned int empty:16;                
                #else
                    # if	__FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__
                    unsigned int exponent:15;
                    unsigned int negative:1;
                    unsigned int empty:16;
                    unsigned int mantissa0:30;
                    unsigned int quiet_nan:1;
                    unsigned int one:1;
                    unsigned int mantissa1:32;
                    # else
                    unsigned int mantissa1:32;
                    unsigned int mantissa0:30;
                    unsigned int quiet_nan:1;
                    unsigned int one:1;
                    unsigned int exponent:15;
                    unsigned int negative:1;
                    unsigned int empty:16;
                    # endif
                #endif
            #endif
            } ieee_nan;
        };

    #define IEEE854_LONG_DOUBLE_BIAS 0x3fff

    // ................................................................................ type

    typedef union ieee754_float         real32_t    ;
    typedef union ieee754_double        real64_t    ;
    #ifdef _MSC_VER
    typedef union ieee754_double        real80_t    ;
    #else
    typedef union ieee854_long_double   real80_t    ;
    #endif
    
    #define real32s(x) x.ieee.negative
    #define real32n(x) x.ieee.negative
    #define real32e(x) x.ieee.exponent
    #define real32m(x) x.ieee.mantissa

    #define real64s(x)  x.ieee.negative
    #define real64n(x)  x.ieee.negative
    #define real64e(x)  x.ieee.exponent
    #define real64m0(x) x.ieee.mantissa0
    #define real64m1(x) x.ieee.mantissa1

    
    #define real80s(x)  x.ieee.negative
    #define real80n(x)  x.ieee.negative
    #define real80e(x)  x.ieee.exponent
    #define real80m0(x) x.ieee.mantissa0
    #define real80m1(x) x.ieee.mantissa1

    #ifdef _MSC_VER

    // ................................................................................ byte swap
        
    #define byteSwap_u16(X) _byteswap_ushort(X)
    #define byteSwap_u32(X) _byteswap_ulong(X)
    #define byteSwap_u64(X) _byteswap_uint64(X) 

    #endif

    #ifdef __GNUC__

    #define byteSwap_u16(X) (uint16_t)((uint16_t)((X & 0xff) << 8) | ((X >> 8) & 0xff))
    #define byteSwap_u32(X) __builtin_bswap32(X)
    #define byteSwap_u64(X) __builtin_bswap64(X) 


#endif

    // ................................................................................ END

#endif


/**/


