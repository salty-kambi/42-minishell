/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuau <lsuau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:02:49 by lsuau             #+#    #+#             */
/*   Updated: 2022/03/24 13:28:27 by lsuau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	tablen(char **tab)
{
	int	x;

	if (!tab)
		return (-1);
	x = 0;
	while (tab[x])
	{
		x++;
	}
	return (x);
}

void	write_nl(int fd, char *s)
{
	write(fd, s, stlen(s));
	write(fd, "\n", 1);
}

char	**red_env(t_env *env, char **tab, int n)
{
	replace_env_line(env, tab + n);
	return (tab);
}

int	longest_in_tab(char **tab)
{
	int	x;
	int	n;
	int	len;

	n = 0;
	len = 0;
	while (tab[n])
	{
		x = 0;
		while (tab[n][x])
			x++;
		if (x > len)
			len = x;
		n++;
	}
	return (len);
}

short	satoi(char *str)
{
	short	res;
	short	neg;
	int		i;

	res = 0;
	neg = 1;
	i = 0;
	while (str[i] == 32 || str[i] == 9)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res * neg);
}
