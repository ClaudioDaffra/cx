-----------------------------
Pthreads on Microsoft Windows
-----------------------------

An extremely common API used for developing parallel programs is the Posix Threads API (pthreads). 
The API contains many synchronization primitives that allow threaded code to be efficiently written. 
Unfortunately, Microsoft Windows does not support this interface as-is. 
Thus if one wishes to port over an application, quite a bit of work may need to be done.

Fortunately, a pthreads library for windows has been written, thus simplifying the porting effort. 
However, the windows API has progressed significantly with regards to threading since that library was written. 
Many new functions have been exported that simplify the creation of a pthread library on windows. 
In fact nearly all of the synchronization primitives now exist, 
and using them may only require the creation of a few simple macros.

Thus it seems to be time to explore the creation of a new pthreads library for Microsoft windows. 
To make its use as simple as possible, 
we will require its entire implementation to be confined to a single header .h file. 
Thus requiring no explicit library to be linked into an application or dll. 
This trick can be done if all its global variables are implicitly defined to be zero, and all functions are static.

Finally, we note that whilst many of the synchronization primitives required by 
the pthreads API are exported by Microsoft windows, not all are. 
Thus we will need to explore some of the undocumented internals of windows. 
This is obviously dangerous, as Microsoft may change these undocumented features at 
any time in the future. However, as a educational learning exercise, 
we can ignore this unpalatable fact and see exactly how much we can get away with.

-----------------------------
Critical Sections for Mutexes
-----------------------------

The first part we shall implement are the functions for pthread_mutex_t. 
This can be done by using a CRITICAL_SECTION object and a typedef. 
This may not be the most efficient mutex, but it is extremely portable on Microsoft windows. 
It allows you to use the resulting pthread API on any mutex, even those defined in other libraries. 
Since the pthread API extends the windows one, this is rather nice.

Most of the mutex functions are simple wrappers around the windows counterparts:

    typedef CRITICAL_SECTION pthread_mutex_t;
    static int pthread_mutex_lock(pthread_mutex_t *m)
    {
        EnterCriticalSection(m);
        return 0;
    }

    static int pthread_mutex_unlock(pthread_mutex_t *m)
    {
        LeaveCriticalSection(m);
        return 0;
    }
        
    static int pthread_mutex_trylock(pthread_mutex_t *m)
    {
        return TryEnterCriticalSection(m) ? 0 : EBUSY; 
    }

    static int pthread_mutex_init(pthread_mutex_t *m, pthread_mutexattr_t *a)
    {
        (void) a;
        InitializeCriticalSection(m);
        
        return 0;
    }

    static int pthread_mutex_destroy(pthread_mutex_t *m)
    {
        DeleteCriticalSection(m);
        return 0;
    }
    
The pthreads API has an initialization macro that has no correspondence to anything in the windows API. 
By investigating the internal definition of the critical section type, 
one may work out how to initialize one without calling InitializeCriticalSection(). 
The trick here is that InitializeCriticalSection() is not allowed to fail. 
It tries to allocate a critical section debug object, but if no memory is available, 
it sets the pointer to a specific value. 
(One would expect that value to be NULL, but it is actually (void *)-1 for some reason.) 
Thus we can use this special value for that pointer, and the critical section code will work.

The other important part of the critical section type to initialize is the number of waiters. 
This controls whether or not the mutex is locked. Fortunately, 
this part of the critical section is unlikely to change. Apparently, 
many programs already test critical sections to see if they are locked using this value, 
so Microsoft felt that it was necessary to keep it set at -1 for an unlocked critical section, 
even when they changed the underlying algorithm to be more scalable. 
The final parts of the critical section object are unimportant, 
and can be set to zero for their defaults. This yields an initialization macro:


    #define PTHREAD_MUTEX_INITIALIZER {(void*)-1,-1,0,0,0,0}

The next part of the pthread_mutex_t API is the pthread_mutex_timedlock() function. 
This also has no correspondence to something exported by windows.
A second problem is that the Posix function expects a struct timespec object. 
Unfortunately, no such type is defined in windows headers, 
so we'll need to define it, and some helper functions that use it.


    struct timespec
    {
        /* long long in windows is the same as long in unix for 64bit */
        long long tv_sec;
        long long tv_nsec;
    };

    static unsigned long long _pthread_time_in_ms(void)
    {
        struct __timeb64 tb;
        
        _ftime64(&tb);
        
        return tb.time * 1000 + tb.millitm;
    }

    static unsigned long long _pthread_time_in_ms_from_timespec(const struct timespec *ts)
    {
        unsigned long long t = ts->tv_sec * 1000;
        t += ts->tv_nsec / 1000000;

        return t;
    }

    static unsigned long long _pthread_rel_time_in_ms(const struct timespec *ts)
    {
        unsigned long long t1 = _pthread_time_in_ms_from_timespec(ts);
        unsigned long long t2 = _pthread_time_in_ms();
        
        /* Prevent underflow */
        if (t1 < t2) return 1;
        return t1 - t2;
    }
    
Using the above helper functions, we can implement pthread_mutex_timedlock using WaitForSingleObject() 
and pthread_mutex_trylock()


    #define ETIMEDOUT	110
    static int pthread_mutex_timedlock(pthread_mutex_t *m, struct timespec *ts)
    {
        unsigned long long t, ct;
        
        struct _pthread_crit_t
        {
            void *debug;
            LONG count;
            LONG r_count;
            HANDLE owner;
            HANDLE sem;
            ULONG_PTR spin;
        };
        
        /* Try to lock it without waiting */
        if (!pthread_mutex_trylock(m)) return 0;
        
        ct = _pthread_time_in_ms();
        t = _pthread_time_in_ms_from_timespec(ts);
        
        while (1)
        {
            /* Have we waited long enough? */
            if (ct > t) return ETIMEDOUT;
            
            /* Wait on semaphore within critical section */
            WaitForSingleObject(((struct _pthread_crit_t *)m)->sem, t - ct);
            
            /* Try to grab lock */
            if (!pthread_mutex_trylock(m)) return 0;
            
            /* Get current time */
            ct = _pthread_time_in_ms();
        }
    }
    
