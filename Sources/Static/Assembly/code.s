	.file	"code.c"
	.section	.text.unlikely,"x"
LCOLDB0:
	.text
LHOTB0:
	.p2align 4,,15
	.globl	_sum
	.def	_sum;	.scl	2;	.type	32;	.endef
_sum:
LFB0:
	.cfi_startproc
	movl	8(%esp), %eax
	addl	4(%esp), %eax
	addl	%eax, _accum
	ret
	.cfi_endproc
LFE0:
	.section	.text.unlikely,"x"
LCOLDE0:
	.text
LHOTE0:
	.globl	_accum
	.bss
	.align 4
_accum:
	.space 4
	.ident	"GCC: (Rev5, Built by MSYS2 project) 5.3.0"
