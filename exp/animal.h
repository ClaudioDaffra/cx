
#ifndef ANIMAL
#define ANIMAL

    // definisce l'interfaccia per i tipi   (t)
    // p.s. vs non vuole ;; in struttura
    
    #define INTERFACE_ANIMAL_T\
            int x ;\
            int y ;
 
    // definisce l'interfaccia per i metodi (s)
            
    #define INTERFACE_ANIMAL_S\
            void        (*delete)       (void*,...) ;\
            void        (*makeSound)    (void*,...) ;\
            void        (*setXY)        (void*,...) ;

    CLASS_TYPE( animal,

        INTERFACE_ANIMAL_T  
        
    );
    
    // struct animal_t
    // typdef struct animal_t animal_t

    CLASS_STRUCTURE(animal,

        INTERFACE_ANIMAL_S

    );

    // struct animal_s
    // typdef struct animal_s animal_s
 
    // header 
    
    animal_t*   animal_new      (const char* s,...      ) ;  
    void        animal_delete   (animal_t *this,...     ) ;
    void        animal_makeSound(animal_t *this         ) ;
    void        animal_setXY    (animal_t *this,...     ) ;

    extern animal_s animal ;
    
#endif


/**/


