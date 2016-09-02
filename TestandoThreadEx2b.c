#define _GNU_SOURCE

#include <stdlib.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sched.h>
#include <stdio.h>

#define FIBER_STACK 1024*64

int i = 5;

int threadFunction (void* argument)
{
	printf("Thread crianca saindo\n");
	return 0;
}

int main (){
	void* stack;
	pid_t pid;

	stack = malloc (FIBER_STACK);

	//printf("\n------------------------\n" );
	if( stack == 0)
	{
		perror("malloc: could not allocate stack");
		exit(1);
	}

	printf("Criando thread criança\n");
	printf("Pid  - %d\n", pid );

	pid = clone (&threadFunction, (char*) stack + FIBER_STACK,
		SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM
		,0);

	pid = waitpid (pid, 0, 0);

	printf("Depois de waitpid\nPid  - %d\n", pid );

		free(stack);
		printf("Thread criança retornada e a pilha livre\n");

	return 0;
}
