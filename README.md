# myshell
[![Work in Repl.it](https://classroom.github.com/assets/work-in-replit-14baed9a392b3a25080506f3b7b6d57f295ec2978f6f33ec97e36a161684cbe9.svg)](https://classroom.github.com/online_ide?assignment_repo_id=3071078&assignment_repo_type=AssignmentRepo)
# Assignment1
An example Makefile is provided. Modify it to compile your shell. Dummy files shell.c and ls.c are given here. The main shell binary must be named "shell". Modify ls.c or delete it if not required and put all other files that are there.

SHELL IMPLEMENTATION IN C
---------------------------------------------------------------				
The implementation involves 3 major steps:

1. READING THE COMMAND

The read_command() function reads the command entered by the user and stores it in a string whose pointer is "command". 

2. SPLITTING THE COMMAND into arguments

The parse_command() function takes the line read by the read_command() function as input and returns an array of words obtained by splitting the command entered. 

3. EXECUTING THE COMMAND

The execute_command() function executes the command using different function calls present in the execute.h file for each command by taking the array of strings returned by parse_command() as inputs.
The function returns the status of the execution. In this shell, though the execution fails, a status of 1 is returned, following by an error message. This is done so that the user will be able to work on the shell without restarting it everytime.
The process is terminated when the command "exit" is invoked.

Finally, we free up the memory so that it can be used for other processes

This implementation comes with a makefile which creates an executable file (sh) by compiling all the files. Make sure the makefile is in the same direcotry as the other files

To run the code: 
user@user-myshell:~$ make
And an executable file "sh" is created. Do './sh' to get the output

READING THE COMMAND
---------------------------------------------------------------		

This function uses the getline function to read the command line entered by the user. The getline function reads until the newline character or End of File(EOF) is encountered and then returns the line read back to the main function. 

SPLITTING THE COMMAND
---------------------------------------------------------------		

This function splits the command into arguments and stores the arguments in an array. It uses the whitespace as a seperator. 
The fucnction uses a 2 dimensional buffer array (arr) to store the seperated words from the command line untill a null character is encountered. Then these words are transfered into a 1 dimensional dynamic array (arguments) which is appended with a null at the end. 

EXECUTING THE COMMANDS
---------------------------------------------------------------		

Here, a command is executed using two ways - by calling the execvp or by calling functions written manually. The array command_names[] consists of all the commands which are executed by manually and the array builtin_command_names consists of commands which are executed by calling exec(). 
The function takes the array of parsed words (args[]) as input. 
The process begins by checking if the first word of the array (which is the command name) is present in any of the command_name arrays. 

The function launch_builtin() is called when the command name matches with an entry of the builtin_command_names[]. The function command_func() is called when the command name matches with an entry of the command_names[].

NOTE: The functions executed manually do not include any flags for the commads as mentioned in their manual pages

EXECUTING BUILTIN COMMANDS
---------------------------------------------------------------		

In this function, we use fork() and exec() to create a new process for the command to be executed. The parent process is the shell program and the child process is the command entered by the user (args[0]). This command is passed as an argument to execvp(). 
When the execvp() is called, a copy of the parent process is craeted. Uopn reading the argument passed to the execvp (command), the execvp loads the program file corresponding to that command and overwrites the parent process in the copy. 
Execvp() returns an integer ( positiove for successful execution and negetive for failed execution)

EXECUTING COMMANDS MANUALLY
---------------------------------------------------------------		

Below are functions for different commands. A function is executed when the user entered command matechs with that function. 

Each function returns 1 to the main() irrespective of whether the execution succeded or failed (in case of failure, it prints an error message). This prevents from restarting the shell always.

Command's Description: 

1. cd - 
Changes the present directory to the input direcotry entered by the user.
Syntax: user@user-myshell:~$ cd DirectoryName
Returns an error message incase of no input directory or failed execution

2. exit - 
Exits the shell 
Syntax: user@user-myshell:~$ exit

3. ls - 
Returns a list of all files and direcotires present in the input directory given by the user. IN case of no inputs, the files in current directory are returned. 
The files are sorted in alphabetical order.
Syntax: user@user-myshell:~$ ls DirectoryName
		user@user-myshell:~$ ls
		 
4. pwd - 
Prints the name of the current/working directory. Donot require any arguments
Syntax: user@user-myshell:~$ pwd

5. mkdir - 
Creates a new directory in the current directory if it doesnot exits. In case the file already exists, a message is printed. The directory name is given as input argument.
Syntax: user@user-myshell:~$ mkdir DirectoryName

6. grep - 
Searches for an input pattern in the file given as input by the user and returns all lines containing the pattern. 
Syntax: user@user-myshell:~$ grep pattern FileName
The pattern argument is compulsory to execute the command. IN case the filename is not mentioned, then the command consideres the input text from the stdin. 
It returns the lines where the matching is found in dofferent lines. If no match is found or the file is not accesable, a print message is thrown.

7. cat - 
Prints the contents of the input text file specified by the user. 
Syntax: user@user-myshell:~$ cat [fileName...]
It takes multiple files as inputs and prints the contents of each file. 
Returns a error message in case of any error

8. cp - 
Copy the input files or Directories to the destination file or Directory. 
Synatx: user@user-myshell:~$ cp [Source FileName/DirName...] [Destination FileName/DirName]
The input can be either a filename or a directory name. 
In case of multiple argumnets, the last argument is considered as Destination. 
If the file doesnot exists, a file is created with the same name as the source filename. (by fopen)
 
