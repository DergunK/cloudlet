.text
.global interrupt
.extern int_handler
handler_helper:
	
    pushq %rax
    pushq %rbx
    pushq %rcx
    pushq %rdx
    pushq %rsi
    pushq %rdi
    pushq %rbp
    pushq %r8
    pushq %r9
    pushq %r10
    pushq %r11
    pushq %r12
    pushq %r13
    pushq %r14
    pushq %r15
    movq %rsp, %rdi
    cld
    call int_handler
    popq %r15
    popq %r14
    popq %r13
    popq %r12
    popq %r11
    popq %r10
    popq %r9
    popq %r8
    popq %rbp
    popq %rdi
    popq %rsi
    popq %rdx
    popq %rcx
    popq %rbx
    popq %rax
    addq $16, %rsp
    iretq


handler0: subq $8,%rsp
	  pushq $0
	  jmp handler_helper
handler1: subq $8,%rsp
	  pushq $1
	  jmp handler_helper
handler2: subq $8,%rsp
  	  pushq $2
	  jmp handler_helper
handler3: subq $8,%rsp
	  pushq $3
	  jmp handler_helper
handler4: subq $8,%rsp
	  pushq $4
	  jmp handler_helper
handler5: subq $8,%rsp
	  pushq $5
	  jmp handler_helper
handler6: subq $8,%rsp
	  pushq $6
	  jmp handler_helper
handler7: subq $8,%rsp
	  pushq $7
	  jmp handler_helper
handler8: subq $8,%rsp
	  pushq $8
	  jmp handler_helper
handler9: subq $8,%rsp
	  pushq $9
	  jmp handler_helper
handler10: subq $8,%rsp
	   pushq $10
	   jmp handler_helper
handler11: subq $8,%rsp
	   pushq $11
	   jmp handler_helper
handler12: subq $8,%rsp
	   pushq $12
	   jmp handler_helper
handler13: subq $8,%rsp
	   pushq $13
	   jmp handler_helper
handler14: subq $8,%rsp
	   pushq $14
	   jmp handler_helper
handler15: subq $8,%rsp
	   pushq $15
	   jmp handler_helper
handler16: subq $8,%rsp
	   pushq $16
	   jmp handler_helper
handler17: subq $8,%rsp
	   pushq $17
	   jmp handler_helper
handler18: subq $8,%rsp
	   pushq $18
	   jmp handler_helper
handler19: subq $8,%rsp
	   pushq $19
	   jmp handler_helper
handler20: subq $8,%rsp
	   pushq $20
	   jmp handler_helper
handler21: subq $8,%rsp
	   pushq $21
	   jmp handler_helper
handler22: subq $8,%rsp
	   pushq $22
	   jmp handler_helper
handler23: subq $8,%rsp
	   pushq $23
	   jmp handler_helper
handler24: subq $8,%rsp
	   pushq $24
	   jmp handler_helper
handler25: subq $8,%rsp
	   pushq $25
	   jmp handler_helper
handler26: subq $8,%rsp
	   pushq $26
	   jmp handler_helper
handler27: subq $8,%rsp
	   pushq $27
	   jmp handler_helper
handler28: subq $8,%rsp
	   pushq $28
	   jmp handler_helper
handler29: subq $8,%rsp
	   pushq $29
	   jmp handler_helper
handler30: subq $8,%rsp
	   pushq $30
	   jmp handler_helper
handler31: subq $8,%rsp
	   pushq $31
	   jmp handler_helper
handler32: subq $8,%rsp
	   pushq $32
	   jmp handler_helper

interrupt:
	.quad handler0
	.quad handler1
	.quad handler2
	.quad handler3
	.quad handler4
	.quad handler5
	.quad handler6
	.quad handler7
	.quad handler8
	.quad handler9
	.quad handler10
	.quad handler11
	.quad handler12
	.quad handler13
	.quad handler14
	.quad handler15
	.quad handler16
	.quad handler17
	.quad handler18
	.quad handler19
	.quad handler20
	.quad handler21
	.quad handler22
	.quad handler23
	.quad handler24
	.quad handler25
	.quad handler26
	.quad handler27
	.quad handler28
	.quad handler29
	.quad handler30
	.quad handler31
	.quad handler32
