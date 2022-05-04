/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:17:58 by mapontil          #+#    #+#             */
/*   Updated: 2022/03/02 17:20:38 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	g_excode;

static int	check_option(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	if (str[i] == '-' && str[i + 1])
		i++;
	else
		return (1);
	while (str[i])
	{
		if (str[i] == 'n')
			i++;
		else
			return (1);
	}
	return (0);
}

static void	print_echo(t_cmd *cmd)
{
	int	i;

	i = 1;
	while (check_option(cmd->cmd[i]) == 0 && cmd->cmd[i])
			i++;
	while (cmd->cmd[i])
	{
		write(1, cmd->cmd[i], stlen(cmd->cmd[i]));
		if (cmd->cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
}

void	echo_builtin(t_cmd *cmd)
{
	print_echo(cmd);
	if ((cmd->cmd[1] && check_option(cmd->cmd[1]) == 1) || !cmd->cmd[1])
		write(1, "\n", 1);
	g_excode = 0;
}
