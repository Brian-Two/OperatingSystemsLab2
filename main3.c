#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

void child_process();
// parent process
int main (){
  pid_t pid;
  int i; 
  for (i = 0; i<2; i++){
    pid = fork(); // stores two child pids
    if (pid == 0) 
				child_process();
    else if (pid<0) 
				exit(1);
  }

  for (i=0; i < 2; i++){
    int status;
    pid_t completed_pid = wait(&status);
    printf("Child Pid: %d has completed\n", (int)completed_pid);
  }
  return 0;
}

// run one child process
void child_process(){
  pid_t pid = getpid();
  srandom((unsigned)time(NULL) ^ (unsigned)pid); // seed RNG
  int n = 1 + (random() % 30); // 1..30 iterations
  int i;
  for (i=0; i < n; i++){
    int t = 1 + (random() % 10); // 1..10 seconds
    printf("Child Pid: %d is going to sleep!\n", (int)pid);
    fflush(stdout);
    sleep(t);
    pid_t parent_pid = getppid();
    printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n", (int)pid, (int)parent_pid);
    fflush(stdout);
  }
  exit(0);
}


