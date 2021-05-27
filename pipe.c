#include "libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int ac, char **av, char **env)
{
    char *str = "/bin/ls -al";
    char *str2 = "usr/bin/grep main";
    char **tmp1 = ft_split(str, ' ');
    char **tmp2 = ft_split(str2, ' ');
    char buf[1024];
    int fd[2];

    pid_t pid;
    int status;

    pipe(fd);
    pid = fork();
    printf("forked\n");
    if (pid == 0)
    {
        close(fd[0]);
        dup2(fd[1], 1);
        read(fd[1], buf,100);
        printf("%s\n", buf);
        close(fd[1]);
        execve(tmp1[0], tmp1, env);
    }
    pid = fork();
    if (pid == 0)
    {
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);
        execve(tmp2[0], tmp2, env);
    }
    close(fd[1]);
    close(fd[0]);
    waitpid(pid, &status, 0);
}