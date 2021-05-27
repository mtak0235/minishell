#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

extern  char **environ;

int     main(int argc, char *argv[])
{
    char **new_argv;
    char command[] = "ls";
    int index;
    int errno;

    errno = 1;
    new_argv = (char **)malloc(sizeof(char *) * (argc + 1));

    new_argv[0] = command;

    for (index = 1; index < argc; index++){
        new_argv[index] = argv[index];
    }

    //절대 값 위치
    new_argv[argc] = NULL;
    if (execve("/usr/bin/ls", new_argv, environ) == -1){
        fprintf(stderr, "프로그램 실행 error : %s\n", strerror(errno));
        return 1;
    }
    printf("error !! ls 명령어 라인이 아닙니다.\n");
    return (0);
    
}
