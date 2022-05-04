/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_starter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuau <lsuau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:28:58 by mapontil          #+#    #+#             */
/*   Updated: 2022/03/08 14:37:11 by lsuau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

t_env	*find_env(t_env *env, char *name)
{
	while (env)
	{
		if (!stcmp(env->name, name))
			return (env);
		env = env->next;
	}
	return (0);
}

void	env_lstadd_back_2(t_env **env, char *name, char *value)
{
	t_env	*t;

	t = malloc(sizeof(t_env));
	t->name = ft_strdup(name);
	t->value = ft_strdup(value);
	t->next = 0;
	env_lstadd_back(env, t);
}

int	check_shlvl_value(char *value)
{
	int	x;

	x = 0;
	if (value[x] == '+' || value[x] == '-')
		x++;
	while (value[x])
	{
		if (!(value[x] >= '0' && value[x] <= '9'))
		{
			free(value);
			return (1);
		}
		x++;
	}
	return (0);
}

char	*update_shlvl(char *value)
{
	int	v;

	if (!value || check_shlvl_value(value))
		return (ft_strdup("1"));
	v = ft_atoi(value);
	free(value);
	if (v < 0)
		return (ft_strdup("0"));
	else if (v == 999)
		return (ft_strdup(""));
	else if (v > 999)
	{
		write(2, "minishell: warning: shell level (", 33);
		ft_putstr_fd(ft_itoa(v + 1), 2);
		write(2, ") too high, resetting to 1\n", 27);
		return (ft_strdup("1"));
	}
	return (ft_itoa(v + 1));
}

void	env_starter(t_env **env)
{
	t_env	*t;
	char	buf[PATH_MAX];

	t = find_env(*env, "PWD");
	if (!t)
		env_lstadd_back_2(env, "PWD", getcwd(buf, PATH_MAX));
	t = find_env(*env, "OLDPWD");
	if (t)
	{
		free(t->value);
		t->value = 0;
	}
	else
		env_lstadd_back_2(env, "OLDPWD", 0);
	t = find_env(*env, "SHLVL");
	if (t)
		t->value = update_shlvl(t->value);
	else
		env_lstadd_back_2(env, "SHLVL", "1");
}
