/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_tab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:55:49 by lsuau             #+#    #+#             */
/*   Updated: 2022/03/16 09:47:36 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	red_count(char *line, char c)
{
	int	x;
	int	nb_red;

	x = 0;
	nb_red = 0;
	while (line[x])
	{
		if (line[x] == '\'' || line[x] == '"')
			x = skip_quote(line, x);
		if (line[x] == c)
		{
			nb_red++;
			while (line[x] == c)
				x++;
		}
		else if (line[x])
			x++;
	}
	return (nb_red);
}

int	red_stlen(char *line)
{
	int		x;
	char	c;
	int		y;

	x = 0;
	y = 0;
	c = line[x];
	while (line[x] == c)
		x++;
	while (line[x + y] == ' ')
		y++;
	ft_strcpy(line + x, line + x + y);
	while (line[x])
	{
		if (line[x] == '\'' || line[x] == '"')
			x = skip_quote(line, x);
		if (line[x] == ' ' || line[x] == '>' || line[x] == '<' || !line[x])
			return (x);
		x++;
	}
	return (x);
}

char	*red_substr(char *line, char c)
{
	char	*red;
	int		len;
	int		x;

	x = 0;
	while (line[x])
	{
		if (line[x] == '\'' || line[x] == '"')
			x = skip_quote(line, x);
		if (line[x] == c)
		{
			len = red_stlen(line + x);
			red = ft_substr(line, x, len);
			if (!red)
				return (0);
			ft_strcpy(line + x, line + x + len);
			return (red);
		}
		x++;
	}
	return (0);
}

char	**fill_red_tab(char *line, char c)
{
	char	**tab;
	int		nb_red;
	int		n;

	nb_red = red_count(line, c);
	tab = malloc(sizeof(char *) * (nb_red + 1));
	if (!tab)
		return (0);
	tab[nb_red] = 0;
	n = 0;
	while (n < nb_red)
	{
		tab[n] = red_substr(line, c);
		if (!tab[n])
			return (free_tab(tab));
		n++;
	}
	return (tab);
}