This almost completes the mutex API. However, to be fully complete we need to support the pthread_mutexattr_t functions. 
These affect the type of mutex created by pthread_mutex_init(). 
However, since Microsoft windows only supports one type of critical section, 
we will ignore most of this functionality. 
Instead, these simple wrapper functions will just record the state so that they give consistent results.


    #define PTHREAD_MUTEX_NORMAL 0
    #define PTHREAD_MUTEX_ERRORCHECK 1
    #define PTHREAD_MUTEX_RECURSIVE 2
    #define PTHREAD_MUTEX_DEFAULT 3
    #define PTHREAD_MUTEX_SHARED 4
    #define PTHREAD_MUTEX_PRIVATE 0

    #define ENOTSUP		134

    #define pthread_mutex_getprioceiling(M, P) ENOTSUP
    #define pthread_mutex_setprioceiling(M, P) ENOTSUP

    static int pthread_mutexattr_init(pthread_mutexattr_t *a)
    {
        *a = 0;
        return 0;
    }

    static int pthread_mutexattr_destroy(pthread_mutexattr_t *a)
    {
        (void) a;
        return 0;
    }

    static int pthread_mutexattr_gettype(pthread_mutexattr_t *a, int *type)
    {
        *type = *a & 3;

        return 0;
    }

    static int pthread_mutexattr_settype(pthread_mutexattr_t *a, int type)
    {
        if ((unsigned) type > 3) return EINVAL;
        *a &= ~3;
        *a |= type;
        
        return 0;
    }

    static int pthread_mutexattr_getpshared(pthread_mutexattr_t *a, int *type)
    {
        *type = *a & 4;
        
        return 0;
    }

    static int pthread_mutexattr_setpshared(pthread_mutexattr_t * a, int type)
    {
        if ((type & 4) != type) return EINVAL;
        
        *a &= ~4;
        *a |= type;
        
        return 0;
    }

    static int pthread_mutexattr_getprotocol(pthread_mutexattr_t *a, int *type)
    {
        *type = *a & (8 + 16);
        
        return 0;
    }

    static int pthread_mutexattr_setprotocol(pthread_mutexattr_t *a, int type)
    {
        if ((type & (8 + 16)) != 8 + 16) return EINVAL;
        
        *a &= ~(8 + 16);
        *a |= type;
        
        return 0;
    }

    static int pthread_mutexattr_getprioceiling(pthread_mutexattr_t *a, int * prio)
    {
        *prio = *a / PTHREAD_PRIO_MULT;
        return 0;
    }

    static int pthread_mutexattr_setprioceiling(pthread_mutexattr_t *a, int prio)
    {
        *a &= (PTHREAD_PRIO_MULT - 1);
        *a += prio * PTHREAD_PRIO_MULT;
        
        return 0;
    }
    
---------------------------------    
Slim Read Write Locks for rwlocks
---------------------------------

Since the earlier pthreads implementation on windows, Microsoft has added Slim Read Write locks (SRWlocks). 
These allow a simple implementation of much of the pthread_rwlock_t API. 
However, again the Microsoft API is a subset of the Posix API, 
so we will again need to explore the undocumented internals to construct the missing functionality.

Using wrappers for the functions that already exist, we can implement:


    typedef SRWLOCK pthread_rwlock_t;
    static int pthread_rwlock_init(pthread_rwlock_t *l, pthread_rwlockattr_t *a)
    {
        (void) a;
        InitializeSRWLock(l);
        
        return 0;
    }

    static int pthread_rwlock_destroy(pthread_rwlock_t *l)
    {
        (void) *l;
        return 0;
    }

    static int pthread_rwlock_rdlock(pthread_rwlock_t *l)
    {
        pthread_testcancel();
        AcquireSRWLockShared(l);
        
        return 0;
    }

    static int pthread_rwlock_wrlock(pthread_rwlock_t *l)
    {
        pthread_testcancel();
        AcquireSRWLockExclusive(l);
        
        return 0;
    }
    
Where we have added explicit calls to pthread_testcancel() mandated by the Posix API. 
Next, we need to work out an initialization macro, 
together with a way of implementing the trylock and unlock functionality. 
The problem here is that the Posix API requires a single unlock function, 
whereas the Microsoft windows API has separate unlock functions for read and write locks. 
We'll need to understand the lock internal state to work out whether 
we are a read or write lock in order to work out which unlock function to call.

By looking at the Microsoft documentation, we notice that the implementation of a 
SRWLock is a single pointer sized object. The InitializeSRWLock() function simply sets this pointer to zero. 
Thus, an initialization macro may be written as:


    #define PTHREAD_RWLOCK_INITIALIZER {0}

Next, we can construct simple programs to see how the state of this pointer-sized object changes 
as we read and write lock and unlock it. 
The first thing that is noticeable is that a SRWLock that is owned exclusively has the value 1, 
and that if multiple shared owners have taken the lock, then it has value 1+16n, 
where n is the number of shared owners. If there is contention, 
then the lock has the value of a pointer with the low bit set.

Thus, if the low bit is set, then the lock is owned by someone. 
If any other of the bottom three bits are set, 
then the lock has some internal state. Using this, 
we can construct the trylock functions which are not implemented by Microsoft.


    static int pthread_rwlock_tryrdlock(pthread_rwlock_t *l)
    {
        /* Get the current state of the lock */
        void *state = *(void **) l;
        
        if (!state)
        {
            /* Unlocked to locked */
            if (!_InterlockedCompareExchangePointer((void *) l, (void *)0x11, NULL)) return 0;
            return EBUSY;
        }
        
        /* A single writer exists */
        if (state == (void *) 1) return EBUSY;
        
        /* Multiple writers exist? */
        if ((uintptr_t) state & 14) return EBUSY;
        
        if (_InterlockedCompareExchangePointer((void *) l, (void *) ((uintptr_t)state + 16), state) == state) return 0;
        
        return EBUSY;
    }

    static int pthread_rwlock_trywrlock(pthread_rwlock_t *l)
    {
        /* Try to grab lock if it has no users */
        if (!_InterlockedCompareExchangePointer((void *) l, (void *)1, NULL)) return 0;
        
        return EBUSY;
    }
    
