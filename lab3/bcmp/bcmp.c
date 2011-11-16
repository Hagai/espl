#include <stdio.h>

int main(int argc, char *argv[]){
	if (argc != 3){
		printf("USAGE: %s [filename1] [filname2]\n",argv[0]);
		return 1;
	}

	char *filename1 = argv[1];
	char *filename2 = argv[2];
	
	FILE *fileStream1 = fopen(filename1, "rb");
	FILE *fileStream2 = fopen(filename2, "rb");
	
	// contiue reading the file until a diffrence is found or end of file reached
	int diff, endOfFile1, endOfFile2;
	char f1=0;
	char f2=0;
	int byteNum;

	byteNum = 1;
	diff = 0;
	endOfFile1 = 1;
	endOfFile2 = 1;


	// read the files until a diffrence is found 
	while ((endOfFile1 == 1) & (endOfFile2 == 1)){
		//printf("debug: reading byte %d\n",byteNum);
		fflush(stdout);
		endOfFile1 = fread((char *)&f1, sizeof(char), 1, fileStream1);
		endOfFile2 = fread((char *)&f2, sizeof(char), 1, fileStream2);

		if (endOfFile1 - endOfFile1 != 0){
			//printf("debug: end of file\n");
		}
		if (f1 != f2){
			printf("byte %d -%u +%u\n",byteNum, f1, f2);
			diff = 1;
		}
		//printf("debug: byte %d in file1 is %d & in file2 is %d\n",byteNum, f1, f2);
		byteNum ++;
	}
	

	fclose(fileStream1);
	fclose(fileStream2);

	return 0;
}