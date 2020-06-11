SYSCALL32 = 0x80
SYSEXIT   = 1
SYSREAD   = 3
SYSWRITE  = 4

STDIN  = 0
STDOUT = 1

.data
_a_size:      .zero 4
_b_size:      .zero 4
_result_size: .zero 4


.global multiply_as
.text
multiply_as:
push %ebp
mov  %esp, %ebp

subl $20, %esp

movl 12(%ebp), %eax
mov $4, %edx
mull %edx
movl %eax, _a_size

movl 20(%ebp), %eax
mov $4, %edx
mull %edx
movl %eax, _b_size

movl _a_size, %eax
addl _b_size, %eax
movl %eax, _result_size

xor %ebx, %ebx

loop_outer:				# outer loop
    movl 8(%ebp), %eax		# loads first 4-byte part   INPUT_A
    addl %ebx, %eax
    mov (%eax), %eax
    xor %ecx, %ecx				# clears index for second loop

loop_inner:			# inner loop
		pushl %ecx			# pushes register values on the stack
		pushl %ebx			# for later use
    pushl %eax

		xor  %edx, %edx			# clears edx register

    movl 16(%ebp), %edx
    addl %ecx, %edx
    mov (%edx), %edx

    mull %edx

    addl %ecx, %ebx			# calculates index for second number
		clc	        		# clearing CF flag
    movl 24(%ebp), %ecx
    addl %ebx, %ecx
    addl %eax, (%ecx)
    #addl %eax, BUFFER(,%ebx,1) 	# low part of the product
    pushf
    addl $4, %ecx			# can increment because value is on the stack
    popf		#adcl %edx, BUFFER(,%ebx,1)	# high part of the product
    adcl %edx, (%ecx)
    jnc no_carry

  carry:					# recursive carry handling
		clc
		addl $4, %ecx
		addl $1, (%ecx)
		jc carry

  no_carry:
    popl %eax
		popl %ebx			# pops register values
		popl %ecx
		addl $4, %ecx
		cmp _b_size, %ecx
		jl loop_inner			# condition for inner loop

  addl $4, %ebx
	cmp _a_size, %ebx
	jl loop_outer				# condition for outer loop

exit:
clr %eax

addl $20, %esp
popl %ebp
ret

/* vim: ft=gas :
*/
