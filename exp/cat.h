
#ifndef CAT
#define CAT

    #include "xoop.h"
    #include "animal.h"
    
    // struttura anonima
    // stuttura con i tipi

    CLASS_TYPE( cat,

        int x;
        int y;     
        
        animal_t xxx ;          
        
    );
    
    // eredita
    
    CLASS_STRUCTURE(cat,

        INTERFACE_ANIMAL_S     

    );

    cat_t*  cat_new         (const char* s,...  ) ;
    void    cat_makeSound   (cat_t *this,...    ) ;
    void    cat_delete      (cat_t *this,...    ) ;

    extern cat_s cat ;
        
#endif