Next we need to implement pthread_rwlock_unlock. 
This is a little tricky. Unfortunately, 
it doesn't seem that there is an easy way to determine if the lock is owned by a reader or a writer. 
We have some known special cases. 
If the lock value is equal to 1, then it is owned by a single writer - so we can write unlock it. 
If the lock value is equal to 1 + 16n, with n>1 then we must be a shared reader trying to unlock it. 
If the lock is contended, and there is a list of threads waiting for it, then we need to know who to wake up.

Unfortunately, since the internals of a SRWLock are undocumented we are a little stuck. 
By exploring the implementation in asm we can see what is going on. Basically, 
the unlock routines need to check if they are the simple cases described above. 
If they aren't, and there are waiters, then more complex code is called to wake the required waiter. 
Fortunately, it seems that the code to wake the next waiter is extremely similar 
between the shared and exclusive cases. The shared (reader) case appears to be more generic, 
so we will use that. Testing the resulting function seems to pass. 
However, this is a little bit of a hack. 
Unlocking a contended exclusive lock with the shared unlock function may not work in the future. 
Ignoring that for now, we have:


    static int pthread_rwlock_unlock(pthread_rwlock_t *l)
    {
        void *state = *(void **)l;
        
        if (state == (void *) 1)
        {
            /* Known to be an exclusive lock */
            ReleaseSRWLockExclusive(l);
        }
        else
        {
            /* A shared unlock will work */
            ReleaseSRWLockShared(l);
        }
        
        return 0;
    }

Finally, we need to implement the timedlock functionality. 
Again, Microsoft windows doesn't have any timeout functions we can use. 
Even worse, the underlying wait is in an undocumented function NtWaitForKeyedEvent(), 
so we probably can't do the trick we did with critical sections. Instead, 
we will implement a busy wait. This isn't optimal, 
but until Microsoft describes its new interfaces it is free to alter them at will, 
so depending on them is extremely risky.


    static int pthread_rwlock_timedrdlock(pthread_rwlock_t *l, const struct timespec *ts)
    {
        unsigned long long ct = _pthread_time_in_ms();
        unsigned long long t = _pthread_time_in_ms_from_timespec(ts);

        pthread_testcancel();
        
        /* Use a busy-loop */
        while (1)
        {
            /* Try to grab lock */
            if (!pthread_rwlock_tryrdlock(l)) return 0;
            
            /* Get current time */
            ct = _pthread_time_in_ms();
            
            /* Have we waited long enough? */
            if (ct > t) return ETIMEDOUT;
        }
    }

    static int pthread_rwlock_timedwrlock(pthread_rwlock_t *l, const struct timespec *ts)
    {
        unsigned long long ct = _pthread_time_in_ms();
        unsigned long long t = _pthread_time_in_ms_from_timespec(ts);

        pthread_testcancel();
        
        /* Use a busy-loop */
        while (1)
        {
            /* Try to grab lock */
            if (!pthread_rwlock_trywrlock(l)) return 0;
            
            /* Get current time */
            ct = _pthread_time_in_ms();
            
            /* Have we waited long enough? */
            if (ct > t) return ETIMEDOUT;
        }
    }
    
The only thing left for a complete implementation of the rwlock API are the attributes for pthread_rwlock_init(). 
Again, since Microsoft only has one type of read/write lock, these don't need to do anything, 
and can be implemented as simple wrapper functions.


    typedef int pthread_rwlockattr_t;
    static int pthread_rwlockattr_destroy(pthread_rwlockattr_t *a)
    {
        (void) a;
        return 0;
    }

    static int pthread_rwlockattr_init(pthread_rwlockattr_t *a)
    {
        *a = 0;
    }

    static int pthread_rwlockattr_getpshared(pthread_rwlockattr_t *a, int *s)
    {
        *s = *a;
        return 0;
    }

    static int pthread_rwlockattr_setpshared(pthread_rwlockattr_t *a, int s)
    {
        *a = s;
        return 0;
    }
    
-------------------    
Condition Variables
-------------------

The next part of the synchronization API we shall implement are condition variables. 
Previously, the implementation of them was rather difficult, 
with issues of correctness and fairness arising. Fortunately, 
Microsoft has now implemented a condition variable API, 
and so the Posix API can now be implemented as a set of simple wrapper functions. 
A quick check reveals that condition variables can be safely zero-initialized, allowing a nice initialization macro.


    typedef CONDITION_VARIABLE pthread_cond_t;
    #define PTHREAD_COND_INITIALIZER {0}
    static int pthread_cond_init(pthread_cond_t *c, pthread_condattr_t *a)
    {
        (void) a;
        
        InitializeConditionVariable(c);
        return 0;
    }

    static int pthread_cond_signal(pthread_cond_t *c)
    {
        WakeConditionVariable(c);
        return 0;
    }

    static int pthread_cond_broadcast(pthread_cond_t *c)
    {
        WakeAllConditionVariable(c);
        return 0;
    }

    static int pthread_cond_wait(pthread_cond_t *c, pthread_mutex_t *m)
    {
        pthread_testcancel();
        SleepConditionVariableCS(c, m, INFINITE);
        return 0;
    }

    static int pthread_cond_destroy(pthread_cond_t *c)
    {
        (void) c;
        return 0;
    }

    static int pthread_cond_timedwait(pthread_cond_t *c, pthread_mutex_t *m, struct timespec *t)
    {
        unsigned long long tm = _pthread_rel_time_in_ms(t);
        
        pthread_testcancel();
        
        if (!SleepConditionVariableCS(c, m, tm)) return ETIMEDOUT;
        
        /* We can have a spurious wakeup after the timeout */
        if (!_pthread_rel_time_in_ms(t)) return ETIMEDOUT;
        
        return 0;
    }
    
Where again, due to only one type of condition variable existing, 
we can write a trivial condattr API that doesn't do much.


    typedef int pthread_condattr_t;
    static int pthread_condattr_destroy(pthread_condattr_t *a)
    {
        (void) a;
        return 0;
    }

    #define pthread_condattr_getclock(A, C) ENOTSUP
    #define pthread_condattr_setclock(A, C) ENOTSUP

    static int pthread_condattr_init(pthread_condattr_t *a)
    {
        *a = 0;
        return 0;
    }

    static int pthread_condattr_getpshared(pthread_condattr_t *a, int *s)
    {
        *s = *a;
        return 0;
    }

    static int pthread_condattr_setpshared(pthread_condattr_t *a, int s)
    {
        *a = s;
        return 0;
    }
 
