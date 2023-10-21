/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:29:51 by ychen2            #+#    #+#             */
/*   Updated: 2023/10/14 17:15:13 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_sub(char const *s, char c)
{
	size_t	ans;
	size_t	i;
	size_t	s_len;

	if (s == 0)
		return (-1);
	if (s[0] == 0)
		return (0);
	ans = 0;
	i = 0;
	s_len = ft_strlen(s);
	while (i < s_len)
	{
		if (i == 0 && s[i] != c)
			ans++;
		if (i + 1 < s_len)
			if (s[i] == c && s[i + 1] != c)
				ans++;
		i++;
	}
	return (ans);
}

void	get_idx(char const *s, char c, size_t *idx_1, size_t *idx_2)
{
	size_t	i[2];
	size_t	s_len;

	i[0] = 0;
	i[1] = 0;
	s_len = ft_strlen(s);
	while (i[0] < s_len)
	{
		if (i[0] == 0 && s[i[0]] != c)
			idx_1[i[1]++] = i[0];
		if (i[0] + 1 < s_len)
			if (s[i[0]] == c && s[i[0] + 1] != c)
				idx_1[i[1]++] = i[0] + 1;
		i[0]++;
	}
	i[0] = 1;
	i[1] = 0;
	while (i[0] < s_len)
	{
		if (s[i[0] - 1] != c && s[i[0]] == c)
			idx_2[i[1]++] = i[0] - 1;
		else if (i[0] == s_len - 1 && s[i[0]] != c)
			idx_2[i[1]++] = i[0];
		i[0]++;
	}
}

void	fail_handle(char **s, size_t n, size_t *idx_1, size_t *idx_2)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		free(s[i]);
		i++;
	}
	free(s);
	free(idx_1);
	free(idx_2);
}

int	alloc(size_t **idx_1, size_t **idx_2, char ***ans, int sub_len)
{
	if (sub_len == -1)
		return (1);
	*idx_1 = malloc(sub_len * sizeof(size_t) + 1);
	if (!*idx_1)
		return (1);
	*idx_2 = malloc(sub_len * sizeof(size_t) + 1);
	if (!*idx_2)
	{
		free(*idx_1);
		return (1);
	}
	if (sub_len != 0)
		*ans = malloc((sub_len + 1) * sizeof(char *));
	else
		*ans = malloc(sizeof(char *));
	if (!*ans)
	{
		free(*idx_1);
		free(*idx_2);
		return (1);
	}
	(*ans)[sub_len] = 0;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	int		sub_len;
	size_t	i;
	size_t	*idx_1;
	size_t	*idx_2;
	char	**ans;

	sub_len = ft_count_sub(s, c);
	if (alloc(&idx_1, &idx_2, &ans, sub_len))
		return (0);
	if (sub_len != 0)
		get_idx(s, c, idx_1, idx_2);
	i = 0;
	while (i < (size_t)sub_len)
	{
		ans[i] = ft_substr(s, idx_1[i], idx_2[i] - idx_1[i] + 1);
		if (!ans[i])
		{
			fail_handle(ans, i, idx_1, idx_2);
			return (0);
		}
		i++;
	}
	free(idx_1);
	free(idx_2);
	return (ans);
}
