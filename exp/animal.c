
#include "xoop.h"
#include "animal.h"



// ..............................................................   new
animal_t* animal_new(const char* s,...) // trick
{
    animal_t* temp = (animal_t*) malloc( sizeof(animal_t) );
    return temp ;
}
// ..............................................................   delete
void animal_delete(animal_t *this,...)
{
    free(this);
}
// ..............................................................   makeSound
void animal_makeSound(animal_t *this)
{
    printf ( "\n make : ? \n") ;
}
// ..............................................................   setXY
void animal_setXY(animal_t *this,...)
{
    va_list args;
    va_start ( args, this );  
    
    int X = va_arg(args, int);  
    int Y = va_arg(args, int); 

    this->x = X ;
    this->y = Y ;

    va_end(args); 
}

// definisci il corpo

animal_s animal = 
{ 
    (void*)animal_delete       ,   
    (void*)animal_makeSound  ,          
    (void*)animal_setXY      ,  
} ;


/**/

