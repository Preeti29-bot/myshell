#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>

#include "parse.h"

char **parse_command(char *cmd)
{
    int size = 100;
    char **arguments = malloc(size * sizeof(char*));
    char arr[1000][1000];

    int n=0,i,j=0;
    for(i=0;1;i++)
    {
        if(cmd[i]!=' '){
            arr[n][j++]=cmd[i];
        }
        else{
            n++;
            j=0;
        }
        //stop parsing the line when encountered a null character
        if(cmd[i]=='\0')
        	break;
    }
   
    int len_arr = n+1;

    if(arguments){
		for(int i=0;i<len_arr;i++){
		    arguments[i] = arr[i];
		   
		   //reallocating memory for arguments[] incase the limit exceeds
		    if (i >= size) {
		      size += 100;
		      arguments = realloc(arguments, size * sizeof(char*));
		      if (!arguments) {
		        exit(EXIT_FAILURE);
		      }
		    }
		}
	   
	   //Each word obtained from above has a newline character at the end which is to be removed for the execution process
		int l;
		for(int i=0;i<len_arr;i++){
		    l = strlen(arguments[i]);
		    if(arguments[i][l-1] == '\n')
		        arguments[i][l-1] = 0;
		   
		}
		
		//appending the arguments with null character for execution
		arguments[len_arr] = NULL;
		return arguments;
    }
    else{
    	exit(EXIT_FAILURE);
    }
}