-------- 
Barriers
--------

Using the condition variables and mutexes, we can now create the barrier API. 
The following describes a barrier where we count the number of incoming and outgoing waiters. 
By using a flag bit, we can work out whether or not we need to let threads into or out of the barrier. 
Note that the following code is designed for simplicity. 
By using a wait-tree greater performance can be obtained at the cost of complexity.


    #define PTHREAD_BARRIER_INITIALIZER \
        {0,0,PTHREAD_MUTEX_INITIALIZER,PTHREAD_COND_INITIALIZER}
    #define PTHREAD_BARRIER_SERIAL_THREAD 1

    typedef struct pthread_barrier_t pthread_barrier_t;
    struct pthread_barrier_t
    {
        int count;
        int total;
        CRITICAL_SECTION m;
        CONDITION_VARIABLE cv;
    };
    typedef void *pthread_barrierattr_t;

    static int pthread_barrier_destroy(pthread_barrier_t *b)
    {
        EnterCriticalSection(&b->m);

        while (b->total > _PTHREAD_BARRIER_FLAG)
        {
            /* Wait until everyone exits the barrier */
            SleepConditionVariableCS(&b->cv, &b->m, INFINITE);
        }

        LeaveCriticalSection(&b->m);

        DeleteCriticalSection(&b->m);
        
        return 0;
    }

    static int pthread_barrier_init(pthread_barrier_t *b, void *attr, int count)
    {
        /* Ignore attr */
        (void) attr;
        
        InitializeCriticalSection(&b->m);
        InitializeConditionVariable(&b->cv);
        b->count = count;
        b->total = 0;
        
        return 0;
    }

    #define _PTHREAD_BARRIER_FLAG (1<<30)
    static int pthread_barrier_wait(pthread_barrier_t *b)
    {
        EnterCriticalSection(&b->m);
        
        while (b->total > _PTHREAD_BARRIER_FLAG)
        {
            /* Wait until everyone exits the barrier */
            SleepConditionVariableCS(&b->cv, &b->m, INFINITE);
        }
        
        /* Are we the first to enter? */
        if (b->total == _PTHREAD_BARRIER_FLAG) b->total = 0;
        
        b->total++;
        
        if (b->total == b->count)
        {
            b->total += _PTHREAD_BARRIER_FLAG - 1;
            WakeAllConditionVariable(&b->cv);
            
            LeaveCriticalSection(&b->m);
            
            return 1;
        }
        else
        {
            while (b->total < _PTHREAD_BARRIER_FLAG)
            {
                /* Wait until enough threads enter the barrier */
                SleepConditionVariableCS(&b->cv, &b->m, INFINITE);
            }
            
            b->total--;
            
            /* Get entering threads to wake up */
            if (b->total == _PTHREAD_BARRIER_FLAG) WakeAllConditionVariable(&b->cv);
            
            LeaveCriticalSection(&b->m);
            
            return 0;
        }
    }

    static int pthread_barrierattr_init(void **attr)
    {
        *attr = NULL;
        return 0;
    }

    static int pthread_barrierattr_destroy(void **attr)
    {
        /* Ignore attr */
        (void) attr;
        
        return 0;
    }

    static int pthread_barrierattr_setpshared(void **attr, int s)
    {
        *attr = (void *) s;
        return 0;
    }

    static int pthread_barrierattr_getpshared(void **attr, int *s)
    {
        *s = (int) (size_t) *attr;

        return 0;
    }
   
---------   
Spinlocks
---------

There are many ways to implement spinlocks. 
We will choose the simplest way because it doesn't suffer slowdowns when the number of threads 
is higher than the number of processors. 
Since the whole point of spinlocks is speed, it doesn't matter that Microsoft doesn't export a spinlock API. 
Using a simple exchange-based algorithm:


    #define PTHREAD_SPINLOCK_INITIALIZER 0
    typedef long pthread_spinlock_t;
    static int pthread_spin_init(pthread_spinlock_t *l, int pshared)
    {
        (void) pshared;
        
        *l = 0;
        return 0;
    }

    static int pthread_spin_destroy(pthread_spinlock_t *l)
    {
        (void) l;
        return 0;
    }

    /* No-fair spinlock due to lack of knowledge of thread number */
    static int pthread_spin_lock(pthread_spinlock_t *l)
    {
        while (_InterlockedExchange(l, EBUSY))
        {
            /* Don't lock the bus whilst waiting */
            while (*l)
            {
                YieldProcessor();
                
                /* Compiler barrier.  Prevent caching of *l */
                _ReadWriteBarrier();
            }
        }
        
        return 0;
    }

    static int pthread_spin_trylock(pthread_spinlock_t *l)
    {
        return _InterlockedExchange(l, EBUSY);
    }

    static int pthread_spin_unlock(pthread_spinlock_t *l)
    {
        /* Compiler barrier.  The store below acts with release symmantics */
        _ReadWriteBarrier();
        
        *l = 0;
        
        return 0;
    }
    pthread_once()
    
The final part of the synchronization API to implement is pthread_once() 
This is designed for safe initialization of objects. 
Thus we use a similar algorithm to that described for singletons



    #define PTHREAD_ONCE_INIT 0
    typedef long pthread_once_t;

    typedef struct _pthread_cleanup _pthread_cleanup;
    struct _pthread_cleanup
    {
        void (*func)(void *);
        void *arg;
        _pthread_cleanup *next;
    };

    #define pthread_cleanup_push(F, A)\
    {\
        const _pthread_cleanup _pthread_cup = {(F), (A), pthread_self()->clean};\
        _ReadWriteBarrier();\
        pthread_self()->clean = (_pthread_cleanup *) &_pthread_cup;\
        _ReadWriteBarrier()
        
    /* Note that if async cancelling is used, then there is a race here */
    #define pthread_cleanup_pop(E)\
        (pthread_self()->clean = _pthread_cup.next, (E?_pthread_cup.func(_pthread_cup.arg):0));}

    static void _pthread_once_cleanup(pthread_once_t *o)
    {
        *o = 0;
    }

    static pthread_t pthread_self(void);
    static int pthread_once(pthread_once_t *o, void (*func)(void))
    {
        long state = *o;

        _ReadWriteBarrier();
        
        while (state != 1)
        {
            if (!state)
            {
                if (!_InterlockedCompareExchange(o, 2, 0))
                {
                    /* Success */
                    pthread_cleanup_push(_pthread_once_cleanup, o);
                    func();
                    pthread_cleanup_pop(0);
                    
                    /* Mark as done */
                    *o = 1;
                    
                    return 0;
                }
            }
            
            YieldProcessor();
            
            _ReadWriteBarrier();
            
            state = *o;
        }
        
        /* Done */
        return 0;
    }

