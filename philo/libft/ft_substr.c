/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:13:25 by ychen2            #+#    #+#             */
/*   Updated: 2023/10/14 18:07:56 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	size;
	size_t			s_len;

	if (s == 0)
		return (0);
	s_len = ft_strlen(s);
	size = s_len - start;
	if (size > len)
		size = len;
	if (start < s_len)
	{
		sub = (char *)malloc(size * sizeof(char) + sizeof(char));
		if (!sub)
			return (0);
		ft_strlcpy(sub, s + start, size + 1);
	}
	else
	{
		sub = (char *)malloc(sizeof(char));
		if (!sub)
			return (0);
		sub[0] = 0;
	}
	return (sub);
}
