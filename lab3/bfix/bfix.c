#include <stdlib.h>
#include <stdio.h>
#include "diff.h"

int main(int argc, char **argv){
    
	if (argc < 3){
		printf("USAGE: [OPTIONS] file differences\n",argv[0]);
		return 1;
	}
	
	char *filename = argv[1];
	char *filename_diff = argv[2];
	FILE *fileStream = fopen(filename, "rb+");
	FILE *fileStream_diff = fopen(filename_diff, "rb+");
	
	
	long byteNum;
	char c=0;
	// sorry about the bad name...
	int not_endOfFile;
	
	byteNum = 1;
	not_endOfFile = 1;
	struct diff diff;
	
	
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
	
	int LINE_LENGTH = 80;
	
	char line[LINE_LENGTH];
	int lineNum = 1;
	
	//read the lines in diff file
	while(fgets(line, LINE_LENGTH, fileStream_diff) != NULL ){
			//for each line
			printf("debug: reading line %d:%s\n",lineNum,line);
			fputdiff(stdout, parsediff(line, &diff));
			lineNum++;
			//check if the file has the old value
			fseek(fileStream, diff.offset-1, SEEK_SET);
			fread((char *)&c, sizeof(char), 1, fileStream);
			printf("debug: byte at offset %ld  is %u\n",diff.offset, c);
			printf("debug: old byte at offset %ld  is %u\n",diff.offset, diff.old);
			printf("debug: new byte at offset %ld  is %u\n",diff.offset, diff.new);
			if(c == diff.old)
			{
				
				fseek(fileStream, diff.offset-1, SEEK_SET);
				fwrite((char *)&diff.new, sizeof(char), 1, fileStream);
				printf("debug: value has changed\n");
			  
			}
			else{
				printf("debug: old value doesn't much\n");
			}
		}
	
	
	//testing
	/*
	long offset;
	offset = 2;
	fseek(fileStream, offset, SEEK_SET);
	fread((char *)&c, sizeof(char), 1, fileStream);
	printf("debug: byte at offset %ld  is %u\n",offset+1, c);
	*/
	
	
	fclose(fileStream);
	fclose(fileStream_diff);
	
	return 0; 
}