The extra complexity in the above comes due to the fact that cancellation may happen during 
the function passed to pthread_once(). 
The Posix specification states that if the function is cancelled, 
then the pthread_once_t variable needs to return to the "uninitialized" state. 
To do this, we use the magic pthread_cleanup_push() and pthread_cleanup_pop() 
macros to record a cleanup function on a cleanup list.

----------
Cancelling
----------

The next big part of the pthreads API to implement are the functions related to cancellation. 
Posix describes two types of cancellation. 
The first is synchronous, and is happens by explicit calls to pthread_testcancel(), 
and to other library functions explicitly listed as being cancellation points. 
We can add these cancellation points by using macros. For example:


    #define accept(...) (pthread_testcancel(), accept(__VA_ARGS__))
    #define aio_suspend(...) (pthread_testcancel(), aio_suspend(__VA_ARGS__))
    #define clock_nanosleep(...) (pthread_testcancel(), clock_nanosleep(__VA_ARGS__))
    #define close(...) (pthread_testcancel(), close(__VA_ARGS__))

    /* More here */

    /* Even for library functions defined as macros */
    #undef getwc
    #define getwc(...) (pthread_testcancel(), getwc(__VA_ARGS__))
    #undef getwchar
    #define getwchar(...) (pthread_testcancel(), getwcahr(__VA_ARGS__))

/* And so on */

A complete list of the cancellation points defined by Posix is in the pthread header on the downloads page. 
You may obviously use extra macro overrides to wrap windows API functions that may block.

The second class of cancellation required for Posix support is asynchronous cancellation. 
This should happen "immediately" without a wait until the next cancellation point. 
The problem is that this is typically implemented in unix operating systems via signals. 
Unfortunately, Microsoft windows doesn't support signals in quite the same way. 
(There is rudimentary support in the CRT, but it is not comprehensive enough for us.) 
Thus we require another way of triggering a cancellation in another thread. 
One way that will work most of the time is to modify the thread descriptor block. 
By changing the instruction pointer to point to our cancellation handler, 
we can cause the cancelled thread to alter its flow of execution. 
The only problem is that this will not unblock a thread blocked in the kernel. 
Anyway, ignoring this problem, we have


    #define PTHREAD_CANCEL_DISABLE 0
    #define PTHREAD_CANCEL_ENABLE 0x01

    #define PTHREAD_CANCEL_DEFERRED 0
    #define PTHREAD_CANCEL_ASYNCHRONOUS 0x02

    #define PTHREAD_CANCELED ((void *) 0xDEADBEEF)

    volatile long _pthread_cancelling;

    static void _pthread_invoke_cancel(void)
    {
        _pthread_cleanup *pcup;
        
        _InterlockedDecrement(&_pthread_cancelling);
        
        /* Call cancel queue */
        for (pcup = pthread_self()->clean; pcup; pcup = pcup->next)
        {
            pcup->func(pcup->arg);
        }
            
        pthread_exit(PTHREAD_CANCELED);
    }

    static void pthread_testcancel(void)
    {
        if (_pthread_cancelling)
        {
            pthread_t t = pthread_self();
            
            if (t->cancelled && (t->p_state & PTHREAD_CANCEL_ENABLE))
            {
                _pthread_invoke_cancel();
            }
        }
    }

    static int pthread_cancel(pthread_t t)
    {
        if (t->p_state & PTHREAD_CANCEL_ASYNCHRONOUS)
        {
            /* Dangerous asynchronous cancelling */
            CONTEXT ctxt;
            
            /* Already done? */
            if (t->cancelled) return ESRCH;
            
            ctxt.ContextFlags = CONTEXT_CONTROL;
            
            SuspendThread(t->h);
            GetThreadContext(t->h, &ctxt);
    #ifdef _M_X64
            ctxt.Rip = (uintptr_t) _pthread_invoke_cancel;
    #else
            ctxt.Eip = (uintptr_t) _pthread_invoke_cancel;
    #endif
            SetThreadContext(t->h, &ctxt);
            
            /* Also try deferred Cancelling */
            t->cancelled = 1;
        
            /* Notify everyone to look */
            _InterlockedIncrement(&_pthread_cancelling);
            
            ResumeThread(t->h);
        }
        else
        {
            /* Safe deferred Cancelling */
            t->cancelled = 1;
        
            /* Notify everyone to look */
            _InterlockedIncrement(&_pthread_cancelling);
        }
        
        return 0;
    }
    
The above uses the _pthread_cancelling variable to fast-path the common case where no cancellation is happening. 
(Having a thread have to check its thread-local cancellation flag all the time is relatively slow.)

One possible way to fix the case where a thread is blocked in the kernel is to use a kernel driver. 
This choice is used by the old windows pthread library. 
Another possibility which may work is to use a Doppelganger thread. 
The algorithm goes as follows: Suspend the cancelled thread. 
The current thread can then save its stack pointer and thread segment register somewhere 
in the thread-local space of the suspended thread. 
This thread can then impersonate the suspended thread by stealing its stack and thread segment selector. 
By running the standard cancellation routines in the Doppelganger thread, the required cleanup functions can be run in the correct context. Finally, once that is done, the Doppelganger can then restore its state to what it was previously and then call the low-level TerminateThread() function to kill the suspended thread (even if it was in kernel mode).

So why isn't the above implemented? 

