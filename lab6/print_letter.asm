section	.text
	global print_letter
	extern prsym

print_letter:					;void print_letter(char c, int iline)
	push ebp
	mov ebp, esp
	
	mov	ecx, [esp+8]	;c_ (code)= c
	movzx	ecx,cl
	mov	ebx, [esp+12]	;b=iline
	sub	ecx, 32		;
	push 	ecx
	push 	ebx
	call 	prsym
	
	sub	esp,8		;return stack
	
	pop ebp
	ret
