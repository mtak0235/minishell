#ifndef MINISHELL_H
#define MINSISHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libft.h>

typedef struct  s_hist
{
    char *content;
    struct s_hist *prev;
    struct s_hist *next;
}       t_jist;//history 구조체

typedef struct  s_red
{
    
}               t_red;//리다이렉션

typedef struct s_cmd
{
    char    **args;
    struct s_cmd    *child;
    struct s_cmd    *sible;
    struct s_cmd    *prev;
    int             type;
    int             pipes[2];
    t_red           re;
}           t_cmd;

typedef struct 
{
    /* data */
};


#endif