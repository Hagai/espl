section	.text	
	global prsym
	extern sys_puts
	extern sys_putc
	extern sys_putcI
	

prsym:					;void prsym(int idx, int iline)
	push ebp
	mov ebp, esp

	mov	ecx,[ebp+8]	;ecx = inx
	xor	edx,edx		;edx = 0	

.INX_LOOP:
	add	edx,24
	dec	ecx
	jnz	.INX_LOOP

	mov	ecx,alphabet
	add     ecx,edx		;jump to alphabet[idx] that is 24*inx (2^3 + 2^4 (8+16=24*inx))

	mov	edx,[ebp+12]	;edx = iline
	sal	edx,2		;edx = iline * 4 (pointer math)	

	add	ecx,edx

 	mov	ecx,[ecx]
	push    ecx
	call	sys_puts
	add	esp,4
		
	pop ebp
	ret

section	.data
  extern alphabet
  extern SYMBOL_HEIGHT ; not used



;//print line i
;void prsym(int idx, int iline) { 
;	//int iline;
;	
;	char *(*symbol)[SYMBOL_HEIGHT] = &alphabet[idx];
;	//for(iline = 0; iline!=SYMBOL_HEIGHT; ++iline)  //for every line
;		////printf("%s", (*symbol)[iline]);
;	sys_puts((*symbol)[iline]);
;}
;
;
;
;
;void prsym(int idx, int iline) { 
;	sys_puts(alphabet[idx][iline]);
;}
;
;alphabet[][SYMBOL_HEIGHT]
