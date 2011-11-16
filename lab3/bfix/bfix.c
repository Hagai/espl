#include <stdlib.h>
#include <stdio.h>
#include "diff.h"

#include <unistd.h>
#include <getopt.h>


int main(int argc, char **argv){
	int help, reverse, message;
	help = 0;
	reverse = 0;
	message = 0;
	int opt;
	char *optstring = "hrm";
	int i;

	
	for(opt = getopt(argc, argv, optstring); opt != -1; opt = getopt(argc, argv, optstring)){
		switch(opt){
		  case 'r':
			reverse =1;
			break;
		  case 'h':
			help = 1;
			break;
		  case 'm':
			message = 1;
			break;
		  default:
			printf("unknown option. Exiting...\n",opt);
			return 0;
		}
	}
	

	if (argc-optind != 2){
		printf("USAGE: [OPTIONS] file differences\n",argv[0]);
		return 1;
	}
	
	if(help ==1){
		printf("USAGE: [OPTIONS] file differences\n",argv[0]);
		printf("OPTIONS\n");
		printf("-h  print a summary of options and exit\n");
		printf("-r  reverse the differences\n");
		printf("-m  print a message each time a change is applied\n");
		return 0;
	}
	
	char *filename = argv[optind];
	char *filename_diff = argv[optind+1];
	FILE *fileStream = fopen(filename, "rb+");
	FILE *fileStream_diff = fopen(filename_diff, "rb+");
	
	
	long byteNum;
	char c=0;
	// sorry about the bad name...
	int not_endOfFile;
	
	byteNum = 1;
	not_endOfFile = 1;
	struct diff diff;

	int LINE_LENGTH = 80;
	
	char line[LINE_LENGTH];
	int lineNum = 1;
	
	//read the lines in diff file
	while(fgets(line, LINE_LENGTH, fileStream_diff) != NULL ){
			parsediff(line, &diff);
			lineNum++;
			//check if the file has the old value
			fseek(fileStream, diff.offset-1, SEEK_SET);
			fread((char *)&c, sizeof(char), 1, fileStream);

			if (reverse == 1){
			  int temp;
			  temp = diff.old;
			  diff.old = diff.new;
			  diff.new = temp;
			}
			if(c == diff.old)
			{
				
				fseek(fileStream, diff.offset-1, SEEK_SET);
				fwrite((char *)&diff.new, sizeof(char), 1, fileStream);
				if(message == 1){
					printf("setting byte at offset %ld from %u to %u\n",diff.offset, diff.old, diff.new);
				}
			  
			}
			else{
				printf("old value doesn't much\n");
			}
		}
	
	
	fclose(fileStream);
	fclose(fileStream_diff);
	
	return 0; 
}