/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuau <lsuau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:30:25 by lsuau             #+#    #+#             */
/*   Updated: 2022/03/10 16:20:48 by lsuau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void	cmd_lstadd_back(t_cmd **alst, t_cmd *new)
{
	t_cmd	*bl;

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

int	cmd_lstclear(t_data *data)
{
	t_cmd	*l;
	t_cmd	*t;

	l = data->cmds;
	data->cmds = 0;
	while (l)
	{
		t = l->next;
		if (l->cmd)
			free_tab(l->cmd);
		if (l->path)
			free(l->path);
		if (l->red_in == 1 && !access(l->in, F_OK))
			unlink(l->in);
		if (l->in)
			free(l->in);
		if (l->out)
			free(l->out);
		if (l->envp)
			free_tab(l->envp);
		free(l);
		l = t;
	}
	return (1);
}

char	**env_lst_to_tab(t_env *env)
{
	char	**envp;
	int		x;

	x = 0;
	envp = malloc(sizeof(char *) * (env_lstsize(env) + 1));
	if (!envp)
		return (0);
	while (env)
	{
		envp[x] = malloc((stlen(env->name) + stlen(env->value) + 2));
		if (!envp[x])
			return (free_tab(envp));
		envp[x][0] = 0;
		ft_strcat(envp[x], env->name);
		if (env->value)
		{
			ft_strcat(envp[x], "=");
			ft_strcat(envp[x], env->value);
		}
		x++;
		env = env->next;
	}
	envp[x] = 0;
	return (envp);
}

t_cmd	*cmd_lstnew(t_data *data)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (0);
	new->cmd = 0;
	new->path = 0;
	new->in = 0;
	new->out = 0;
	new->envp = env_lst_to_tab(data->env);
	new->next = 0;
	new->red_in = 0;
	new->red_out = 0;
	new->data = data;
	if (!new->envp)
	{
		free(new);
		return (0);
	}
	return (new);
}
