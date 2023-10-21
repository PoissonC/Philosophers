/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:16:32 by ychen2            #+#    #+#             */
/*   Updated: 2023/09/23 17:25:01 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	trim_start(size_t idx[], char const *s1, char const *set)
{
	size_t	s1_len;
	size_t	set_len;

	idx[0] = 0;
	s1_len = ft_strlen(s1);
	set_len = ft_strlen(set);
	while (idx[0] < s1_len)
	{
		idx[1] = 0;
		while (idx[1] < set_len)
		{
			if (s1[idx[0]] == set[idx[1]])
			{
				idx[2] = idx[0];
				break ;
			}
			idx[1]++;
		}
		if (idx[2] != idx[0])
			break ;
		idx[0]++;
	}
	idx[2]++;
}

void	trim_end(size_t idx[], char const *s1, char const *set)
{
	size_t	s1_len;
	size_t	set_len;

	s1_len = ft_strlen(s1);
	set_len = ft_strlen(set);
	idx[0] = s1_len;
	while (idx[0] > idx[2])
	{
		idx[1] = 0;
		while (idx[1] < set_len)
		{
			if (s1[idx[0]] == set[idx[1]])
			{
				idx[3] = idx[0];
				break ;
			}
			idx[1]++;
		}
		if (idx[3] != idx[0])
			break ;
		idx[0]--;
	}
}

void	check(size_t idx[], char const *s1, char const *set)
{
	unsigned int	i;
	size_t			set_len;

	set_len = ft_strlen(set);
	i = 0;
	while (i < set_len)
	{
		if (set[i] == s1[0])
			break ;
		i++;
	}
	if (i == set_len)
		idx[2] = 0;
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	s1_len;
	char	*str;
	size_t	idx[4];

	if (s1 == 0 || set == 0)
		return (0);
	s1_len = ft_strlen(s1);
	idx[2] = 0;
	idx[3] = s1_len;
	trim_start(idx, s1, set);
	check(idx, s1, set);
	trim_end(idx, s1, set);
	str = malloc(idx[3] - idx[2] + 1);
	if (!str)
		return (0);
	ft_strlcpy(str, s1 + idx[2], idx[3] - idx[2] + 1);
	return (str);
}
