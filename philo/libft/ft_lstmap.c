/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 19:31:16 by ychen2            #+#    #+#             */
/*   Updated: 2023/10/15 20:53:04 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	map(t_list **ans, t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;

	tmp = *ans;
	while (lst)
	{
		tmp->content = f(lst->content);
		if (lst->next)
		{
			tmp->next = malloc(sizeof(t_list));
			if (!tmp->next)
			{
				ft_lstclear(ans, del);
				return (1);
			}
		}
		else
			tmp->next = 0;
		lst = lst->next;
		tmp = tmp->next;
	}
	return (0);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ans;

	if (lst == 0 || f == 0 || del == 0)
		return (0);
	ans = malloc(sizeof(t_list));
	if (!ans)
		return (0);
	if (map(&ans, lst, f, del))
		return (0);
	return (ans);
}
