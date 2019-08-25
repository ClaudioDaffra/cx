
#include "xoop.h"
#include "animal.h"
#include "cat.h"

/*
    cl  exp\animal.c exp\cat.c exp\main.c /Fex.exe
    gcc exp\animal.c exp\cat.c exp\main.c -o x.exe
    gcc exp/animal.c exp/cat.c exp/main.c -o x    
*/

// .......................  FRIEND  makeSound

void friend_makeSound(void *_this,...)
{
    va_list args;
    va_start ( args, _this );  
    
    const char *s = va_arg(args, const char *);  
     
    if ( strcmp(s,"cat")==0 )
    {
        animal_t* this = (animal_t*) _this;
        printf ( "\n (friend) miaoh\n") ;
    }
    else
    {
        printf ( "\n hmm i am not your friend!") ;
    }
    
    va_end(args);    
}

int main ( void )
{
    // ................................ a STACK
    
    // utilizza direttamente i metodi di animal (statico)
    
    animal_t a ;  

    animal.makeSound(&a);
    animal.setXY(&a,45,67);
    printf ( "\n %d",a.x ); 
    printf ( "\n %d",a.y );

    // ................................ c STACK

    // utilizza direttamente i metodi di animal, cat (statico)
    
    cat_t c ;
    cat.makeSound(&c);
    animal.setXY(&c.xxx,111,222);
    printf ( "\n %d %d",c.x,c.xxx.x ); 
    printf ( "\n %d %d",c.y,c.xxx.y );    

    // ................................ pc HEAP

    // utilizza direttamente i metodi di animal (statico)
    
    cat_t* pc = NEW(cat);

    cat.makeSound(pc); 
    
    cat.setXY(pc,450,670);

    printf ( "\n %d",pc->x ); 
    printf ( "\n %d",pc->y );

    cat.delete(pc);
    
    // ................................ c2

    // utilizza direttamente i metodi di cat derivati da animal (dinamico)
    
    cat_t c2 ;      // definisci il tipo
    cat_s cat2 ;    // definisci la struttura
    
    IMPORT_METHOD ( &cat2,&cat,sizeof(cat) ); // eredita tutta la struttura !
    
    // ................................ bind late
    
    cat2.makeSound  = (void*)friend_makeSound ;     // change in runtime !     
    cat2.makeSound(&c2,"cat");


    // -------------------- 
    // FINAL IMPLEMENTATION
    // --------------------  
    
    // utilizza la struttura di CAT , eredita la struttura di ANIMAL
    // e clona i rispettivi metodi di cat, e definisce un nuovo tipo (c3_t)

    printf ( "\n last implementation:\n" );

    CLASS(cat,c3,
    
        INHERIT(ANIMAL);
        animal_t xxx ;
        PROPERTY(int,a);
        
    ); // c3_t         

    $(c3,makeSound); //c3.call.makeSound(&c3);
 
    c3.x = 11;
    c3.y = 12;    
    
    SET(c3.a,13) ;

    printf( "\n %d/%d - %d\n",c3.x,c3.y,GET(c3.a) );
 
    /**/

    printf ( "\n" ); 
   
 return 0 ;
}








