#include <stdio.h>
#include <string.h>

int main( int argc, const char* argv[] )
{
	if (argc == 3){
		int LINE_LENGTH = 80;
		//get the name of the first file
		const char* File1 = argv[1];
		const char* File2 = argv[2];
		const char* mode = "r";
		//open stream for the file
		FILE* File1_handler = fopen(File1, mode);
		FILE* File2_handler = fopen(File2, mode);
		char line1[LINE_LENGTH];
		char line2[LINE_LENGTH];
		int equal;
		int lineNum = 1;		
		while(fgets(line1, LINE_LENGTH, File1_handler) != NULL ){
			//for each line
			fgets(line2, LINE_LENGTH, File2_handler);
			equal = strcmp(line1, line2);
			if (equal != 0){
				printf( "-%d: %s",lineNum, line1 );
				printf( "+%d: %s",lineNum, line2 );
			}
			lineNum++;

		}
		
		
		
		if (fclose(File1_handler) != 0){
			printf( "\ncant close first file... \n\n");
		}
		if (fclose(File2_handler) != 0){
			printf( "\ncant close second file... \n\n");
		}

	}
	else{
		printf("USEGE: complines <first file> <second file>\n");
	}
}
