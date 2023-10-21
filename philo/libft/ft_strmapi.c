/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:44:18 by ychen2            #+#    #+#             */
/*   Updated: 2023/09/23 20:58:06 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	size_t			s_len;
	char			*ans;

	if (s == 0 || f == 0)
		return (0);
	s_len = ft_strlen(s);
	ans = malloc(s_len + 1);
	if (!ans)
		return (0);
	ans[s_len] = 0;
	i = 0;
	while (i < s_len)
	{
		ans[i] = f(i, s[i]);
		i++;
	}
	return (ans);
}
