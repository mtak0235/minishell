#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
 
int        main(void)
{
    int        prcw[2]; /* parent read, child write */
    int        pwcr[2]; /* parent write, child read */
    pid_t    pid;
    int        status;
    char    res[10];
 
    if (pipe(prcw) || pipe(pwcr))
    {
        printf("pipe error: %s\n", strerror(errno));
        return (-1);
    }
    pid = fork();
    if (pid > 0) /* parent */
    {
		printf("pid == %d\n", pid);
        write(pwcr[1], "Parent", 6);
        memset(res, 0, 10);
        read(prcw[0], res, 5); res[5] = 0;
        printf("Parent Process: %s\n", res);
        while (!waitpid(pid, &status, WNOHANG));
    }
    else if (pid == 0) /* chlid */
    {
		printf("pid == %d\n", pid);
        write(prcw[1], "Child", 5);
        memset(res, 0, 10);
        read(pwcr[0], res, 6); res[6] = 0;
        printf("Chlid Process: %s\n", res);
    }
    else
    {
        printf("fork error\n");
        return (-1);
    }
    printf("end\n");
    return (0);
}