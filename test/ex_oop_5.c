
/*

    cl test\ex_oop_5.c /Fex.exe     /WX 
    gcc test\ex_oop_5.c -o x.exe    -Wall -Wextra
    gcc test/ex_oop_5.c -o x        -Wall -Wextra
    
*/

#include "../lib/oop.h"

CLASS( point,

    FIELD(int,x) ; // incapsulamento
    
    METHOD(int,getX);
    METHOD(int,setX,int data);    
    
    FIELD(int,y); 
    
    METHOD(int,getY);
    METHOD(int,setY,int data);    

    METHOD(void,free);
) ;

 
METHOD_SET(point,int, getX ) 
{
    return THIS(point)->x ;
}
METHOD_SET(point,int, getY )
{
    return THIS(point)->y ;
}
METHOD_SET(point,int, setX , int data) 
{
    return THIS(point)->x = data ;
}
METHOD_SET(point,int, setY , int data) 
{
    return THIS(point)->y = data ;
}

CONSTRUCTOR (point,

    this->getX = METHOD_GET(point,getX) ;
    this->getY = METHOD_GET(point,getY) ;
    this->setX = METHOD_GET(point,setX) ;
    this->setY = METHOD_GET(point,setY) ;
    //
    this->free = METHOD_GET(point,free) ;
);
DESTRUCTOR(point) ;

 
CLASS( linea,

    INHERIT(point) p;   // ereditarietà

    FIELD(int,len) ;

    METHOD(void,free);
);

METHOD_SET(linea,int, setX , int data) 
{
    return THIS(linea)->p.x = (data*100) ;
}
METHOD_SET(linea,int, setY , int data) 
{
    return THIS(linea)->p.y = (data*100) ;
}
CONSTRUCTOR (linea,

    this->p.getX = METHOD_GET(point,getX) ;
    this->p.getY = METHOD_GET(point,getY) ;
    
    this->p.setX = METHOD_GET(linea,setX) ;   // polimorfismo
    this->p.setY = METHOD_GET(linea,setY) ;
    //
    this->free = METHOD_GET(linea,free) ;
);
DESTRUCTOR(linea) ;
 
//###############################################################

CLASS( duePunti,

  INHERIT(point) p1;    // struct point p1 ;
  INHERIT(point) p2;    // struct point p2 ;
  
  METHOD(void,set_p1_xy,int x,int y);
  METHOD(void,set_p2_xy,int x,int y);
 
  METHOD(void,free) ;

  METHOD(void,lateBinding); 
  // late binding, not method SET : void (*lateBinding)(void*)
);

METHOD_SET(duePunti,void, set_p1_xy , int x,int y) 
{
    THIS(duePunti)->p1.x = x ;
    THIS(duePunti)->p1.y = y ;    
}
METHOD_SET(duePunti,void, set_p2_xy , int x,int y) 
{
    THIS(duePunti)->p2.x = x ;
    THIS(duePunti)->p2.y = y ;    
}
CONSTRUCTOR (duePunti,

    this->set_p1_xy = METHOD_GET(duePunti,set_p1_xy ) ;  
    this->set_p2_xy = METHOD_GET(duePunti,set_p2_xy ) ;  
    //
    this->free = METHOD_GET(duePunti,free) ;
);
DESTRUCTOR(duePunti) ;

int FRIEND(duePunti,showPoint) 
{
 printf ( "\n p1[%d,%d]",THIS(duePunti)->p1.x,THIS(duePunti)->p1.y ) ;
 printf ( "\n p1[%d,%d]",THIS(duePunti)->p2.x,THIS(duePunti)->p2.y ) ;
 printf ( "\n" );
 return 0 ;    
}
 
 
int main ( void )
{
    // ..................... punto    
  
    point* p1 = NEW(point);

    p1->x = 100 ; // accesso diretto ai dati
    
    $(p1,setX,1);
    $(p1,setY,2);    
 
    printf ( "\n%d %d\n" 
       , $(p1,getX)
       , $(p1,getY)  
    ); 
     
    $(p1,free);
   
    // ..................... linea
    
    linea* l1 = NEW(linea);
    
    l1->p.x = 10 ;
    
    $(l1,p.setY,12);
    
    printf ( "{%d}",$(l1,p.getY) );
    
    l1->len = 300 ;
 
    $(l1,free);
 
    // ..................... due punti

    duePunti* dp = NEW(duePunti);

    $(dp,set_p1_xy,123,456);
    $(dp,set_p2_xy,78,90);
    
    printf ( "\np1 xy(%d,%d)\n" 
       , dp->p1.x 
       , dp->p1.y        
    );
    printf ( "\np1 xy(%d,%d)\n" 
       , dp->p2.x 
       , dp->p2.y        
    );
    
    // ..................... friend
    
    showPoint(dp);

    // ..................... late binding

    BIND(dp,lateBinding,showPoint);

    $(dp,lateBinding);

    // ..................... destructor
    
    $(dp,free);
 
    printf("\n");
    return 0 ;
}

 

/**/
/**/
/**/


