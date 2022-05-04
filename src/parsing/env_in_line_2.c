/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_in_line_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 13:52:53 by lsuau             #+#    #+#             */
/*   Updated: 2022/04/06 15:03:57 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	is_spe_env(char c, int dq)
{
	int	n;

	n = 1;
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		n = 0;
	if ((c >= '0' && c <= '9'))
		n = 0;
	if ((c == '"' && !dq) || c == '?')
		n = 0;
	return (n);
}

int	copy_value(char *s, char *value)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (value[x])
	{
		s[x + y] = value[x];
		x++;
	}
	return (x + y);
}

char	*put_value(char *line, int x, char *value)
{
	char	*s;
	int		i;
	int		y;

	s = malloc(sizeof(char) * (stlen(line) + stlen(value) + nb_red(value) + 1));
	if (!s)
		return (0);
	i = -1;
	while (++i < x)
		s[i] = line[i];
	y = copy_value(s + i, value);
	while (line[i])
	{
		s[i + y] = line[i];
		i++;
	}
	s[i + y] = 0;
	free(line);
	return (s);
}
