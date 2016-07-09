.text
.global machine_switch

machine_switch:
	# address of the new sp is arg1
	# address of the current tcb is arg2
	# need to store all required registered for old tcb
	# restore all required registers from the new tcb
	# then when you return, you should get to the new thread

    push    %rbp
    push    %rax
    push    %rbx
    push    %rcx
    push    %rdx
    push    %rsi
    push    %rdi
    push    %r8
    push    %r9
    push    %r10
    push    %r11
    push    %r12
    push    %r13
    push    %r14
    push    %r15
    mov     %rsp, (%rsi)    # Store the old stack pointer in the old TCB

    mov     (%rdi), %rsp    # Get the new stack pointer from the new TCB
    pop     %r15
    pop     %r14
    pop     %r13
    pop     %r12
    pop     %r11
    pop     %r10
    pop     %r9
    pop     %r8
    pop     %rdi
    pop     %rsi
    pop     %rdx
    pop     %rcx
    pop     %rbx
    pop     %rax
    pop     %rbp

    #jmp (%rbp)

	ret 

