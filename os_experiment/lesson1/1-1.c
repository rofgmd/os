#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
int main()
	{
		pid_t pid;
		printf("PID before fork():%d\n",(int)getpid());
		pid=fork();
		if(pid<0)
			printf("error in fork!\n");
		else if (0==pid)
			printf("I'm the child process,CurpPID is %d,ParentPID is %d\n",pid,(int)getpid());
		else
			printf("I'm the parent process,childPID is %d,ParentPID is %d\n",pid,(int)getpid());

	}	
