#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "threadlib.h"

#define DEBUG
/* uncomment when you are done! */

#ifdef DEBUG
 #define PRINT printf
#else 
 #define PRINT(...)
#endif

/* information about threads */
struct tcb { 
    void *sp;  /* Address of stack pointer Keep this as first element would ease switch.S You can do something else as well.*/

    /* you will need others stuff */ 
};

typedef struct tcb tcb_t;
typedef struct tcb *TCB;

/**
 * assembly code for switching 
 * @sp -- new stack to switch 
 * return sp of the old thread
 * 
 * Switching 
*/
void machine_switch(tcb_t *newthread /* addr. of new TCB */, tcb_t *oldthread /* addr. of old TCB */);
void switch_threads(tcb_t *newthread /* addr. of new TCB */, tcb_t *oldthread /* addr. of old TCB */);
		    

/** Data structures and functions to support thread control box */ 





/** end of data structures */



void switch_threads(tcb_t *newthread /* addr. of new TCB */, tcb_t *oldthread /* addr. of old TCB */) {
  /* This is basically a front end to the low-level assembly code to switch. */
 
    assert(!printf("Implement %s",__func__));
}


/*********************************************************
 *                 Thread creation etc 
 *********************************************************/

/* Notes: make sure to have sufficient space for the stack
 * also it needs to be aligned 
 */

#define STACK_SIZE (sizeof(void *) * 1024)
#define FRAME_REGS 48 // is this correct for x86_64?

#include <stdlib.h>
#include <assert.h>

/*
 * allocate some space for thread stack.
 * malloc does not give size aligned memory 
 * this is some hack to fix that.
 * You can use the code as is. 
 */
void *malloc_stack(void);

void *malloc_stack() {
    /* allocate something aligned at 16 */
    void *ptr = malloc(STACK_SIZE + 16);
    if (!ptr) return NULL;
    ptr = (void *)(((long int) ptr & (-1 << 4)) + 0x10);

    return ptr;
}

int create_thread(void (*ip)(void)) {	
    long int *stack;
    stack = malloc_stack();
    if(!stack) return -1; /* no memory? */

    /**
    * Stack layout: last slot should contain the return address and I should have some space 
    * for callee saved registers. Also, note that stack grows downwards. So need to start from the top. 
    * Should be able to use this code without modification Basic idea: C calling convention tells us the top 
    * most element in the stack should be return ip. So we create a stack with the address of the function 
    * we want to run at this slot. 
    */

    return 0;
}

void yield() {
    /* thread wants to give up the CPU just call the scheduler to pick the next thread. */

}


void delete_thread(void) {
    /* When a user-level thread calls this you should not 
    * let it run any more but let others run
    * make sure to exit when all user-level threads are dead */ 

       
    assert(!printf("Implement %s",__func__));
}


void stop_main(void) { 
    /* Main function was not created by our thread management system. 
    * So we have no record of it. So hijack it. 
    * Do not put it into our ready queue, switch to something else.*/


    assert(!printf("Implement %s",__func__));
}