The problem is that the thread-stealing requires low level assembly to work. 
Unfortunately, Microsoft has decided that all 64bit assembly should use compiler intrinsics instead of inline assembly. 
The problem here is that Microsoft hasn't thought of everything, and the particular instructions required are not exported as compiler intrinsics. The correct way to implement this on 64bit would be to have a separate assembly file to compile along side the C code. This, however, does not fit with our goal of having a single .h file for the implementation of the library. (Another problem is that it is difficult to portably hook the cleanup of the CRT to prevent memory leaks - but this may perhaps be fixed through the use of a new thread as the Doppelganger.)

-------------------------------
Thread Creation and Destruction
-------------------------------

pthread_create() unfortunately has a slightly different interface than _beginthreadex(). 
This deficiency may be fixed by using a wrapper function that in turn will call the thread main function. 
We can hide the extra information inside pthread_t. 
Similarly, we can store the return value inside pthread_t so that pthread_join() will work correctly. 
Together with a few extra details to complete the library, the resulting pthread_t definition is:


    struct _pthread_v
    {
        void *ret_arg;
        void *(* func)(void *);
        _pthread_cleanup *clean;
        HANDLE h;
        int cancelled;
        unsigned p_state;
        int keymax;
        void **keyval;
        
        jmp_buf jb;
    };

    typedef struct _pthread_v *pthread_t;

