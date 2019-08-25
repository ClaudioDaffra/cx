
// January 13, 2013 by: Job Vranish
//
// https://gist.github.com/jvranish/4441299
// jvranish/stack_traces.c
// https://spin.atomicobject.com/2013/01/13/exceptions-stack-traces-c/
//
// july  23, 2019 by :claudio daffra
//
// add : winaddr2line
// add : win64 support
// add : bug fix .exe not present to winaddr2line 
// add : StackWalk 64bit
//
// split    : debugWithStacTrace
// remove   : Addr2Line
// add      : macro begin end
// add      : printStackTrace
//

#include <signal.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>

#if defined(_WIN32) || defined(_WIN64)
  #include <windows.h>
  #include <imagehlp.h>
#else
  #include <err.h>
  #include <execinfo.h>
#endif

static char const * global_program_name="<program>";  

//************ 
//stack trace
//************ 

#include "../lib/mstack.h"

// ..................................... tipo enumerativo

typedef enum stackTraceType_e
{
    stNoType,
    stFunction,
} stackTraceType_t ;

// ..................................... struttura principale

typedef struct stackTrace_s
{
    stackTraceType_t    type;   // il tipo di dato contenuto
    char*               name;   // il nome 
    void*               value;  // il valore 
} stackTrace_t ;

typedef void* stPVOID ;

stackType(stPVOID,st);

// ..................................... stampa lo stack

int printStackTrace(void)
{
    puts ( "\nStack Trace ::");
    while(!stackEmpty(st))
    {
        printf ( "\n[%s]::",global_program_name );         
        switch ( ((stackTrace_t*)stackTop(st))->type )
        {

            case stFunction : 
                  printf ( "FUNCTION[%s]",(char*)((stackTrace_t*)stackTop(st))->name );
                break;
                
            default : 
                puts ( "\n?? INTERNAL ERROR : (debugWithStackTrace.h) -> void printStackTrace(void)\n" ) ;
                gcStop();
                exit(EXIT_FAILURE);
                return EXIT_FAILURE;
                break;
        }
        stackPop(st);
    }
    puts(""); // \n
    
    gcStop();
  return 0;
}

// ............................... svuota lo stack trace

void stStop(void)
{
    while(!stackEmpty(st))
    {
        stackPop(st);
    }
}
// ............................... inizializza lo stack trace

#define stStart(...) stackNew(st,128);

// ............................... push function

// per evitare : gcc -Wdiscarded-qualifiers : char*s = (char*)__FUNCTION__
 
#define stPushFunction(...)\
    do {\
        stackTrace_t* pst = (stackTrace_t*) gcMalloc(sizeof(stackTrace_t));\
        pst->type  = stFunction;\
        char*s = (char*)__FUNCTION__;\
        pst->name  = gcStrDup(s);\
        pst->value = gcStrDup(s);\
        stackPush(st,pst);\
    } while(0);\
    
//****************
// END stack trace
//****************


