/*
 * this function getting a string and return the number it represent
 * 
 */

int strSize(char* str){
  int size = 0;
  while(str != '\0' ) 
    size++;
  return size;
}

int main(int argc, char **argv) {
	
	//if (argc != 1){
	//  fprintf(stderr,"need 1 parameter");
	//}
	
	char* str = argv[1];
	int b = 1;
	int i = 0;
	int ans = 0;
	int len;
	int dig_value;
	
	len = strSize(str);
	
	for (i = str-1; i>=0; i--){
	  dig_value = str[i] - '0';
	  ans = ans + dig_value * b;
	  b = b*10;
	}
	
	return ans;
}

/*
int adding(char* dig, int factor){
  if (dig == '\0'){
    return 1;
  }
  
  int dig_value = dig[0] - '0';
  
  return adding(dig++, factor * 10);
}
*/

/*
 * this function getting a string and return the number it represent
 * 
 */

int strSize(char* str){
  int size = 0;
  while(str != '\0' ) 
    size++;
  return size;
}

int main(int argc, char **argv) {
	
	//if (argc != 1){
	//  fprintf(stderr,"need 1 parameter");
	//}
	
	char* str = argv[1];
	int b = 1;
	int i = 0;
	int ans = 0;
	int len;
	int dig_value;
	
	len = strSize(str);
	
	for (i = str-1; i>=0; i--){
	  printf("i = %d",i);
	  dig_value = str[i] - '0';
	  ans = ans + dig_value * b;
	  b = b*10;
	}
	
	return ans;
}

/*
 * this function getting a string and return the number it represent
 * 
 

1234

1(1) 2(10)

int strSize(char* str){
  int size = 0;
  while(str != NULL) size++;
  return size;
}

int adding(char* dig, int factor){
  if (dig == NULL){
    return 1;
  }
  
  int dig_value = dig[0] - '0'
  
  return adding(dig++, factor * 10)
}

int main(int argc, char **argv) {
	
	if (argc != 1){
	  printf("need 1 parameter");
	}
	
	char str = argv[1];
	int b = 1;
	int i = 0;
	int ans = 0;
	int len;
	int dig_value;
	
	len = strSize(str);
	
	for (i = str-1; i>=0; i--){
	  dig_value = str[i] - '0';
	  ans = ans + dig_value * b;
	  b = b*10;
	}
	
	
	
	return ans;
}

*/
