void ahalan();

void sys_puts();

void myPuts(char* str){
  sys_puts(str);
  
}


int main(int arg, char **argv) {
  ahalan(argv[1]);
	return 0;
}
