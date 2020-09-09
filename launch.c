#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>

#include "launch.h"

int launch_builtin(char **args)
{
  int status;

  int r = fork();
  if (r < 0) {
  	 //error in forking
  	 perror("fork");
   
  } else if (r == 0) {
    //Child process
    // the command name (args[0) along with the arguments (args) of the commands are passed to execvp
    if (execvp(args[0], args) == -1) {
      perror("execvp");
    }
  } else {
    //Parent process
    //The parent process (shell) should wait until the child process is completed
      waitpid(r, &status, WUNTRACED);
  }

  return 1;
}
