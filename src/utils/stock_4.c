/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuau <lsuau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:22:56 by mapontil          #+#    #+#             */
/*   Updated: 2022/03/10 17:08:39 by lsuau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

char	*ft_lower_case(char *str)
{
	int		i;
	char	*dup;

	if (!str)
		return (NULL);
	i = 0;
	dup = ft_strdup(str);
	while (dup[i])
	{
		if (dup[i] >= 'A' && dup[i] <= 'Z')
			dup[i] += 32;
		i++;
	}
	return (dup);
}

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = stlen(s);
	if (!s)
		return (0);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i--;
	}
	return (0);
}

char	*ft_userchr(t_data *data)
{
	t_env	*curr;
	char	*name;

	curr = data->env;
	name = 0;
	if (!curr)
		return (NULL);
	while (curr)
	{
		if (stcmp(curr->name, "USER") == 0)
			name = ft_strdup(curr->value);
		curr = curr->next;
	}
	if (!name)
		name = ft_strdup("tarnished");
	return (name);
}

int	size_wospace(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] == 32 || str[i] == 9)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		i++;
		j++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		j++;
		i++;
	}
	return (j);
}

char	*clear_cmd_space(char *str)
{
	int		i;
	int		j;
	char	*dst;

	dst = malloc((size_wospace(str) + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] == 32 || str[i] == 9)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		dst[j] = str[i];
		i++;
		j++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		dst[j] = str[i];
		j++;
		i++;
	}
	dst[j] = '\0';
	return (dst);
}
