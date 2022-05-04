/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuau <lsuau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 08:42:47 by mapontil          #+#    #+#             */
/*   Updated: 2022/03/15 15:20:40 by lsuau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	ft_atoi(const char *str)
{
	int		x;
	long	res;
	int		fact;

	x = 0;
	res = 0;
	fact = 1;
	while (str[x] == ' ' || (str[x] >= '\t' && str[x] <= '\r'))
		x++;
	if (str[x] == '-')
	{
		x++;
		fact = -1;
	}
	else if (str[x] == '+')
		x++;
	while (str[x] >= '0' && str[x] <= '9')
	{
		res = res * 10 + str[x++] - '0';
		if (res > 2147483648 && fact == -1)
			return (0);
		else if (res > 2147483647 && fact == 1)
			return (-1);
	}
	return (res * fact);
}

int	check_red_mall(char *line, char **out, char **in, char *order)
{
	if ((!out && red_count(line, '>')) && (!in && red_count(line, '<')))
	{
		free(order);
		free_tab(in);
		free_tab(out);
		return (1);
	}
	return (0);
}

char	*red_order(char *line)
{
	int		x;
	int		n;
	char	*order;

	x = 0;
	n = 0;
	order = malloc(sizeof(char) * (red_count(line, '>') \
		+ red_count(line, '<') + 1));
	while (line[x])
	{
		if (line[x] == '\'' || line[x] == '"')
			x = skip_quote(line, x);
		if (line[x] == '>' || line[x] == '<')
		{
			order[n] = line[x];
			while (line[x] == '>' || line[x] == '<')
				x++;
			n++;
		}
		else if (line[x])
			x++;
	}
	order[n] = 0;
	return (order);
}

int	red_multifree(char **in, char **out, char *order)
{
	free(order);
	free_tab(in);
	free_tab(out);
	return (1);
}

int	nb_red(char *s)
{
	int	x;
	int	n;

	x = 0;
	n = 0;
	while (s[x])
	{
		if (s[x] == '>' || s[x] == '<')
			n++;
		x++;
	}
	return (n * 2);
}
