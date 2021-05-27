/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_listadd_back.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: napark <napark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 19:20:51 by napark            #+#    #+#             */
/*   Updated: 2021/05/23 19:33:14 by napark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_double_listadd_back(t_double_list **lst, t_double_list *new_list)
{
    t_double_list       *last;

    if (*lst == NULL)
    {
        *lst = new_list;
        return;
    }
    last = ft_double_listlast(*lst);
    last->next = new_list;
    new_list->prev = last;
}