#if defined(_WIN32) || defined(_WIN64)

  static LONG WINAPI windows_exception_handler(EXCEPTION_POINTERS * ExceptionInfo)
  {
    switch(ExceptionInfo->ExceptionRecord->ExceptionCode)
    {
      case EXCEPTION_ACCESS_VIOLATION:
        fputs("Error: EXCEPTION_ACCESS_VIOLATION\n", stderr);
        break;
      case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
        fputs("Error: EXCEPTION_ARRAY_BOUNDS_EXCEEDED\n", stderr);
        break;
      case EXCEPTION_BREAKPOINT:
        fputs("Error: EXCEPTION_BREAKPOINT\n", stderr);
        break;
      case EXCEPTION_DATATYPE_MISALIGNMENT:
        fputs("Error: EXCEPTION_DATATYPE_MISALIGNMENT\n", stderr);
        break;
      case EXCEPTION_FLT_DENORMAL_OPERAND:
        fputs("Error: EXCEPTION_FLT_DENORMAL_OPERAND\n", stderr);
        break;
      case EXCEPTION_FLT_DIVIDE_BY_ZERO:
        fputs("Error: EXCEPTION_FLT_DIVIDE_BY_ZERO\n", stderr);
        break;
      case EXCEPTION_FLT_INEXACT_RESULT:
        fputs("Error: EXCEPTION_FLT_INEXACT_RESULT\n", stderr);
        break;
      case EXCEPTION_FLT_INVALID_OPERATION:
        fputs("Error: EXCEPTION_FLT_INVALID_OPERATION\n", stderr);
        break;
      case EXCEPTION_FLT_OVERFLOW:
        fputs("Error: EXCEPTION_FLT_OVERFLOW\n", stderr);
        break;
      case EXCEPTION_FLT_STACK_CHECK:
        fputs("Error: EXCEPTION_FLT_STACK_CHECK\n", stderr);
        break;
      case EXCEPTION_FLT_UNDERFLOW:
        fputs("Error: EXCEPTION_FLT_UNDERFLOW\n", stderr);
        break;
      case EXCEPTION_ILLEGAL_INSTRUCTION:
        fputs("Error: EXCEPTION_ILLEGAL_INSTRUCTION\n", stderr);
        break;
      case EXCEPTION_IN_PAGE_ERROR:
        fputs("Error: EXCEPTION_IN_PAGE_ERROR\n", stderr);
        break;
      case EXCEPTION_INT_DIVIDE_BY_ZERO:
        fputs("Error: EXCEPTION_INT_DIVIDE_BY_ZERO\n", stderr);
        break;
      case EXCEPTION_INT_OVERFLOW:
        fputs("Error: EXCEPTION_INT_OVERFLOW\n", stderr);
        break;
      case EXCEPTION_INVALID_DISPOSITION:
        fputs("Error: EXCEPTION_INVALID_DISPOSITION\n", stderr);
        break;
      case EXCEPTION_NONCONTINUABLE_EXCEPTION:
        fputs("Error: EXCEPTION_NONCONTINUABLE_EXCEPTION\n", stderr);
        break;
      case EXCEPTION_PRIV_INSTRUCTION:
        fputs("Error: EXCEPTION_PRIV_INSTRUCTION\n", stderr);
        break;
      case EXCEPTION_SINGLE_STEP:
        fputs("Error: EXCEPTION_SINGLE_STEP\n", stderr);
        break;
      case EXCEPTION_STACK_OVERFLOW:
        fputs("Error: EXCEPTION_STACK_OVERFLOW\n", stderr);
        break;
      default:
        fputs("Error: Unrecognized Exception\n", stderr);
        break;
    }
    fflush(stderr);

    //----------------
    printStackTrace();
    //----------------
    
    return EXCEPTION_EXECUTE_HANDLER;
  }

  static void set_signal_handler()
  {
    SetUnhandledExceptionFilter(windows_exception_handler);
  }
  
