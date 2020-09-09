#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>

#include "execute.h"
#include "commands.h"
#include "launch.h"


char *command_names[] = {
  "cd",
  "exit",
  "ls",
  "pwd",
  "mkdir",
  "grep",
  "cat",
  "cp"
};

char *builtin_command_names[] = {
  "ps",
  "pmap",
  "wget"
};

//array which stores the function names for different commands to be executed manually.
int (*command_func[]) (char **) = {
  &cmd_cd,
  &cmd_exit,
  &cmd_ls,
  &cmd_pwd,
  &cmd_mkdir,
  &cmd_grep,
  &cmd_cat,
  &cmd_cp
};

int execute_command(char **args)
{
  int i;

  if (args[0] == NULL) {
  //No command is entered by the user
    printf("Enter a command\n");
    return 1;
  }

  for (i = 0; i < (sizeof(command_names) / sizeof(char *)); i++) {
	if (strcmp(args[0], command_names[i]) == 0) {
		//executing manual functions
		return (*command_func[i])(args);
	}
  }
  
  for( int j=0; j<(sizeof(builtin_command_names) / sizeof(char *)); j++){
	if(strcmp(args[0], builtin_command_names[j]) == 0){
		//executing inbuilt functions
  		printf("builtin funtion");
  		return launch_builtin(args);
  	}
  }
  
}
