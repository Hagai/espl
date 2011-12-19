section	.text
	global print_letter
	extern prsym
;	extern sys_puts		;debug

print_letter:					;void print_letter(char c, int iline)
	push ebp
	mov ebp, esp
	
	mov	ecx, [ebp+8]	;c_ (code)= c
	movzx	ecx,cl
	
;	push ecx	;debug	
;	push 0		;debug	
	;call prsym	;debug - print msg
	;sub	esp,8	;debug-  return stack	
	sub	ecx, 32		
	;push ecx	;debug	
	;push 0		;debug
	;call prsym	;debug - print msg
	;sub	esp,8	;debug-  return stack
	
	mov	ebx, [ebp+12]	;b=iline
	
	push ebx
	push ecx
	call 	prsym
	
	add	esp,8		;return stack
	
	pop ebp
	ret

;;;;;;;;;;;;;


;	mov	eax,[esp+4]		;get the char c into dl
;	movzx	eax,al
;	add	eax,'0'			;add ascii code for 0 to c
;	
;	pop ebp
;	ret
;;;;;;;;;;;;;;;;;;;;;;

;void print_letter(char c, int iline)

;{
;  
;    //printf("the number of %c is %d \n",c,c);
;    int code = c;
;    //printf("the number of %c is %d \n",c,code);
;    
;    prsym(code - 32, iline);
;}