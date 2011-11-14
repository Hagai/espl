#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fgetname.h"
#include "namelist.h"

int WORD_LENGTH = 512;


static int
cmpstringp(const void *p1, const void *p2)
{
   /* The actual arguments to this function are "pointers to
      pointers to char", but strcmp(3) arguments are "pointers
      to char", hence the following cast plus dereference */
	const struct namestat *n1;
	const struct namestat *n2;
	n1 = (struct namestat*)p1;
	n2 = (struct namestat*)p2;
	const char *s1 = n1->name;
	const char *s2 = n2->name;
   return strcmp(s1, s2);
}

int screenReservedNames (char *word){
	//return 0 if the word is reseved
	int isReseved = 0;
	char* reservedNames[] = {"break", "int", "case", "long", "char","register", "continue","return","default", "short", "do", "sizeof", "double", "static","else", "struct", "entry", "switch", "extern", "typedef", "float", "union", "for", "unsigned", "goto", "while", "enum", "void", "const", "signed", "volatile","if", NULL};
	int i=0;
	//printf("DEBUG: checking if %s is reserved\n", word);
	while(reservedNames[i] != NULL){
		if(strcmp(word,reservedNames[i]) == 0){
			isReseved = 1;
			//printf("DEBUG: %s is reserved!\n", word);
		}
		i++;
	}
	return (1-isReseved);
}

int main(int argc, char **argv) {
	// init the variables
	int numOfFiles = argc - 1;
	namelist nl = make_namelist();
	
	//for each file
	int i_file;
	for ( i_file = 1; i_file <= numOfFiles; i_file++){
		//get the name of the file
		const char* fileName = argv[i_file];
		const char* mode = "r";	
		//printf("DEBUG: name of file number %d is %s\n",i_file, fileName);

		FILE *file_handler = fopen(fileName, mode);
		char name[WORD_LENGTH];
		if(!file_handler) {
			fprintf(stderr, "run the test in the source directory\n");
			return 1;
		}

		while(fgetname(name, sizeof(name), file_handler)){
			//printf("DEBUG: got name %s \n",name);
			if(screenReservedNames (name) != 0){
				add_name(nl, name);
				//printf("DEBUG: name %s was added \n",name);	
			}
		}
		fclose(file_handler);
	}
	qsort(nl->names,nl->size, sizeof(nl->names[0]), cmpstringp);
	int j;
	for(j = 0; j!=nl->size; ++j) {
		printf("%s %d\n",nl->names[j].name,nl->names[j].count);
	}
	return 0;
}

	

