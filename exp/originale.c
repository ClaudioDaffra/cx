
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

 
/**
    obj_t   :   struttura dati
    obj_s   :   struttura metodi
    obj     :   namespace metodo
    
*/
 

//#######
// ANIMAL
//#######

struct animal_t
{
    int x ;
    int y ;
    
}  ;
typedef struct animal_t animal_t ;

// ..............................................................
animal_t* animal_new(const char* s,...) // trick
{
    animal_t* temp = (animal_t*) malloc( sizeof(animal_t) );
    return temp ;
}
void animal_free(animal_t *this)
{
    free(this);
}
void animal_makeSound(animal_t *this)
{
    printf ( "\n make : ? \n") ;
}
// ..............................................................
void animal_setXY(void *_this,...)
{
    va_list args;
    va_start ( args, _this );  

    animal_t* this = (animal_t*) _this ;
    
    int X = va_arg(args, int);  
    int Y = va_arg(args, int); 

    this->x = X ;
    this->y = Y ;

    va_end(args); 
}
// ..............................................................
typedef struct animal_s
{
    void        (*free)        (void*,...) ; 
    void        (*makeSound)   (void*,...) ;         
    void        (*setXY)       (void*,...) ;  
} animal_s ; 

animal_s animal = 
{ 
    (void*)animal_free       ,   
    (void*)animal_makeSound  ,          
    (void*)animal_setXY      ,  
} ;

//######
// CAT
//######

// .............................................................. FIELD
struct cat_t
{
    int x ;
    int y ;
}  ;
typedef struct cat_t cat_t ;

// .............................................................. new
cat_t* cat_new(const char* s,...) // trick
{
    cat_t* temp = (cat_t*) malloc( sizeof(cat_t) );
    return temp ;
}
// .............................................................. TABELLA VIRTUALE
void cat_makeSound(void *_this)
{
    cat_t* this = (cat_t*) _this ;
    
    printf ( "\n make : miaooo \n") ;
}
void cat_free(cat_t *this)
{
    free(this);
} 
// .............................................................. METODI
typedef struct cat_s
{
    void        (*free)        (void*,...) ;
    void        (*makeSound)   (void*,...) ;          
    void        (*setXY)       (void*,...) ;  
} cat_s ;

cat_s cat = // incapsulamento
{ 
    (void*)cat_free       ,   
    (void*)cat_makeSound     ,     // polimorfismo         
    (void*)animal_setXY      ,  
} ;

// #############################################################

int main ( void )
{
    // ................................ a
    animal_t a ;  

    animal.makeSound(&a);
    animal.setXY(&a,45,67);
    printf ( "\n %d",a.x ); 
    printf ( "\n %d",a.y );

    //
    // ................................ c 
    cat_t c ;
    cat.makeSound(&c);

    // ................................ pc 
    cat_t* pc = cat_new("");
    cat.makeSound(pc); 
    animal.setXY(pc,450,670);
    printf ( "\n %d",pc->x ); 
    printf ( "\n %d",pc->y );    
    cat_free(pc);
    
    // evolution
    
    cat_t c2 ;
    
    cat_s cat2 ;     // definisci tipo
    // eredita tutta la struttura !
    memmove ( &cat2,&cat,sizeof(cat) );
    
    // ................................ bind late
    
    cat2.makeSound  = (void*)animal_makeSound ;     // change in runtime !     
    cat2.makeSound(&c2);
    
    printf ( "\n" ); 
   
 return 0 ;
}








