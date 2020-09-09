// Including the header files for read_command, parse_command and execute_command functions

#include "read.h"
#include "parse.h"
#include "execute.h"

int main(int argc, char **argv)
{
  char *command;
  char **args;
  int status;

  do {
    printf("user@user-myshell:~$ ");
    command = read_command();
    args = parse_command(command);
    status = execute_command(args);

    free(command);
    free(args);
  } while (status);

  return EXIT_SUCCESS;
}
