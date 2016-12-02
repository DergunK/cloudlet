.text
.code64
.extern thread_origin
.global thread_switch
.global origin

thread_switch:
  pushq %rbp
  pushq %rbx
  pushq %r12
  pushq %r13
  pushq %r14
  pushq %r15

  movq %rsp, (%rdi)
  movq %rsi, %rsp

  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp

  ret

origin:
	movq %r15, %rdi
	movq %r14, %rsi
    
	cld
	callq thread_origin
