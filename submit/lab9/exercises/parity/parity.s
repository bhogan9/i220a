	.text
	.globl get_parity
	#edi contains n
get_parity:
	test	%eax, %eax
	jpe	even_parity
	xorl	%eax, %eax
	ret
even_parity:
	mov %rax, 1
	ret
