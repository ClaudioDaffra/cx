
#include "xoop.h"
#include "animal.h"
#include "cat.h"


// .............................................................. new
cat_t* cat_new(const char* s,...) // trick ansi C need 1 paramter al least
{
    cat_t* temp = (cat_t*) malloc( sizeof(cat_t) );
    return temp ;
}
// .............................................................. makeSound
void cat_makeSound(cat_t *this,...)
{
    printf ( "\n make : miaooo \n") ;
}
// .............................................................. delete
void cat_delete(cat_t *this,...)
{
    free(this);
} 

cat_s cat = // incapsulamento
{ 
    (void*)cat_delete          ,   
    (void*)cat_makeSound     ,     // polimorfismo         
    (void*)animal_setXY      ,  
} ;
