output: shell_mycopy.o read.o parse.o execute.o commands.o launch.o
	gcc -o sh shell_mycopy.o read.o parse.o execute.o commands.o launch.o 
	
shell_mycopy.o: shell_mycopy.c
	gcc -c shell_mycopy.c
	
read.o: read.c
	gcc -c read.c
	
parse.o: parse.c
	gcc -c parse.c

execute.o: execute.c
	gcc -c execute.c

commands.o: commands.c 
	gcc -c commands.c
	
launch.o: launch.c 
	gcc -c launch.c

clean:
	rm *.o sh 
