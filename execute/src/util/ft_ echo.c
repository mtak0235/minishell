#include <execute.h>

static int  put_argument_std(t_cmd *cmd, int check, int i)
{
    if (cmd->token[i])
        
}


static int check_flag(t_cmd *cmd, int *i)
{
    int result;
    char *str;
    int j;

    j = 0;
    result = 0;
    while (cmd->token[*i])
    {
        str = cmd->token[*i];//tokening한 것을 받고
        j = 1;
        if (ft_strncmp(str, "-n", 2))
        {
            while (str[j++] == 'n')
                if (str[j] == 1)
                    return (result);
        }
        else
        {
            result = 0;
            return result;//없음
        }
        result = 1;
        (*i)++;
    }
    return (result);
    //echo -n$HOME = 엔터없이 PATH값 출력
    //echo $text = 
    //echo test = test
}

//echo -n$HOME
int     ft_echo(t_cmd *cmd)
{
    int     check;
    int     i;

    i = 1;//커멘더는 앞에서 처리
    check = 0;
    if (check_flag(cmd, &i))//0, 1
        check = 1;
    put_argument_std(cmd, check, i);


}