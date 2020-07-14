
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int my_system(const char *command) {
  pid_t pid = fork();
  if (pid == 0) {
    execlp(command, command, (char *)0);
    exit(127);
  }
  else if (pid > 0) {
    if (waitpid(pid, NULL, 0) == -1) {
      perror("waitpid");
      return -1;
    }
  }
  else {
    perror("fork");
    return -1;
  }

  return 0;
}

int main(void) {
  my_system("clear"); // system("clear");
  return 0;
}


