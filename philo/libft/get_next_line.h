/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:03:28 by ychen2            #+#    #+#             */
/*   Updated: 2023/10/15 16:53:09 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

typedef struct s_str
{
	char			content;
	struct s_str	*next;
}	t_str;
typedef struct s_gnl
{
	int		idx;
	int		read_num;
	int		len;
	char	buffer[BUFFER_SIZE];
}	t_gnl;

char	*get_next_line(int fd);
t_str	*ft_strnew(char content);
void	ft_strclear(t_str **lst);
int		ft_strsize(t_str *lst);
int		copy_buffer(t_str **tail, t_gnl *status);
void	copy_str(char *str, t_str *lst);
#endif