/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_listlast.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: napark <napark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 18:56:15 by napark            #+#    #+#             */
/*   Updated: 2021/05/23 19:33:26 by napark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "libft.h"

t_double_list       *ft_double_listlast(t_double_list *lst)
{
    while (lst->next)
        lst = lst->next;
    return (lst);
}