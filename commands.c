#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>

#include "commands.h"

char *command_names1[] = {
  "cd",
  "exit",
  "ls",
  "pwd",
  "mkdir",
  "grep",
  "cat",
  "cp"
};

//_________________________________________________________________________

int cmd_cd(char **args)
{
	if (args[1] != NULL) {
		// chdir changes the current directory to the input directory given by the user (args[1])
		int c = chdir(args[1]);
		if (c != 0) {
			perror("chdir");
		}
	} 
	else {
		printf("This command requires an argument \n");
	}
  
  return 1;
}

//_________________________________________________________________________

int cmd_exit(char **args)
{
  return 0;
}

//_________________________________________________________________________

int cmd_ls(char **args){
	//An array that is to store pointers to the strings containing the names of files or directories. 
	struct dirent **file_names;
	int n;
	
	if (args[0] != NULL){
		if(args[1] != NULL){
			int i=1;
			while(args[i] != NULL){
			//scandir scans through all files present in the directory
			//alphasort is given to sort the filenames alphabetically
				n = scandir(args[i],&file_names,NULL,alphasort);
				
				if(n<0){
					perror("scandir");
					return 1;
				}
				else{
					printf("%s:\n",args[i]);
					for(int i=0;i<n;i++){
						printf("%s\n ",file_names[i]->d_name);
					}
				}
				i++;
			}
		}
		else
			//In case of no arguments, current directory is considered
			//"." represents current/working directory
			n = scandir(".",&file_names,NULL,alphasort);
			if(n<0){
				perror("scandir");
				return 1;
			}
			else{
				for(int i=0;i<n;i++){
					printf("%s\n ",file_names[i]->d_name);
					free(file_names[i]);
				}
			}
	}
	else{
		exit(EXIT_FAILURE);		
	}
	// freeing up the memory
	free(file_names);
	return 1;
}

//_________________________________________________________________________

int cmd_pwd(char **args){
	char c[1000];
	//getcwd() places the current working directory path in c
	if(getcwd(c,sizeof(c)) != NULL){
		printf("%s\n", c);
	}
	else{
		perror("cwd");
	}
	return 1;
}

//_________________________________________________________________________

int cmd_mkdir(char **args){
	if (args[1] != NULL) {
    	int d; 
    	char* dirname = args[1]; 
		
		//incase the file already exists
		if (opendir(dirname)!=NULL){
			printf("File already exists\n");
			return 1;
		}
	  
		d = mkdir(dirname,0777); 
	  
		// check if directory is created or not 
		if (d == 0) 
		    printf("Directory created\n"); 
		else { 
		    printf("Unable to create directory\n"); 
		}
		
  	}
  	else{
  		printf("This command requires an argument\n");
  		}
  	
	return 1;
}

//_________________________________________________________________________

int cmd_grep(char **args){
	if (args[1] == NULL)
		printf("wgrep: searchterm[file...]\n");
	else if(args[1] == " "){
		printf("no match found");
	}
	else{
		
		char *argu = NULL;
		int size = 1000;
		char *q;
		ssize_t len = 0;
		if(args[2] != NULL){
			// all arguments are present
			int i=2;
			while(args[i] != NULL){
				FILE *f;
				f = fopen(args[i],"r");
				if(f == NULL){
					printf("wgrep: cannot open file\n");
					return 1;
				}
				else{
					//file opened
					while(getline(&argu,&len,f) != EOF){
					//strstr retrun pointer to the first occurance of substring args[1] in argu
						q = strstr(argu,args[1]);
						if(q != NULL){
							printf("match found: %s\n",argu);
							
						}
						else{
							printf("no match found\n");
						}
					}
				}
				//freeing up memory
				free(argu);
				fclose(f);
				i++;
			}
		}
		else{
			//In case of no filename mentioned, read from standard input
			char buffer[size];
			while(fgets(buffer,&size,stdin) != NULL){
				q = strstr(buffer,args[1]);
				if(q != NULL){
					printf("%s\n",buffer);
					return 1;
				}
				
			}
		}
	}
	return 1;
}

//_________________________________________________________________________

int cmd_cat(char **args){
	if(args[1] != NULL){
	// while loop for multiple files
		int i=1;
		while(args[i] != NULL){
			FILE *f;
			char c;
			f = fopen(args[i],"r");
			if(f != NULL){
				//c = fgetc(f);
				//printing the contents of the file character by character
				while((c=fgetc(f)) != EOF)
					printf("%c",c);
			}
			else{
				printf("wcat: cannot open file\n");
				//exit(EXIT_FAILURE);
				return 1;
			}
			i++;
		}
	}
	else{
		printf("Requires an argument");
	}
	printf("\n");
	return 1;
}

//_________________________________________________________________________

int cmd_cp(char **args){
	//file to file
	//file to dir
	//multiple files to file
	//multiple files to dir
	if(args[3] == NULL){
			//one source one destination
			
			FILE *s;
			FILE *d;
			
			s = fopen(args[1],"r");
			
			if(s == NULL){
				printf("source file cannot open\n");
				return 1;
			}
			
			d = fopen(args[2],"w");
			
			if(d == NULL){
			// d is either a directory or dile pointed by d cannot be opened
				printf("2nd argument is not a file\n");
				int dir;
				printf("%s\n",args[2]);
				dir = chdir(args[2]);
				
				if(dir<0){
					fclose(s);
					printf("destination file cannot be accessed\n");
					return 1;
				}
				//file to directory copying
				printf("file to dir\n");
				//file to dir
				//char filepath[1000] = {0};
				//sprintf(filepath,"/home/%s/%s", args[2], args[1]);
				//printf("dest file name: %s\n",filepath);
				FILE *f;
				f = fopen(args[1],"w");
				printf("fopen\n");
				if(f == NULL){
					printf("failed creating a file in dest directory\n");
					fclose(s);
					fclose(d);
					fclose(f);
					return 1;
				}
				printf("file created\n");
				char c;
				while((c = fgetc(s)) != EOF){
					printf("printing characters in file\n");
					//printf("%c",c);
					fputc(c,f);
				}			
				fclose(f);					
			}
			else{
				//if(args[3] == NULL){
					// file to file copying
					char c;
					while((c = fgetc(s)) != EOF){
						fputc(c,d);
					}
				/*}
				else{
					fclose(d);
					fclose(s);
					//multiple file to file
					int i = -2;
					FILE *f;
					char buffer[10000];
					int j=0;
					while(args[i+2] == NULL){
						f = fopen(args[i],"r");
						char c;
						while((c = fgetc(args[i])) != EOF){
							buffer[j] = c;
							j++;
						}
						i++;
					}
					for(int j=0;j<10000;j++){
						while(buffer[j] != EOF)
							fputc(buffer[j],args[i]);
					}					
				}*/				
			}
			//freeing up the memory
			fclose(s);
			fclose(d);
	}
	
	return 1;
}
