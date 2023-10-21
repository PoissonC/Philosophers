/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 09:37:49 by yu                #+#    #+#             */
/*   Updated: 2023/10/15 16:52:24 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	read_handle(int fd, t_gnl *status)
{
	if (read(fd, 0, 0) < 0)
	{
		status->idx = 0;
		return (0);
	}
	if (status->idx == 0 || status->idx == BUFFER_SIZE)
	{
		status->idx = 0;
		status->read_num = read(fd, status->buffer, BUFFER_SIZE);
		if (status->read_num == 0)
		{
			status->idx = 0;
			return (2);
		}
		if (status->read_num < 0)
			return (0);
		if (status->idx == BUFFER_SIZE)
			status->idx = 0;
	}
	if (status->read_num < BUFFER_SIZE && status->idx == status->read_num)
		return (0);
	return (1);
}

//0 -> end get_next_line with output NULL, 
//1 -> keep read_buffer
//2 -> found new line or eof
int	read_buffer(int fd, t_str **tail, t_gnl *status)
{
	int				buffer_flag;
	int				read_handler;

	read_handler = read_handle(fd, status);
	if (read_handler == 2)
		return (2);
	if (read_handler == 0)
		return (0);
	buffer_flag = copy_buffer(tail, status);
	if (buffer_flag == 1)
		return (0);
	else if (buffer_flag == 2)
		return (2);
	return (1);
}

int	erro_handle(int fd, t_str *curr, t_str **head, t_gnl *status)
{
	int	read_flag;

	status->len = 0;
	read_flag = read_buffer(fd, &curr, status);
	while (read_flag == 1)
	{
		read_flag = read_buffer(fd, &curr, status);
	}
	if (read_flag == 2)
		return (0);
	ft_strclear(head);
	return (1);
}

char	*get_next_line(int fd)
{
	char			*ans;
	t_str			*head;
	static t_gnl	status;

	if (BUFFER_SIZE <= 0)
		return (0);
	head = ft_strnew(0);
	if (!head)
		return (0);
	if (erro_handle(fd, head, &head, &status))
		return (0);
	ans = malloc(status.len + 1);
	if (!ans)
	{
		ft_strclear(&head);
		return (0);
	}
	copy_str(ans, head->next);
	ft_strclear(&head);
	if (ans[0] == '\0')
	{
		free(ans);
		return (0);
	}
	return (ans);
}
