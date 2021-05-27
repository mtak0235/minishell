#include <stdio.h>
#include <unistd.h>
 
int        main(void)
{
    pid_t pid;
 
 	printf("before fork\n");
    
	pid = fork();
    if (pid == 0)
    {
		printf("pid == 0\n");
		printf("child process: %d\n", getpid());
	}
    else if (pid > 0)
    {
		printf("pid == %d\n", pid);
		printf("parent process: %d, child pid: %d\n", getpid(), pid);
	}		
    else
    {
        printf("fork error\n");
        return (-1);
    }
    printf("end pid: %d\n", getpid());
    return (0);
}
