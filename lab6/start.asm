section .text
	global _start
	extern sys_putc
	extern print_word
_start:

;argc = esp, argv = esp+4	
	xor	ebx,ebx	;ebx will be the line inx
.LINE:
	cmp ebx,6
	je	.LINE_END
	
	
	xor	edx,edx
	add	edx,1
.ARGC:
	
	cmp	edx,[esp]
	je	.ARGC_END
	
	push	edx
	push	ebx
	mov	eax, esp
	add	eax,12
	sal	edx,2
	add	eax,edx
	mov	eax,[eax]
	push	eax
	call	print_word
	add	esp,4
	pop	ebx
	pop	edx
	

	;if we're not on the last word put space	
	mov	ecx,[esp]
	sub	ecx,1
	cmp	ecx,edx
	je	.LAST_PARAM

	;print space
	pusha
	push space
	call	sys_putc
	add	esp,4
	popa

.LAST_PARAM:	

	add	edx,1
	jmp	.ARGC
.ARGC_END:
	pusha
	push	10
	call	sys_putc
	add	esp,4
	popa
	add	ebx,1
	jmp	.LINE

.LINE_END:
	
	

			
        mov     ebx,eax
	mov	eax,1
	int 0x80

section .data
	nl	db	10
	space	db	' '
;	extern	SYMBOL_HEIGHT
