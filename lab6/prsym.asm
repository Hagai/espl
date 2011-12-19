section	.text
	extern sys_puts
	global prsym
	

prsym:					;void prsym(int idx, int iline)
	push ebp
	mov ebp, esp

	mov	eax,[esp+4]		;get the char c into dl
	movzx	eax,al
	add	eax,'0'			;add ascii code for 0 to c
	
	pop ebp
	ret

section	.data
  extern alpabet;



//print line i
void prsym(int idx, int iline) { 
	//int iline;
	
	char *(*symbol)[SYMBOL_HEIGHT] = &alphabet[idx];
	//for(iline = 0; iline!=SYMBOL_HEIGHT; ++iline)  //for every line
		////printf("%s", (*symbol)[iline]);
	sys_puts((*symbol)[iline]);
}