#include <stdlib.h>
#include <stdio.h>
#include "diff.h"

int main(int argc, char **argv){

	if (argc < 2){
		printf("USAGE: [OPTIONS] file differences\n",argv[0]);
		return 1;
	}

	char *filename = argv[1];  
	FILE *fileStream = fopen(filename, "rb+");
	
	long byteNum;
	char c=0;
	// sorry about the bad name...
	int not_endOfFile;
	
	byteNum = 1;
	not_endOfFile = 1;
	
	while ((not_endOfFile == 1)){
		printf("debug: reading byte %ld\n",byteNum);
		fflush(stdout);
		not_endOfFile = fread((char *)&c, sizeof(char), 1, fileStream);

		if (not_endOfFile == 0){
			printf("debug: end of file\n");
			not_endOfFile = 0;
		}
		printf("debug: byte %ld in file is %u\n",byteNum, c);
		byteNum ++;
	}
	
	fclose(fileStream);
	return 0; 
}