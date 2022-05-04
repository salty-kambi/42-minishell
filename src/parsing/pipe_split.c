/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 15:18:15 by lsuau             #+#    #+#             */
/*   Updated: 2022/03/01 15:03:49 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	check_line_split(char *line)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (line[x])
	{
		if (line[x] != ' ')
			y = 1;
		x++;
	}
	if (x > 0 && y)
		return (1);
	return (0);
}

int	char_count(char	*line, char c)
{
	int	x;
	int	nb_char;

	nb_char = 1;
	x = 0;
	while (line[x])
	{
		if (line[x] == '\'' || line[x] == '"')
			x = skip_quote(line, x);
		if (line[x] == c)
			nb_char++;
		x++;
	}
	return (nb_char);
}

int	next_pipe(char *line, int n)
{
	int	x;
	int	pipe;

	pipe = 0;
	x = 0;
	if (n == -1)
		return (0);
	while (line[x])
	{
		if (line[x] == '\'' || line[x] == '"')
			x = skip_quote(line, x);
		if (line[x] == '|')
		{
			if (pipe == n)
				return (x + 1);
			pipe++;
		}
		x++;
	}
	return (x + 1);
}

char	**pipe_split(char *line)
{
	char	**spl;
	char	*t;
	int		nb_cmd;
	int		x;

	x = 0;
	nb_cmd = char_count(line, '|');
	spl = malloc(sizeof(char *) * (nb_cmd + 1));
	if (!spl)
		return (0);
	spl[nb_cmd] = 0;
	while (x < nb_cmd)
	{
		t = ft_substr(line, next_pipe(line, x - 1), \
			next_pipe(line, x) - next_pipe(line, x - 1) - 1);
		spl[x] = t;
		if (!t)
			return (free_tab(spl));
		x++;
	}
	return (spl);
}
