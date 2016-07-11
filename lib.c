#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "threadlib.h"
#include "queue.h"

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
    int state; /* 0 for sleeping 1 for running*/
    void *malloc_addr;
};

typedef struct tcb tcb_t;
typedef struct tcb *TCB;

Queue *queue;
int flag = 1;

/**
 * assembly code for switching 
 * @sp -- new stack to switch 
 * return sp of the old thread
 * 
 * Switching 
*/
void machine_switch(tcb_t *newthread /* addr. of new TCB */, tcb_t *oldthread /* addr. of old TCB */);
void switch_threads(tcb_t *newthread /* addr. of new TCB */, tcb_t *oldthread /* addr. of old TCB */);
void init_thread_queue(void);
void rem_thread(tcb_t *newthread);
		    

/** Data structures and functions to support thread control box */

void init_thread_queue(void) {
    if (flag == 1) {
        queue = queueCreate();
    }

    flag = 0;
}

/** end of data structures */

void switch_threads(tcb_t *newthread /* addr. of new TCB */, tcb_t *oldthread /* addr. of old TCB */) {
  /* This is basically a front end to the low-level assembly code to switch. */
 
    machine_switch(newthread, oldthread);
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
    //ptr = (void *)(((long int) ptr & (-1 << 4)) + 0x10);

    return ptr;
}

int create_thread(void (*ip)(void)) {
    init_thread_queue();
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

    tcb_t *thread_tcb = (tcb_t *) malloc(sizeof(tcb_t));

    enqueue(queue, (void *) thread_tcb);

    thread_tcb -> malloc_addr = stack;
    thread_tcb -> state = 0;
    long int *align_top = (void *)(((long int) stack & (-1 << 4)) + STACK_SIZE);

    *(align_top-1) = (long int) ip;
    *(align_top-2) = (long int) align_top;

    thread_tcb -> sp = align_top - 16;

#ifdef DEBUG
    PRINT("arg ip         = %p\n", ip);
    PRINT("align_top ptr  = %p\n", align_top);
    PRINT("align_top - 1  = %p\n", align_top-1);
    PRINT("align_top - 2  = %p\n", align_top-2);
    PRINT("*(align_top-1) = %p\n", (void *) *(align_top-1));
    PRINT("*(align_top-2) = %p\n", (void *) *(align_top-2));
    PRINT("TCB = %p size  = %d\n", thread_tcb, queue -> size);
    PRINT("thread_tcb     = %p\n", thread_tcb);
    PRINT("thread_tcb->sp = %p\n", thread_tcb->sp);
    PRINT("&(tcb->sp)     = %p\n", &(thread_tcb->sp));
    PRINT("queue peek = %p\n", queuePeek(queue));
#endif

    return 0;
}

void yield() {
    /* thread wants to give up the CPU just call the scheduler to pick the next thread. */
    void  *current;
    dequeue(queue, &current);
#ifdef DEBUG
    PRINT("current = %p\n", current);
    PRINT("new thr = %p\n", queuePeek(queue));
#endif

    enqueue(queue, current);
    switch_threads(current, queuePeek(queue));
}


void delete_thread(void) {
    /* When a user-level thread calls this you should not 
    * let it run any more but let others run
    * make sure to exit when all user-level threads are dead */

    void *remove;
    dequeue(queue, &remove);

    tcb_t *thread_tcb = (tcb_t *)remove;
#ifdef DEBUG
    PRINT("delete thr = %p\n", (void *) thread_tcb);
#endif
}


void stop_main(void) { 
    /* Main function was not created by our thread management system. 
    * So we have no record of it. So hijack it. 
    * Do not put it into our ready queue, switch to something else.*/

#ifdef DEBUG
    PRINT("queue peek = %p\n", queuePeek(queue));
#endif

    rem_thread(queuePeek(queue));
}
