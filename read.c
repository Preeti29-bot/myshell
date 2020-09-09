#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>

#include "read.h"

char *read_command(void)
{
  //the command line is placed in cmd
  char *cmd = NULL;
  //getline allocates required memory to cmd
  int size = 0;
  
  if(getline(&cmd,&size,stdin) == -1){
      if((int)(stdin) == EOF || (int)(stdin) == '\n'){
          //end of the command line
          exit(EXIT_SUCCESS);
      }
      else{
          exit(EXIT_FAILURE);
      }
  }
  return cmd;
}

