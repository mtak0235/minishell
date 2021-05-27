#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv, char *envp[])
{
    int x;
    pid_t pid;
    int fd[2];
    int fd2;
    x = 0;


    pipe(fd);
    printf("%d, %d\n", fd[0], fd[1]);

    pid = fork();//자식 생성
    if (pid > 0)//부모일 경우
    {
        dup2(fd[1], 1);//표준출력 1이 fd[1]을 복제(고정)한다.
        //dup2함수
//      int dup2(int fd, int fd2);
//      #include <unistd.h>
//      fd2가 fd를 복제한다
        write(fd[1], "hello\n", 6);//컴퓨터는 hello를 fd[1]을 통해서 읽는다.

        waitpid(pid, 0, 0);//자식이 끝날때까지 기다림
    }
    else if (pid == 0)
    {
        char ch[100];//buffer를 만들고
        dup2(fd[0], 0);//(컴퓨터가)표준입력을 통해서 fd[0]에 복제(고정)한다.
        read(0, ch, 6);//read함수로 ch버퍼를 읽음(컴퓨터가)
        sleep(2);//2초동안 기다림
        write(1, ch, 6);//표준출력(컴퓨터가)으로 ch를 읽어들임
    }

    return (0);
}