
#ifndef xoop
#define xoop

    #if defined(__MINGW32__) || defined(__MINGW64__) || defined(__GNUC__)
        #pragma GCC diagnostic ignored "-Wunused-variable"
        #pragma GCC diagnostic ignored "-Wunused-parameter"
    #endif

    #include <stdio.h>
    #include <stdlib.h>
    #include <stdarg.h>
    #include <string.h>

    /**
    
        obj_t   :   struttura dati
        obj_s   :   struttura metodi
        obj     :   namespace metodo
        
    */

    // definisce la struttura per i tipi

    #define CLASS_TYPE(ID,...)\
    struct ID##_t\
    {\
        __VA_ARGS__\
    };\
    typedef struct ID##_t ID##_t ;

    // definisce la struttura per i metodi

    #define CLASS_STRUCTURE(ID,...)\
    typedef struct ID##_s\
    {\
        __VA_ARGS__\
    } ID##_s ; 

    // NEW , ansi C richiede di definire il primo campo, trick.

    #define NEW(ID,...) ID##_new("",##__VA_ARGS__)

    // NEW , ansi C richiede di definire il primo campo, trick.

    #define IMPORT_METHOD memmove

    #define CLASS(class,id,...)\
    typedef struct id ## _s\
    {\
        __VA_ARGS__\
        class##_s call;\
    } id##_t;\
    id##_t id;\
    memmove ( & id . call ,& class ,sizeof(class) );\

    #define $(id,method,...) (id . call. method( & id ),#__VA_ARGS__)

    #define INHERIT(ID) INTERFACE_##ID##_T

    // ...................................... PROPERTY  

    #define PROPERTY(TYPE,ID)\
    struct ID##_s\
    {\
       TYPE data;\
       TYPE (*get)(void);\
       void (*set)(TYPE value);\
    } ID

    // ...................................... GET  

    #define GET(ID)  (ID).data

    // ...................................... SET 

    #define SET(ID,value) (ID).data = value
    
    /**/
    
#endif



/**/