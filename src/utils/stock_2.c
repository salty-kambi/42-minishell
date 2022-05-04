/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:46:04 by mapontil          #+#    #+#             */
/*   Updated: 2022/03/04 14:43:25 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*dst;
	size_t	size1;
	size_t	size2;
	size_t	i;

	if (!s1 || !s2)
		return (0);
	size1 = stlen(s1);
	size2 = stlen(s2);
	dst = malloc((size1 + size2 + 1) * sizeof(char));
	if (!dst)
		return (0);
	i = -1;
	while (s1[++i])
		dst[i] = s1[i];
	i = -1;
	while (s2[++i])
		dst[size1 + i] = s2[i];
	dst[size1 + size2] = '\0';
	return (dst);
}

int	skip_quote(char *line, int x)
{
	char	c;

	c = line[x];
	x++;
	while (line[x] != c)
		x++;
	return (x);
}

void	ft_strcpy(char *dst, const char *src)
{
	int	x;

	x = 0;
	while (src[x])
	{
		dst[x] = src[x];
		x++;
	}
	dst[x] = 0;
	return ;
}

void	ft_strcat(char *dst, const char *src)
{
	int	x;
	int	y;

	if (!src)
		return ;
	x = stlen(dst);
	y = 0;
	while (src[y])
	{
		dst[x] = src[y];
		x++;
		y++;
	}
	dst[x] = 0;
	return ;
}

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int	x;

	x = 0;
	if (n < 1)
		return (0);
	while (s1[x] && s2[x] && (s1[x] == s2[x]) && n > 0)
	{
		n--;
		if (n > 0)
			x++;
	}
	return ((unsigned char)s1[x] - (unsigned char)s2[x]);
}
