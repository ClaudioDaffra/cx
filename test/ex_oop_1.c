
#include "../lib/oop.h"

/*

    cl test\ex_oop_1.c /Fex.exe
    gcc test\ex_oop_1.c -o x.exe

*/


#define FOO_EXCEPTION (1)
#define BAR_EXCEPTION (2)
#define BAZ_EXCEPTION (3)

int
main(int argc, char** argv)
{
   TRY
   {
      printf("In Try Statement\n");
      THROW( BAR_EXCEPTION );
      printf("I do not appear\n");
   }
   CATCH( FOO_EXCEPTION )
   {
      printf("Got Foo!\n");
   }
   CATCH( BAR_EXCEPTION )
   {
      printf("Got Bar!\n");
   }
   CATCH( BAZ_EXCEPTION )
   {
      printf("Got Baz!\n");
   }
   /*
   FINALLY
   {
      printf("...et in arcadia Ego\n");
   }
   */
   END_TRY;

   return 0;
}