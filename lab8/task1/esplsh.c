#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

#define BUF_LEN 1024
static char command[BUF_LEN+1];
static int argc;
static char *argv[BUF_LEN+1];

/* read command and remove end of line if present */
int read_command() {
  int len;

  if(fgets(command, BUF_LEN, stdin)) {
    len = strlen(command);
    if(len>0 && command[len-1]=='\n')
      command[len-1] = '\0';
    return 1;
  } 
  
  return 0;
}

#define NO_SEP '\0'
#define EOC '\1'

/* split the command line into arguments and fill argv with pointers
   to the arguments */
void split_command() {
  char *s, sep;
  int between;

  between = 1;
  argc = 0;
  sep = NO_SEP;
  for(s = command; *s; ++s) {
    switch(*s) {
    case '\"': case '\'':
      if(sep==NO_SEP) {
        sep = *s;
      } else if(sep==*s) {
        sep = '\0';
      } 
      break;
    case '\\':
      ++s;
      break;
    case ' ':
      if(!sep) {
        between = 1;
        *s = '\0';
        continue;
      }
      break;
    }
    if(between) {
      argv[argc++] = s;
      between = 0;
    }
  }
  argv[argc] = NULL;
}

/* expand arguments, substitute shell variable values etc. */
void expand_args() {
  char **a = argv;
  while(*a) {
    if(**a=='"' || **a=='\'') { /* TODO: quotes can be in any place */
      *a = strdup(*a);
      memmove(*a, *a+1, strlen(*a));
      (*a)[strlen(*a)-1] = 0;
    } else {
      *a = strdup(*a);
    }
    /* TODO: eliminate escapes \ */
    /* TODO: expand environment variables */
    ++a;
  }
}

/* free arguments allocated during expansion */
void free_args() {
  char **a = argv;
  while(*a) {
    free(*a);
    ++a;
  }
}

/* run an external program */
void run_program() {
  int pid1, pid2, status, p_status;
  static char ststr[8];
  int arrow_flag = 0;
  int pipe_pos;
  int p[2];
  int fd;

  
  
  /* TODO: input, output redirection */
  /* TODO: pipelines */
  /* TODO: background commands */

  printf("DEBUG: argc=%d\n",argc);
  printf("DEBUG: last two argv are: %s, %s\n",argv[argc-2],argv[argc-1] );
  
  // check for arrow: left arrow is 2 and right arrow is 1

//

/*
find "|"
send argv to two childs
create pipe
second fork
close pipes
*/

  if(argc >= 3){
   if(!strcmp(argv[argc-2], ">")){
     printf("DEBUG:  right arrow\n");
       arrow_flag = 1;
       fd = open( argv[argc-1], O_CREAT|O_WRONLY|O_TRUNC, S_IRUSR|S_IWUSR);
       printf("DEBUG: file name is %s and fd is %d\n",argv[argc-1], fd);
       //dup2(fd,1);
       argv[argc-2] = '\0';
    }    
    else if(!strcmp(argv[argc-2], "<")){
      printf("DEBUG:  left arrow\n");
      arrow_flag = 2;
      fd = open(argv[argc-1], O_RDONLY, S_IRWXU);
      printf("DEBUG: file name is %s and fd is %d\n",argv[argc-1], fd);
      argv[argc-2] = '\0';
    } else {
	for (pipe_pos=1; pipe_pos<argc; pipe_pos++){
		if(!strcmp(argv[pipe_pos], "|")){
			printf("DEBUG:  Pipe found\n");
			printf("DEBUG: pipe pos is %d\n",pipe_pos);
			      arrow_flag = 3;
			      //fd = open(argv[argc-1], O_RDONLY, S_IRWXU);
			      //printf("DEBUG: file name is %s and fd is %d\n",argv[argc-1], fd);
			      argv[pipe_pos] = '\0';
			 break;
		}
	}
    }
  }

 //create pipe
if(arrow_flag == 3){
  p_status = pipe(p);
  if (p_status == -1)
 {
    perror("pipe call error");
    exit(1);
  }
}

  if((pid1=fork())>0) {
    // PARENT
    //if found pipe then ford for the second time.
    if(arrow_flag == 3){
	printf("DEBUG: doinf second fork\n");
	if((pid2=fork())>0) {
		// PARENT
			

	} else if(pid2==0) {
		printf("DEBUG: Im the second child!!\n");
		// CHILD 2
	    char **argv2;
	    //argv2 = argv + pipe_pos +2;
	    argv2 = &(argv[pipe_pos + 1]);
	    printf("DEBUG: command for second child is %s\n",argv2[0]);
	    printf("DEBUG: pipe pos is %d\n",pipe_pos);
	    execvp(argv2[0], argv2);
	    perror(argv2[0]);
	}
	
	  } else {
	    perror(getenv("SHELL")); /* problem while forking child2, not due to a particular program */
    }// arrow == 3

    waitpid(pid2, &status, 0);
    sprintf(ststr, "%d", status);
    setenv("?", ststr, 1);  
  } else if(pid1==0) {
    // CHILD 1
    if(arrow_flag == 1)
    {
     dup2(fd,1); 
    }
    else if (arrow_flag == 2)
    {
     dup2(fd,0); 
    }
    //printf("DEBUG1: running command: %s", argv);
    execvp(argv[0], argv);
    perror(argv[0]);
  } else {
    perror(getenv("SHELL")); /* problem while forking, not due to a particular program */
  }
  printf("DEBUG: my pid1 is %d. now Im checking arrow flag\n",pid1);
  if (arrow_flag > 0 && arrow_flag < 3){
    printf("DEBUG: closing file descriptor number %d\n", fd);
   close(fd);
  }
}

int main(int _argc, char **_argv) {
  /* clear shell variables and  re-assign a minimum set */
  clearenv();
  setenv("PATH", ":/bin:/usr/bin", 1);
  setenv("PROMPT", "$ ", 1);
  setenv("SHELL", _argv[0], 1);

  signal(SIGINT, SIG_IGN); /* ignore ^C */

  while(1) {
    printf("%s", getenv("PROMPT"));
    if(!read_command())
      break;
    split_command();
    if(!argc)
      continue;
    expand_args();
    /* process builtin commands */
    if(!strcmp(argv[0],"exit")) {
      break;
    } else if(!strcmp(argv[0],"set")) {
      if(argc!=3) {
        fprintf(stderr, "set: two arguments required\n");
        continue;
      }
      setenv(argv[1], argv[2], 1);
    } else if(!strcmp(argv[0], "cd")) {
      if(argc!=2) {
        fprintf(stderr, "cd: one argument required\n");
        continue;
      }
      if(chdir(argv[1])==-1) {
        perror("cd");
      }
    } else if(!strcmp(argv[0], "pwd")) {
      if(argc!=1) {
        fprintf(stderr, "pwd: no arguments allowed\n");
        continue;
      }
      printf("%s\n", getcwd(command, BUF_LEN));
    } else {
      /* run external command */
      run_program();
    }
    free_args();
  }
  printf("\n");

  return 0;
}
    

    
