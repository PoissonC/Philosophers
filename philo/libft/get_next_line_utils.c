/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 09:43:28 by yu                #+#    #+#             */
/*   Updated: 2023/10/15 16:52:32 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_str	*ft_strnew(char content)
{
	t_str	*ans;

	ans = malloc(sizeof(t_str));
	if (!ans)
		return (0);
	ans->content = content;
	ans->next = 0;
	return (ans);
}

void	ft_strclear(t_str **lst)
{
	t_str	*tmp;

	if (lst == 0)
		return ;
	while ((*lst))
	{
		tmp = (*lst)->next;
		free(*lst);
		*lst = tmp;
	}
	*lst = 0;
}

void	copy_str(char *str, t_str *lst)
{
	unsigned int	i;

	i = 0;
	while (lst)
	{
		str[i] = lst->content;
		lst = lst->next;
		i++;
	}
	str[i] = '\0';
}

int	copy_buffer(t_str **tail, t_gnl *status)
{
	if (tail == 0)
		return (0);
	while (status->idx < status->read_num)
	{
		status->len++;
		(*tail)->next = ft_strnew(status->buffer[status->idx]);
		if ((*tail)->next == 0)
			return (1);
		*tail = (*tail)->next;
		if (status->buffer[status->idx++] == '\n')
		{
			if (status->idx == status->read_num)
				status->idx = 0;
			return (2);
		}
	}
	if (status->idx < BUFFER_SIZE)
	{
		if (status->idx == status->read_num)
			status->idx = 0;
		return (2);
	}
	if (status->idx == status->read_num)
		status->idx = 0;
	return (0);
}

int	ft_strsize(t_str *lst)
{
	int	ans;

	if (lst == 0)
		return (0);
	ans = 0;
	while (lst)
	{
		lst = lst->next;
		ans++;
	}
	return (ans);
}
