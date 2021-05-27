/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_list_clear.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: napark <napark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 19:09:30 by napark            #+#    #+#             */
/*   Updated: 2021/05/23 19:12:04 by napark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_double_list_clear(t_double_list **lst, void  (*del)(void *))
{
    t_double_list    *tmp;

    while (*lst)
    {
        tmp = (*lst)->next;
        if (del != NULL)
            del((*lst)->data);
        free(*lst);
        *lst = tmp;
    }
    *lst = 0;
}