section	.text
	global ahalan
	
	extern myPuts			;length is implemented in main.c


ahalan:					;void ahalan()
	push ebp
	mov ebp, esp

			;send args to main.c:myPuts
	
	push dword [esp + 8]
	call myPuts
	
	add esp,4

	pop ebp
	ret