Where pthread_t is a pointer to a structure that has the required information. 
Using the above definition, we can implement the thread creation and destruction functions.


    typedef struct pthread_attr_t pthread_attr_t;
    struct pthread_attr_t
    {
        unsigned p_state;
        void *stack;
        size_t s_size;
    };

    #define PTHREAD_CREATE_JOINABLE 0
    #define PTHREAD_CREATE_DETACHED 0x04

    #define PTHREAD_EXPLICT_SCHED 0
    #define PTHREAD_INHERIT_SCHED 0x08

    #define PTHREAD_SCOPE_PROCESS 0
    #define PTHREAD_SCOPE_SYSTEM 0x10

    #define PTHREAD_DESTRUCTOR_ITERATIONS 256

    #define PTHREAD_PRIO_NONE 0
    #define PTHREAD_PRIO_INHERIT 8
    #define PTHREAD_PRIO_PROTECT 16
    #define PTHREAD_PRIO_MULT 32
    #define PTHREAD_PROCESS_SHARED 0
    #define PTHREAD_PROCESS_PRIVATE 1

    int _pthread_concur;
    pthread_once_t _pthread_tls_once;
    DWORD _pthread_tls;

    static int _pthread_once_raw(pthread_once_t *o, void (*func)(void))
    {
        long state = *o;

        _ReadWriteBarrier();
        
        while (state != 1)
        {
            if (!state)
            {
                if (!_InterlockedCompareExchange(o, 2, 0))
                {
                    /* Success */
                    func();
                    
                    /* Mark as done */
                    *o = 1;
                    
                    return 0;
                }
            }
            
            YieldProcessor();
            
            _ReadWriteBarrier();
            
            state = *o;
        }
        
        /* Done */
        return 0;
    }
    
    static void pthread_tls_init(void)
    {
        _pthread_tls = TlsAlloc();
        
        /* Cannot continue if out of indexes */
        if (_pthread_tls == TLS_OUT_OF_INDEXES) abort();
    }

    static void _pthread_cleanup_dest(pthread_t t)
    {
        int i, j;
        
        for (j = 0; j < PTHREAD_DESTRUCTOR_ITERATIONS; j++)
        {
            int flag = 0;
        
            for (i = 0; i < t->keymax; i++)
            {
                void *val = t->keyval[i];
                
                if (val)
                {
                    pthread_rwlock_rdlock(&_pthread_key_lock);
                    if ((uintptr_t) _pthread_key_dest[i] > 1)
                    {
                        /* Call destructor */
                        t->keyval[i] = NULL;
                        _pthread_key_dest[i](val);
                        flag = 1;
                    }
                    pthread_rwlock_unlock(&_pthread_key_lock);
                }
            }
        
            /* Nothing to do? */
            if (!flag) return;
        }
    }

    static pthread_t pthread_self(void)
    {
        pthread_t t;
        
        _pthread_once_raw(&_pthread_tls_once, pthread_tls_init);
        
        t = TlsGetValue(_pthread_tls);
        
        /* Main thread? */
        if (!t)
        {
            t = malloc(sizeof(struct _pthread_v));
            
            /* If cannot initialize main thread, then the only thing we can do is abort */
            if (!t) abort();
        
            t->ret_arg = NULL;
            t->func = NULL;
            t->clean = NULL;
            t->cancelled = 0;
            t->p_state = PTHREAD_DEFAULT_ATTR;
            t->keymax = 0;
            t->keyval = NULL;
            t->h = GetCurrentThread();
            
            /* Save for later */
            TlsSetValue(_pthread_tls, t);
            
            if (setjmp(t->jb))
            {
                /* Make sure we free ourselves if we are detached */
                if (!t->h) free(t);
                
                /* Time to die */
                _endthreadex(0);
            }
        }
        
        return t;
    }

    static int pthread_getconcurrency(int *val)
    {
        *val = _pthread_concur;
        return 0;
    }

    static int pthread_setconcurrency(int val)
    {
        _pthread_concur = val;
        return 0;
    }

    #define pthread_getschedparam(T, P, S) ENOTSUP
    #define pthread_setschedparam(T, P, S) ENOTSUP
    #define pthread_getcpuclockid(T, C) ENOTSUP

    static int pthread_exit(void *res)
    {
        pthread_t t = pthread_self();

        t->ret_arg = res;
        
        _pthread_cleanup_dest(t);
        
        longjmp(t->jb, 1);
    }

    static unsigned _pthread_get_state(pthread_attr_t *attr, unsigned flag)
    {
        return attr->p_state & flag;
    }

    static int _pthread_set_state(pthread_attr_t *attr, unsigned flag, unsigned val)
    {
        if (~flag & val) return EINVAL;
        attr->p_state &= ~flag;
        attr->p_state |= val;
        
        return 0;
    }

    static int pthread_attr_init(pthread_attr_t *attr)
    {
        attr->p_state = PTHREAD_DEFAULT_ATTR;
        attr->stack = NULL;
        attr->s_size = 0;
        return 0;
    }

    static int pthread_attr_destroy(pthread_attr_t *attr)
    {
        /* No need to do anything */
        return 0;
    }

    static int pthread_attr_setdetachstate(pthread_attr_t *a, int flag)
    {
        return _pthread_set_state(a, PTHREAD_CREATE_DETACHED, flag);
    }

    static int pthread_attr_getdetachstate(pthread_attr_t *a, int *flag)
    {
        *flag = _pthread_get_state(a, PTHREAD_CREATE_DETACHED);
        return 0;
    }

    static int pthread_attr_setinheritsched(pthread_attr_t *a, int flag)
    {
        return _pthread_set_state(a, PTHREAD_INHERIT_SCHED, flag);
    }

    static int pthread_attr_getinheritsched(pthread_attr_t *a, int *flag)
    {
        *flag = _pthread_get_state(a, PTHREAD_INHERIT_SCHED);
        return 0;
    }

    static int pthread_attr_setscope(pthread_attr_t *a, int flag)
    {
        return _pthread_set_state(a, PTHREAD_SCOPE_SYSTEM, flag);
    }

    static int pthread_attr_getscope(pthread_attr_t *a, int *flag)
    {
        *flag = _pthread_get_state(a, PTHREAD_SCOPE_SYSTEM);
        return 0;
    }

    static int pthread_attr_getstackaddr(pthread_attr_t *attr, void **stack)
    {
        *stack = attr->stack;
        return 0;
    }

    static int pthread_attr_setstackaddr(pthread_attr_t *attr, void *stack)
    {
        attr->stack = stack;
        return 0;
    }

    static int pthread_attr_getstacksize(pthread_attr_t *attr, size_t *size)
    {
        *size = attr->s_size;
        return 0;
    }

    static int pthread_attr_setstacksize(pthread_attr_t *attr, size_t size)
    {
        attr->s_size = size;
        return 0;
    }

    #define pthread_attr_getguardsize(A, S) ENOTSUP
    #define pthread_attr_setgaurdsize(A, S) ENOTSUP
    #define pthread_attr_getschedparam(A, S) ENOTSUP
    #define pthread_attr_setschedparam(A, S) ENOTSUP
    #define pthread_attr_getschedpolicy(A, S) ENOTSUP
    #define pthread_attr_setschedpolicy(A, S) ENOTSUP


    static int pthread_setcancelstate(int state, int *oldstate)
    {
        pthread_t t = pthread_self();
        
        if ((state & PTHREAD_CANCEL_ENABLE) != state) return EINVAL;
        if (oldstate) *oldstate = t->p_state & PTHREAD_CANCEL_ENABLE;
        t->p_state &= ~PTHREAD_CANCEL_ENABLE;
        t->p_state |= state;
        
        return 0;
    }

    static int pthread_setcanceltype(int type, int *oldtype)
    {
        pthread_t t = pthread_self();
        
        if ((type & PTHREAD_CANCEL_ASYNCHRONOUS) != type) return EINVAL;
        if (oldtype) *oldtype = t->p_state & PTHREAD_CANCEL_ASYNCHRONOUS;
        t->p_state &= ~PTHREAD_CANCEL_ASYNCHRONOUS;
        t->p_state |= type;
        
        return 0;
    }

    static int pthread_create_wrapper(void *args)
    {
        struct _pthread_v *tv = args;
        int i, j;
        
        _pthread_once_raw(&_pthread_tls_once, pthread_tls_init);
        
        TlsSetValue(_pthread_tls, tv);
            
        if (!setjmp(tv->jb))
        {
            /* Call function and save return value */
            tv->ret_arg = tv->func(tv->ret_arg);
            
            /* Clean up destructors */
            _pthread_cleanup_dest(tv);
        }
        
        /* If we exit too early, then we can race with create */
        while (tv->h == (HANDLE) -1)
        {
            YieldProcessor();
            _ReadWriteBarrier();
        }
        
        /* Make sure we free ourselves if we are detached */
        if (!tv->h) free(tv);
        
        return 0;
    }

    static int pthread_create(pthread_t *th, pthread_attr_t *attr, void *(* func)(void *), void *arg)
    {
        struct _pthread_v *tv = malloc(sizeof(struct _pthread_v));
        unsigned ssize = 0;
        
        if (!tv) return 1;
        
        *th = tv;
        
        /* Save data in pthread_t */
        tv->ret_arg = arg;
        tv->func = func;
        tv->clean = NULL;
        tv->cancelled = 0;
        tv->p_state = PTHREAD_DEFAULT_ATTR;
        tv->keymax = 0;
        tv->keyval = NULL;
        tv->h = (HANDLE) -1;
        
        if (attr)
        {
            tv->p_state = attr->p_state;
            ssize = attr->s_size;
        }
        
        /* Make sure tv->h has value of -1 */
        _ReadWriteBarrier();

        tv->h = (HANDLE) _beginthreadex(NULL, ssize, pthread_create_wrapper, tv, 0, NULL);
        
        /* Failed */
        if (!tv->h) return 1;
        
        
        if (tv->p_state & PTHREAD_CREATE_DETACHED)
        {
            CloseHandle(tv->h);
            _ReadWriteBarrier();
            tv->h = 0;
        }

        return 0;
    }

    static int pthread_join(pthread_t t, void **res)
    {
        struct _pthread_v *tv = t;
        
        pthread_testcancel();
        
        WaitForSingleObject(tv->h, INFINITE);
        CloseHandle(tv->h);
        
        /* Obtain return value */
        if (res) *res = tv->ret_arg;
        
        free(tv);

        return 0;
    }

    static int pthread_detach(pthread_t t)
    {
        struct _pthread_v *tv = t;
        
        /*
         * This can't race with thread exit because
         * our call would be undefined if called on a dead thread.
         */
        
        CloseHandle(tv->h);
        _ReadWriteBarrier();
        tv->h = 0;
        
        return 0;
    }
    
