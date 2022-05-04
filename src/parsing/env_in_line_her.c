/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_in_line_her.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:49:31 by lsuau             #+#    #+#             */
/*   Updated: 2022/03/16 09:47:38 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

char	*her_put_value(char *line, int x, char *value)
{
	char	*s;
	int		i;
	int		y;

	s = malloc(sizeof(char) * (stlen(line) + stlen(value) + 1));
	if (!s)
		return (0);
	i = -1;
	while (++i < x)
		s[i] = line[i];
	y = -1;
	while (value[++y])
		s[i + y] = value[y];
	while (line[i])
	{
		s[i + y] = line[i];
		i++;
	}
	s[i + y] = 0;
	free(line);
	return (s);
}

char	*her_insert_value(char *line, int *x, int dq, char *value)
{
	int	y;

	y = *x + 1;
	if (!line[y] || is_spe_env(line[y], dq))
		*x = *x + 1;
	else if (!dq && (line[y] == '\'' || line[y] == '"'))
		ft_strcpy(line + *x, line + y);
	else if (line[y] >= '0' && line[y] <= '9')
		ft_strcpy(line + *x, line + y + 1);
	else
	{
		if (line[y] == '?')
			y++;
		else
			y = check_env_char(line, y);
		ft_strcpy(line + *x, line + y);
		if (value)
		{
			line = her_put_value(line, *x, value);
			*x += stlen(value);
			free(value);
		}
	}
	return (line);
}

int	her_replace_env_line(t_env *env, char **old_line)
{
	int		x;
	int		dq;
	char	*line;

	x = 0;
	dq = 0;
	line = *old_line;
	while (line[x])
	{
		if (line[x] == '\'' && !dq)
			x = skip_quote(line, x);
		if (line[x] == '"')
			dq = (dq + 1) % 2;
		if (line[x] == '$')
		{
			line = her_insert_value(line, &x, dq, \
			search_env(env, line + x + 1));
			if (!line)
				return (1);
			*old_line = line;
		}
		else
			x++;
	}
	return (0);
}
