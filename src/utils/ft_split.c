/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:10:57 by mapontil          #+#    #+#             */
/*   Updated: 2022/03/04 14:42:26 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

static int	ft_wordlen(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	ft_wordcount(const char *s, char c)
{
	int	i;
	int	j;

	j = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		i = ft_wordlen(s, c);
		s += i;
		if (i)
			j++;
	}
	return (j);
}

static char	*ft_strdups(const char *s, int size, char **tab, int tabsize)
{
	int		i;
	char	*dst;

	i = -1;
	dst = malloc((size + 1) * sizeof(char));
	if (!dst)
	{
		while (++i < tabsize)
			free(tab[i]);
		free(tab);
		return (0);
	}
	while (++i < size && s[i])
		dst[i] = s[i];
	dst[i] = '\0';
	return (dst);
}

char	**ft_split(char const *s, char c)
{
	char	**dst;
	int		size;
	int		i;
	int		j;

	if (!s)
		return (0);
	size = ft_wordcount(s, c);
	dst = malloc((size + 1) * sizeof(char *));
	if (!dst)
		return (0);
	i = -1;
	while (++i < size)
	{
		while (*s == c)
			s++;
		j = ft_wordlen(s, c);
		dst[i] = ft_strdups(s, j, dst, size);
		if (!dst[i])
			return (NULL);
		s += j;
	}
	dst[i] = 0;
	return (dst);
}
