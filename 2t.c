#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
 
int        main(void)
{
    char *argv[] = { "ls", "-al", NULL };
    char *envp[] = { "MY_PATH=/Users/mtak/Desktop/seokim/minishell/test", NULL };
 
    printf("!!! execve !!!\n");
    if (execve("/bin/ls", argv, envp))
    {
        printf("execve error : %s\n", strerror(errno));
        return (-1);
    }
    /* 정상적으로 실행 되었을 때 여기를 실행하는지 확인 */
    printf("!!! check !!!\n");
    /* 위의 printf가 실행되지 않음 */
    return (0);
}