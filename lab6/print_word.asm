section	.text
	global print_word
	extern print_letter
	extern mystrlen
;	extern sys_puts		;debug

print_word:					;print_word(char *word, int iline)
	push ebp
	mov ebp, esp
		
	;int len =  mystrlen(word);
	push DWORD [ebp+8]
	xor	eax,eax		;eax = 0
	call	mystrlen	;now eax = len
	add	esp,4		;return stack
	;ebx will be used as counter
	xor	ebx,ebx		;ebx = 0
	
	cmp	eax,ebx		;ebx == eax
	je	.P_LETTER_END
	
	mov	ecx,[ebp+8]
	
.P_LETTER:
	PUSHA
	push DWORD [ebp+12]
	;mov	edx,[ebp+8]
	;add DWORD dl,0
	push DWORD [ecx]
	call	print_letter
	add	esp,8		;return stack
	POPA
	
	add	ebx,1
	cmp	eax,ebx
	je	.P_LETTER_END
	add  ecx,1

	jmp	.P_LETTER
	
.P_LETTER_END:	
	
	pop ebp
	ret




;void print_word(char *word, int iline){
;	//printf("DEBUG: im in print_word/n");
;	int len =  mystrlen(word);
;	//printf("first word is in length: %d\n",len);
;	
;	int i;
;	for(i=0; i<len; ++i){
;	  print_letter(word[i], iline);
;	  
;	}
;}