#include <stdio.h> 
#include <stdlib.h> 

#include <string.h>

#include <sys/types.h> 
#include <sys/wait.h>

#include <unistd.h> 

//Much thanks to http://www.makelinux.net/alp/024

#define MSGSIZE 1

int main(int argc, char *argv[]){
  
 char* program = argv[1];
 char* arg_list = ++argv;
 

 printf ("running %s",program);

 int i, line_c;
 int status, p_status;
 int p[2];
 char buf[1];

 for (i = 1;i<argc-1;i++){
  printf(" %s",argv[i]);
 }
 printf("\n");
  
 pid_t child_pid; 
 
 // create a pipe
  p_status = pipe(p);
  if (p_status == -1)
 {
    perror("pipe call error");
    exit(1);
  }

  
  /* Duplicate this process. */ 
  child_pid = fork (); 
  
  if (child_pid != 0) {
    /* This is the parent process. */ 
    printf ("parent:%u\n",child_pid);
    //printf("DEBUG: enter wait\n");
    close(p[1]);
    wait(&status);
    //printf("DEBUG: done waiting\n");
    line_c = 0;

    while (read(p[0], buf, MSGSIZE)){
	if(line_c == 0){
	  printf(" 1: ");
	  line_c++;
	}
        printf("%c",buf[0]);

	if(*buf == '\n'){
	  printf(" %d: ",line_c);
	  line_c++;
        }
	//printf("loop!!!");
	}
    //WEXITSTATUS(&stat);
    printf ("exit status: %u\n",status);
    return status; 
    
  }
  else {
    printf ("child:%u\n",child_pid); 
    // duplicate file descriptor
    dup2(p[1],1);
    close(p[0]);
    /* Now execute PROGRAM, searching for it in the path.  */ 
    execvp (program,  arg_list); 

    /* The execvp  function returns only if an error occurs.  */ 
    fprintf (stderr,  "an error occurred in execvp\n"); 
    abort (); 
  } 
 

 
}
