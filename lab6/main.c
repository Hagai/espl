
#include "font.h"

void sys_puts(char*);
void sys_putsl(char*);
int char2int(char c);
/*
int char2int(char c){
	int i = c+0;
	return i;
}
*/

int mystrlen(char *str);
/*

{
int i;

for(i = 0; str[i] != '\0'; i++)
	{}

return i;
}
*/

void print_letter(char c, int iline);
/*
{
  
    //printf("the number of %c is %d \n",c,c);
    int code = c;
    //printf("the number of %c is %d \n",c,code);
    
    prsym(code - 32, iline);
}
*/

void print_word(char *word, int iline);
/*
 * {
	//printf("DEBUG: im in print_word/n");
	int len =  mystrlen(word);
	//printf("first word is in length: %d\n",len);
	
	int i;
	for(i=0; i<len; ++i){
	  print_letter(word[i], iline);
	  
	}
}
*/

//print line i
void prsym(int idx, int iline);
/*
 { 
	//int iline;
	
	//char *(*symbol)[SYMBOL_HEIGHT] = &alphabet[idx];
	//for(iline = 0; iline!=SYMBOL_HEIGHT; ++iline)  //for every line
		////printf("%s", (*symbol)[iline]);
	//sys_puts((*symbol)[iline]);
	
	sys_puts(alphabet[idx][iline]);
}
*/

int main(int argc, char **argv) {
	int i;
	int iline;
	char *nl = "\n";
	for(iline = 0; iline!=SYMBOL_HEIGHT; ++iline){	  
	 for(i=1; i!=argc; ++i) {
	   
		print_word(argv[i], iline);

		if(i!=argc-1){}
		
		char *space= " ";
		print_word(space, iline);
	 }
	sys_puts(nl); 
	}
	 
	/* 
	switch(argc) {
	case 1: {
			int idx;
			for(idx = 0;; ++idx) {
				if(!alphabet[idx][0])
					break;
				prsym(idx);
			}
		}
		break;
	case 2:
		prsym(atoi(argv[1]));
		break;
	default:
		printf("print all available symbols or a symbol by the given index in ASCII art.\n\nusage: %s [symbol-index]\n", argv[0]);
		return 1;
	}
	*/
	return 0;
}
