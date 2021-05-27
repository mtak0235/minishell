/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_listadd_front.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: napark <napark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 19:12:41 by napark            #+#    #+#             */
/*   Updated: 2021/05/23 19:20:16 by napark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_double_listadd_front(t_double_list **lst, t_double_list *new_lst)
{
    if (*lst == NULL)
    {
        *lst = new_lst;
        return ;
    }
    new_lst->next = *lst;
    (*lst)->prev = new_lst;
    *lst = new_lst;
}