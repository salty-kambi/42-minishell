/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:35:54 by mapontil          #+#    #+#             */
/*   Updated: 2022/03/04 17:11:24 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	g_excode;

static void	check_unset(char *str, t_env **env)
{
	t_env	*curr;
	t_env	*prev;
	t_env	*save;

	curr = *env;
	save = *env;
	prev = NULL;
	while (curr)
	{
		if (stcmp(str, curr->name) == 0)
		{
			if (!prev)
				save = curr->next;
			else
				prev->next = curr->next;
			free(curr->name);
			free(curr->value);
			free(curr);
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
	(*env) = save;
}

static void	not_valid_identifier(char *str)
{
	write(2, "minishell: unset: `", 20);
	ft_putstr_fd(str, 2);
	write(2, "': not a valid identifier\n", 26);
}

static int	check_valid_identifier(char *str)
{
	int	i;

	i = -1;
	if (!(str[++i] >= 'a' && str[i] <= 'z') && !(str[i] >= 'A' && str[i] <= 'Z')
		&& str[i] != '_')
	{
		not_valid_identifier(str);
		return (1);
	}
	while (str[i])
	{
		if (!(str[i] >= 'a' && str[i] <= 'z')
			&& !(str[i] >= 'A' && str[i] <= 'Z')
			&& str[i] != '_' && !(str[i] >= '0' && str[i] <= '9'))
		{
			not_valid_identifier(str);
			return (1);
		}
		i++;
	}
	return (0);
}

void	unset_builtin(t_cmd *cmd, t_env **env)
{
	int		i;

	i = 0;
	while (cmd->cmd[++i])
	{
		if (check_valid_identifier(cmd->cmd[i]) == 0)
			check_unset(cmd->cmd[i], env);
	}
	g_excode = 0;
}
