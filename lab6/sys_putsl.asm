section	.text
	global sys_putsl
	
	extern length			;length is implemented in length.c

sys_putsl:					;void sys_putsl()
	push ebp
	mov ebp, esp

	;get the pointer to str (esp?)


	;call c function to get str len
	push dword [esp + 8]		; prepare args for function call	
	call	length			; call the function
	mov	edx,eax			; move the var to the right register
	
	add esp,4	;to guard stack (BETTER THEN POP)
	
	mov dword ecx,[esp + 8]	;message to write
	mov	ebx,1	;file descriptor (stdout)
	mov	eax,4	;system call number (sys_write)
	int	0x80	;call kernel
	
	
	
	;call c function to get str len
	push 	msg		; prepare args for function call	
	call	length			; call the function
	mov	edx,eax			; move the var to the right register
	
	add esp,4	;to guard stack (BETTER THEN POP)
	
	mov	ecx,msg	;message to write
	mov	ebx,1	;file descriptor (stdout)
	mov	eax,4	;system call number (sys_write)
	int	0x80	;call kernel
	
	
	pop ebp
	ret

section	.data

msg	db	0xa,0	;our dear string