#else

  static void posix_signal_handler(int sig, siginfo_t *siginfo, void *context)
  {
    (void)context;
    switch(sig)
    {
      case SIGSEGV:
        fputs("Caught SIGSEGV: Segmentation Fault\n", stderr);
        break;
      case SIGINT:
        fputs("Caught SIGINT: Interactive attention signal, (usually ctrl+c)\n", stderr);
        break;
      case SIGFPE:
        switch(siginfo->si_code)
        {
          case FPE_INTDIV:
            fputs("Caught SIGFPE: (integer divide by zero)\n", stderr);
            break;
          case FPE_INTOVF:
            fputs("Caught SIGFPE: (integer overflow)\n", stderr);
            break;
          case FPE_FLTDIV:
            fputs("Caught SIGFPE: (floating-point divide by zero)\n", stderr);
            break;
          case FPE_FLTOVF:
            fputs("Caught SIGFPE: (floating-point overflow)\n", stderr);
            break;
          case FPE_FLTUND:
            fputs("Caught SIGFPE: (floating-point underflow)\n", stderr);
            break;
          case FPE_FLTRES:
            fputs("Caught SIGFPE: (floating-point inexact result)\n", stderr);
            break;
          case FPE_FLTINV:
            fputs("Caught SIGFPE: (floating-point invalid operation)\n", stderr);
            break;
          case FPE_FLTSUB:
            fputs("Caught SIGFPE: (subscript out of range)\n", stderr);
            break;
          default:
            fputs("Caught SIGFPE: Arithmetic Exception\n", stderr);
            break;
        }
      case SIGILL:
        switch(siginfo->si_code)
        {
          case ILL_ILLOPC:
            fputs("Caught SIGILL: (illegal opcode)\n", stderr);
            break;
          case ILL_ILLOPN:
            fputs("Caught SIGILL: (illegal operand)\n", stderr);
            break;
          case ILL_ILLADR:
            fputs("Caught SIGILL: (illegal addressing mode)\n", stderr);
            break;
          case ILL_ILLTRP:
            fputs("Caught SIGILL: (illegal trap)\n", stderr);
            break;
          case ILL_PRVOPC:
            fputs("Caught SIGILL: (privileged opcode)\n", stderr);
            break;
          case ILL_PRVREG:
            fputs("Caught SIGILL: (privileged register)\n", stderr);
            break;
          case ILL_COPROC:
            fputs("Caught SIGILL: (coprocessor error)\n", stderr);
            break;
          case ILL_BADSTK:
            fputs("Caught SIGILL: (internal stack error)\n", stderr);
            break;
          default:
            fputs("Caught SIGILL: Illegal Instruction\n", stderr);
            break;
        }
        break;
      case SIGTERM:
        fputs("Caught SIGTERM: a termination request was sent to the program\n", stderr);
        break;
      case SIGABRT:
        fputs("Caught SIGABRT: usually caused by an abort() or assert()\n", stderr);
        break;
      default:
        break;
    }
    
    //----------------
    printStackTrace();
    //----------------
    
    _Exit(1);
  }

  static uint8_t alternate_stack[SIGSTKSZ];

  static void set_signal_handler(void)
  {
    /* setup alternate stack */
    {
      stack_t ss = {};
      /* malloc is usually used here, I'm not 100% sure my static allocation
         is valid but it seems to work just fine. */
      ss.ss_sp = (void*)alternate_stack;
      ss.ss_size = SIGSTKSZ;
      ss.ss_flags = 0;

      if (sigaltstack(&ss, NULL) != 0) { err(1, "sigaltstack"); }
    }

    /* register our signal handlers */
    {
      struct sigaction sig_action = {};
      sig_action.sa_sigaction = posix_signal_handler;
      sigemptyset(&sig_action.sa_mask);

      #ifdef __APPLE__
          /* for some reason we backtrace() doesn't work on osx
             when we use an alternate stack */
          sig_action.sa_flags = SA_SIGINFO;
      #else
          sig_action.sa_flags = SA_SIGINFO | SA_ONSTACK;
      #endif

      if (sigaction(SIGSEGV, &sig_action, NULL) != 0) { err(1, "sigaction"); }
      if (sigaction(SIGFPE,  &sig_action, NULL) != 0) { err(1, "sigaction"); }
      if (sigaction(SIGINT,  &sig_action, NULL) != 0) { err(1, "sigaction"); }
      if (sigaction(SIGILL,  &sig_action, NULL) != 0) { err(1, "sigaction"); }
      if (sigaction(SIGTERM, &sig_action, NULL) != 0) { err(1, "sigaction"); }
      if (sigaction(SIGABRT, &sig_action, NULL) != 0) { err(1, "sigaction"); }
    }
  }
  


#endif






/**/

