section	.text
	global char2int

char2int:					;int char2int(char c)
	push ebp
	mov ebp, esp

	mov	eax,[esp+4]		;get the char c into dl
	movzx	eax,al
	add	eax,'0'			;add ascii code for 0 to c
	
	pop ebp
	ret
