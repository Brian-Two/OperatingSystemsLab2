#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>       // fork, sleep, getpid, getppid
#include <sys/types.h>    // pid_t
#include <sys/wait.h>     // wait, WIFEXITED, WEXITSTATUS
#include <time.h>         // time

void child_process();

// parent process
int main() {
  int pid;
  int i;

  /* fork two children */
  for (i = 0; i < 2; i++) {
    pid = fork();
    if (pid == 0) {
      child_process();    /* child runs and exits(0) */
    } else if (pid < 0) {
      perror("fork");
      exit(1);
    }
  }

  /* parent waits for both */
  for (i = 0; i < 2; i++) {
    int status;
    int completed_pid = wait(&status);
    if (completed_pid > 0) {
      if (WIFEXITED(status)) {
        printf("Child Pid: %d has completed with exit status: %d\n",
               completed_pid, WEXITSTATUS(status));
      } else {
        printf("Child Pid: %d has completed (non-normal exit)\n", completed_pid);
      }
    }
  }

  return 0;
}

/* run one child process */
void child_process() {
  int pid = getpid();
  int parent_pid = getppid();

  /* seed RNG uniquely per child */
  srand((unsigned)time(NULL) ^ (unsigned)pid);

  /* random iterations: 1..30 */
  int n = 1 + (rand() % 30);
  int i;

  for (i = 0; i < n; i++) {
    /* sleep time: 1..10 seconds */
    int t = 1 + (rand() % 10);
    printf("Child Pid: %d is going to sleep for %d seconds!\n", pid, t);
    fflush(stdout);

    sleep((unsigned)t);

    /* refresh parent pid (in case it changed) */
    parent_pid = getppid();
    printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n", pid, parent_pid);
    fflush(stdout);
  }

  exit(0);
}