/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuau <lsuau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 21:51:00 by lsuau             #+#    #+#             */
/*   Updated: 2022/03/05 15:49:28 by lsuau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

t_env	*env_lstnew(const char *var)
{
	t_env	*new;
	int		x;

	new = malloc(sizeof(t_env));
	if (!new)
		return (0);
	x = 0;
	while (var[x] != '=')
		x++;
	new->name = ft_substr(var, 0, x);
	new->value = ft_substr(var, x + 1, stlen(var + x + 1));
	new->next = 0;
	if (!new->name || !new->value)
	{
		if (new->name)
			free(new->next);
		if (new->value)
			free(new->value);
		free(new);
		return (0);
	}
	return (new);
}

void	env_lstadd_back(t_env **alst, t_env *new)
{
	t_env	*bl;

	bl = *alst;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	while ((*alst)->next)
		*alst = (*alst)->next;
	(*alst)->next = new;
	*alst = bl;
}

void	env_lstclear(t_data *data)
{
	t_env	*l;
	t_env	*t;

	l = data->env;
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

t_env	*env_init(t_data *data, char **envp)
{
	t_env	*env;
	t_env	*t;
	int		x;

	env = 0;
	x = 0;
	while (envp[x])
	{
		t = env_lstnew(envp[x]);
		if (!t)
		{
			env_lstclear(data);
			return (0);
		}
		env_lstadd_back(&env, t);
		x++;
	}
	env_starter(&env);
	return (env);
}

int	env_lstsize(t_env *env)
{
	int	x;

	x = 0;
	while (env)
	{
		x++;
		env = env->next;
	}
	return (x);
}
