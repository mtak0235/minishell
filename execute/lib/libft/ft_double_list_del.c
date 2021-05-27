/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_list_del.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: napark <napark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 19:00:53 by napark            #+#    #+#             */
/*   Updated: 2021/05/23 19:08:50 by napark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_double_list_del(t_double_list *lst, void (*del)(void*))
{
    if (lst->prev != NULL)
        lst->prev->next = lst->next;
    if (lst->next != NULL)
        lst->next->prev = lst->prev;
    del(lst->data);
    free(lst);
    
}