Most of the above code is fairly trivial. 
The only non-obvious thing is the use of a jump buffer to transfer control in pthread_exit(). 
This is done so that C++ destructors may be called as the stack is unwound. 
A simple call to terminate the thread may not clean up exactly what we want otherwise. 
Another subtlety is pthread_self() This function will transparently convert 
a non-pthreads created thread into one with the extra information required for the pthreads API. 
Thus if you don't want to use pthread_create(), 
and instead use the Microsoft windows thread creation API, you can. 
The only downside is that pthread_self() has no documented failure mode, so if it can't allocate memory 
it calls abort() as there is nothing else it can do.

--------------------
Thread Specific Data
--------------------

The last significant part of the pthreads API is that for thread specific data. 
This can be implemented in two different ways in windows. 
The simplest is to use __declspec(thread). 
Unfortunately, that technique doesn't work correctly for dll's. 
Thus we are forced to use the other interface based on TlsAlloc(). 
This is the reason why the variable _pthread_tls is used above. 
By using a resizable array within the thread-specific data we can store the information required by 
the Posix specification.

The data-keys are able to be implemented as a global resizable array protected by read-write locks.


    #define PTHREAD_KEYS_MAX (1<<20)

    pthread_rwlock_t _pthread_key_lock;
    long _pthread_key_max;
    long _pthread_key_sch;
    void (**_pthread_key_dest)(void *);

    typedef unsigned pthread_key_t;

    static int pthread_key_create(pthread_key_t *key, void (* dest)(void *))
    {
        int i;
        long nmax;
        void (**d)(void *);

        if (!key) return EINVAL;
        
        pthread_rwlock_wrlock(&_pthread_key_lock);
        
        for (i = _pthread_key_sch; i < _pthread_key_max; i++)
        {
            if (!_pthread_key_dest[i])
            {
                *key = i;
                if (dest)
                {
                    _pthread_key_dest[i] = dest;
                }
                else
                {
                    _pthread_key_dest[i] = (void(*)(void *))1;
                }
                pthread_rwlock_unlock(&_pthread_key_lock);
                
                return 0;
            }
        }
	
        for (i = 0; i < _pthread_key_sch; i++)
        {
            if (!_pthread_key_dest[i])
            {
                *key = i;
                if (dest)
                {
                    _pthread_key_dest[i] = dest;
                }
                else
                {
                    _pthread_key_dest[i] = (void(*)(void *))1;
                }
                pthread_rwlock_unlock(&_pthread_key_lock);
                
                return 0;
            }
        }
	
        if (!_pthread_key_max) _pthread_key_max = 1;
        if (_pthread_key_max == PTHREAD_KEYS_MAX)
        {
            pthread_rwlock_unlock(&_pthread_key_lock);
            
            return ENOMEM;
        }
        
        nmax = _pthread_key_max * 2;
        if (nmax > PTHREAD_KEYS_MAX) nmax = PTHREAD_KEYS_MAX;
        
        /* No spare room anywhere */
        d = realloc(_pthread_key_dest, nmax * sizeof(*d));
        if (!d)
        {
            pthread_rwlock_unlock(&_pthread_key_lock);
            
            return ENOMEM;
        }
	
        /* Clear new region */
        memset((void *) &d[_pthread_key_max], 0, (nmax-_pthread_key_max)*sizeof(void *));
        
        /* Use new region */
        _pthread_key_dest = d;
        _pthread_key_sch = _pthread_key_max + 1;
        *key = _pthread_key_max;
        _pthread_key_max = nmax;
        
        if (dest)
        {
            _pthread_key_dest[*key] = dest;
        }
        else
        {
            _pthread_key_dest[*key] = (void(*)(void *))1;
        }

        pthread_rwlock_unlock(&_pthread_key_lock);
        
        return 0;
    }

    static int pthread_key_delete(pthread_key_t key)
    {
        if (key > _pthread_key_max) return EINVAL;
        if (!_pthread_key_dest) return EINVAL;
        
        pthread_rwlock_wrlock(&_pthread_key_lock);
        _pthread_key_dest[key] = NULL;
        
        /* Start next search from our location */
        if (_pthread_key_sch > key) _pthread_key_sch = key;
        
        pthread_rwlock_unlock(&_pthread_key_lock);
        
        return 0;
    }
    
Finally, the thread specific data for the keys is stored inside the struct pointed to by the pthread_t pointer.


    static void *pthread_getspecific(pthread_key_t key)
    {
        pthread_t t = pthread_self();
        
        if (key >= t->keymax) return NULL;
        
        return t->keyval[key];

    }

    static int pthread_setspecific(pthread_key_t key, const void *value)
    {
        pthread_t t = pthread_self();

        if (key > t->keymax)
        {
            int keymax = (key + 1) * 2;
            void **kv = realloc(t->keyval, keymax * sizeof(void *));
            
            if (!kv) return ENOMEM;
            
            /* Clear new region */
            memset(&kv[t->keymax], 0, (keymax - t->keymax)*sizeof(void*));
            
            t->keyval = kv;
            t->keymax = keymax;
        }
        
        t->keyval[key] = (void *) value;
        
        return 0;
    }
    
-----------------------    
Unimplemented Functions
-----------------------

There finally remains some functions that exist in the Posix Threading API, 
but do not correspond well to the Microsoft windows API. The first of these is pthread_atfork(). 
It is designed to make sure the fork() system call works as intended in multithreaded programs, 
allowing the child process to know that it is able to use all its required data due to it being in a consistent state. 
However, windows doesn't have the fork() function, so this routine can be a simple stub.

Similarly, windows lacks good support for signals. Thus pthread_kill() and pthread_sigmask 
also can be implemented as stubs since porting a signal-using
application over will require much extra work anyway.

    /* No fork() in windows - so ignore this */
    #define pthread_atfork(F1,F2,F3) 0

    /* Windows has rudimentary signals support */
    #define pthread_kill(T, S) 0
    #define pthread_sigmask(H, S1, S2) 0

A full implementation of this library is on the downloads page. 
It is licensed under the BSD license. However, 
be aware that it does use undocumented windows internals for a few of the synchronization primitives. 
These may be changed by Microsoft in the future, 
so probably should not be relied on for anything important.

[winpthreads.h](https://locklessinc.com/articles/pthreads_on_windows/)

