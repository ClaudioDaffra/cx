
//
// http://theorangeduck.com/page/printing-stack-trace-mingw
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
    #include <stdio.h>
    #include <stdlib.h>  
#else
    #include <err.h>
    #include <execinfo.h>
    #include <string.h>
    #include <errno.h>
    #include <unistd.h>
    #include <stdlib.h>
#endif

static char const * global_program_name;



#if defined(_WIN32) || defined(_WIN64)

    static void windows_print_stack_trace(void) 
    {
      HANDLE process = GetCurrentProcess();
      HANDLE thread = GetCurrentThread();
      
      CONTEXT context;
      memset(&context, 0, sizeof(CONTEXT));
      context.ContextFlags = CONTEXT_FULL;
      RtlCaptureContext(&context);
      
      SymInitialize(process, NULL, TRUE);
      
      DWORD image;
      STACKFRAME64 stackframe;
      ZeroMemory(&stackframe, sizeof(STACKFRAME64));
      
    #ifdef _M_IX86
      image = IMAGE_FILE_MACHINE_I386;
      stackframe.AddrPC.Offset = context.Eip;
      stackframe.AddrPC.Mode = AddrModeFlat;
      stackframe.AddrFrame.Offset = context.Ebp;
      stackframe.AddrFrame.Mode = AddrModeFlat;
      stackframe.AddrStack.Offset = context.Esp;
      stackframe.AddrStack.Mode = AddrModeFlat;
    #elif _M_X64
      image = IMAGE_FILE_MACHINE_AMD64;
      stackframe.AddrPC.Offset = context.Rip;
      stackframe.AddrPC.Mode = AddrModeFlat;
      stackframe.AddrFrame.Offset = context.Rsp;
      stackframe.AddrFrame.Mode = AddrModeFlat;
      stackframe.AddrStack.Offset = context.Rsp;
      stackframe.AddrStack.Mode = AddrModeFlat;
    #elif _M_IA64
      image = IMAGE_FILE_MACHINE_IA64;
      stackframe.AddrPC.Offset = context.StIIP;
      stackframe.AddrPC.Mode = AddrModeFlat;
      stackframe.AddrFrame.Offset = context.IntSp;
      stackframe.AddrFrame.Mode = AddrModeFlat;
      stackframe.AddrBStore.Offset = context.RsBSP;
      stackframe.AddrBStore.Mode = AddrModeFlat;
      stackframe.AddrStack.Offset = context.IntSp;
      stackframe.AddrStack.Mode = AddrModeFlat;
    #endif

      for (size_t i = 0; i < 25; i++) 
      {
            BOOL result = StackWalk64(
              image, process, thread,
              &stackframe, &context, NULL, 
              SymFunctionTableAccess64, SymGetModuleBase64, NULL);
            
            if (!result) 
            { 
                break; 
            }
            
            char buffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR)];
            PSYMBOL_INFO symbol = (PSYMBOL_INFO)buffer;
            symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
            symbol->MaxNameLen = MAX_SYM_NAME;
            
            DWORD64 displacement = 0;
            if (SymFromAddr(process, stackframe.AddrPC.Offset, &displacement, symbol)) 
            {
              printf("[%i] %s\n", i, symbol->Name);
            } 
            else 
            {
              printf("[%i] ???\n", i);
            }
      }
      
      SymCleanup(process);

    }

  static LONG WINAPI windows_exception_handler(EXCEPTION_POINTERS * ExceptionInfo)
  {
    printf("\n");
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
    
    windows_print_stack_trace() ;

    return EXCEPTION_EXECUTE_HANDLER;
  }

  static void set_signal_handler()
  {
    SetUnhandledExceptionFilter(windows_exception_handler);
  }
  
#else // LINUX
 
    // http://kungjohan.blogspot.com/2012/06/how-to-print-stack-trace-in-your-user.html

   #define MAX_STACK_FRAMES 64

  static void posix_print_stack_trace()
  {
    void *trace[MAX_STACK_FRAMES];

    char **messages = (char **)NULL;

    int i, trace_size = 0;

    trace_size = backtrace(trace, MAX_STACK_FRAMES);

    messages = backtrace_symbols(trace, trace_size);

    for (i=0; i < trace_size; i++) printf("%s\n", messages[i]);

    printf("\n");
     
    free(messages);
  }
 
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
    
    posix_print_stack_trace();
    
    _Exit(1);
  }

  static uint8_t alternate_stack[SIGSTKSZ];
  
  static void set_signal_handler()
  {
    /* setup alternate stack */
    {
      // stack_t ss = {}; //   warning: ISO C forbids empty initializer braces [-Wpedantic]
      stack_t ss = { 0 }  ; 

      /* malloc is usually used here, I'm not 100% sure my static allocation
         is valid but it seems to work just fine. */
      ss.ss_sp = (void*)alternate_stack;
      ss.ss_size = SIGSTKSZ;
      ss.ss_flags = 0;

      if (sigaltstack(&ss, NULL) != 0) { err(1, "sigaltstack"); }
    }

    /* register our signal handlers */
    {
      //struct sigaction sig_action = {}; //   warning: ISO C forbids empty initializer braces [-Wpedantic]
      struct sigaction sig_action = { 0 };

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

