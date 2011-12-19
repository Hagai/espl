section	.text
	global mystrlen

mystrlen:					;int mystrlen(char *str)
	push ebp
	mov ebp, esp
	
	
	xor     eax, eax	;a = 0 will be use for loop
	mov	edx,[ebp+8]
	jmp	.Loo
.ForEach:
	add	eax,1
	add     DWORD edx, 1
.Loo:
	mov     ecx,edx	;get arg
	mov	ecx,[ecx]	;get the char c into c
	movzx	ecx,cl
	sub	ecx,0		;if eax = 0
	
	jne	.ForEach	;if ecx == 0 then end of string eax contain the length of the string
	
	pop ebp
	ret