/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_list_size.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: napark <napark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 18:53:51 by napark            #+#    #+#             */
/*   Updated: 2021/05/23 19:26:24 by napark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int     ft_double_list_size(t_double_list    *lst)
{
    int count;

    count = 0;
    while (lst != NULL)
    {
        lst = lst->next;
        ++count;
    }
    return (count);
}