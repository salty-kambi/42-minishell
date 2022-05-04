/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:46:31 by mapontil          #+#    #+#             */
/*   Updated: 2022/03/04 15:09:20 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

static t_env	*env_lstnew_no_value(char *str)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (0);
	new->name = ft_strdup(str);
	new->value = NULL;
	new->next = NULL;
	return (new);
}

static t_env	*env_lstnew_value(char const *str)
{
	t_env	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(t_env));
	if (!new)
		return (0);
	while (str[i] != '=')
		i++;
	new->name = ft_substr(str, 0, i);
	new->value = ft_substr(str, i + 1, stlen(str + i + 1));
	new->next = NULL;
	return (new);
}

static int	check_env_dup(char *str, t_env *env)
{
	char	*name;
	int		i;

	i = 0;
	while (str[i] != '=')
		i++;
	name = ft_substr(str, 0, i);
	while (env)
	{
		if (stcmp(env->name, name) == 0)
		{
			free(name);
			return (1);
		}
		env = env->next;
	}
	if (name)
		free(name);
	return (0);
}

static int	check_exp_dup(char *str, t_env *env)
{
	while (env)
	{
		if (stcmp(env->name, str) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

void	ft_add_env(char *str, t_data *data)
{
	t_env	*new;

	if (valid_identifier(str, 0) == 0)
	{
		if (check_equal(str))
		{
			if (check_env_dup(str, data->env) == 0)
			{
				new = env_lstnew_value(str);
				env_lstadd_back(&data->env, new);
			}
			else
				change_value_env(str, data->env);
		}
		else
		{
			if (check_exp_dup(str, data->env) == 0)
			{
				new = env_lstnew_no_value(str);
				env_lstadd_back(&data->env, new);
			}
		}
	}
}
