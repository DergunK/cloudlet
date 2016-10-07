.text
.global interrupt
.global int_handler

handler0:
	pushq $0;
	pushq $0;
	jmp handler_helper;
handler1:
	pushq $0;
	pushq $1;
	jmp handler_helper;
handler2:
	pushq $0;
	pushq $2;
	jmp handler_helper;
handler3:
	pushq $0;
	pushq $3;
	jmp handler_helper;
handler4:
	pushq $0;
	pushq $4;
	jmp handler_helper;
handler5:
	pushq $0;
	pushq $5;
	jmp handler_helper;
handler6:
	pushq $0;
	pushq $6;
	jmp handler_helper;
handler7:
	pushq $0;
	pushq $7;
	jmp handler_helper;
handler8:
	pushq $8;
	jmp handler_helper;
handler9:
	pushq $0;
	pushq $9;
	jmp handler_helper;
handler10:
	pushq $10;
	jmp handler_helper;
handler11:
	pushq $11;
	jmp handler_helper;
handler12:
	pushq $12;
	jmp handler_helper;
handler13:
	pushq $13;
	jmp handler_helper;
handler14:
	pushq $14;
	jmp handler_helper;
handler15:
	pushq $0;
	pushq $15;
	jmp handler_helper;
handler16:
	pushq $0;
	pushq $16;
	jmp handler_helper;
handler17:
	pushq $17;
	jmp handler_helper;
handler18:
	pushq $0;
	pushq $18;
	jmp handler_helper;
handler19:
	pushq $0;
	pushq $19;
	jmp handler_helper;
handler20:
	pushq $0;
	pushq $20;
	jmp handler_helper;
handler21:
	pushq $0;
	pushq $21;
	jmp handler_helper;
handler22:
	pushq $0;
	pushq $22;
	jmp handler_helper;
handler23:
	pushq $0;
	pushq $23;
	jmp handler_helper;
handler24:
	pushq $0;
	pushq $24;
	jmp handler_helper;
handler25:
	pushq $0;
	pushq $25;
	jmp handler_helper;
handler26:
	pushq $0;
	pushq $26;
	jmp handler_helper;
handler27:
	pushq $0;
	pushq $27;
	jmp handler_helper;
handler28:
	pushq $0;
	pushq $28;
	jmp handler_helper;
handler29:
	pushq $0;
	pushq $29;
	jmp handler_helper;
handler30:
	pushq $0;
	pushq $30;
	jmp handler_helper;
handler31:
	pushq $0;
	pushq $31;
	jmp handler_helper;

handler_helper:
	
	pushq %rdi
	movq 8(%rsp), %rdi 

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

	popq %rdi

	addq $16, %rsp

	iretq

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
