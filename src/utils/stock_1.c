/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 17:29:27 by lsuau             #+#    #+#             */
/*   Updated: 2022/03/04 14:43:18 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	stcmp(const char *s1, const char *s2)
{
	int	x;

	x = 0;
	if (!s1)
		return (1);
	while (s1[x] && s2[x] && (s1[x] == s2[x]))
		x++;
	return ((unsigned char)s1[x] - (unsigned char)s2[x]);
}

int	stlen(const char *s)
{
	int	x;

	x = 0;
	if (!s)
		return (0);
	while (s[x])
		x++;
	return (x);
}

char	*ft_substr(char const *s, int start, int len)
{
	int		x;
	int		y;
	char	*r;

	if (!s)
		return (0);
	if (len > stlen(s))
		len = stlen(s);
	r = malloc(sizeof(char) * (len + 1));
	if (!r)
		return (0);
	x = 0;
	y = 0;
	while (s[x] && x < (len + start))
	{
		if (x >= start && x < (len + start))
		{
			r[y] = s[x];
			y++;
		}
		x++;
	}
	r[y] = 0;
	return (r);
}

char	*ft_strdup(const char *s1)
{
	int		x;
	char	*r;

	if (!s1)
		return (NULL);
	x = 0;
	r = malloc(stlen(s1) + 1);
	if (!r)
		return (0);
	while (s1[x])
	{
		r[x] = s1[x];
		x++;
	}
	r[x] = '\0';
	return (r);
}

char	**free_tab(char	**tab)
{
	int	x;

	x = 0;
	if (!tab)
		return (0);
	while (tab[x])
	{
		free(tab[x]);
		x++;
	}
	free(tab);
	return (0);
}
