#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int main(int argc, char **argv) {
	char a[]= {2, 4, 0, 1};
	char b[]= {2, 2, 0, 1};
	
	int ans = 0;
	
	ans = hsvmhr(a ,b);
	
	if(ans){
	  printf("equal\n");
	}
	printf("ans=%d\n",ans);
	return 0;
}