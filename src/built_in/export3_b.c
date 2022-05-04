/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 17:55:19 by mapontil          #+#    #+#             */
/*   Updated: 2022/03/04 15:00:26 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	g_excode;

static void	not_valid_identifier(char *str)
{
	write(2, "minishell: export: `", 20);
	ft_putstr_fd(str, 2);
	write(2, "': not a valid identifier\n", 26);
}

int	valid_identifier(char *str, int mod)
{
	int	i;

	i = -1;
	if (!(str[++i] >= 'a' && str[i] <= 'z') && !(str[i] >= 'A' && str[i] <= 'Z')
		&& str[i] != '_')
	{
		if (mod == 0)
			not_valid_identifier(str);
		return (1);
	}
	while (str[i])
	{
		if (str[i] == '=')
			return (0);
		if (!(str[i] >= 'a' && str[i] <= 'z')
			&& !(str[i] >= 'A' && str[i] <= 'Z')
			&& str[i] != '_' && !(str[i] >= '0' && str[i] <= '9'))
		{
			if (mod == 0)
				not_valid_identifier(str);
			return (1);
		}
		i++;
	}
	return (0);
}

void	envcpy_lstclear(t_env *cpy)
{
	t_env	*l;
	t_env	*t;

	l = cpy;
	while (l)
	{
		t = l->next;
		if (l->name)
			free(l->name);
		if (l->value)
			free(l->value);
		free(l);
		l = t;
	}
}
