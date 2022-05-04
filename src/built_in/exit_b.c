/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:18:24 by mapontil          #+#    #+#             */
/*   Updated: 2022/03/04 16:22:05 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	g_excode;

static int	nb_arg_exit(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->cmd[i])
		i++;
	if (i > 2)
		return (1);
	return (0);
}

static int	limit_arg_exit(t_cmd *cmd)
{
	long long int	nb;
	char			*temp;
	char			*clear_cmd;

	nb = atolli(cmd->cmd[1]);
	temp = ft_llitoa(nb);
	clear_cmd = clear_cmd_space(cmd->cmd[1]);
	if (stcmp(clear_cmd, temp))
	{
		free(clear_cmd);
		free(temp);
		return (1);
	}
	free(clear_cmd);
	free(temp);
	return (0);
}

static int	is_valid_exit(t_cmd *cmd)
{
	if (is_number(cmd->cmd[1]) || limit_arg_exit(cmd))
		return (1);
	if (nb_arg_exit(cmd))
		return (2);
	return (0);
}

static void	exit_numeric(t_data *data, t_cmd *cmd)
{
	write(2, "minishell: exit: ", 17);
	ft_putstr_fd(cmd->cmd[1], 2);
	write(2, " numeric argument required\n", 27);
	g_excode = 255;
	if (data->nb_cmd == 1)
		exit(255);
}

void	exit_builtin(t_data *data, t_cmd *cmd)
{
	if (data->nb_cmd == 1)
		write(2, "exit\n", 5);
	if (!cmd->cmd[1] || is_valid_exit(cmd) == 0)
	{
		if (cmd->cmd[1])
			g_excode = satoi(cmd->cmd[1]);
		if (data->nb_cmd == 1)
			exit(g_excode);
	}
	else if (is_valid_exit(cmd) == 1)
		exit_numeric(data, cmd);
	else if (is_valid_exit(cmd) == 2)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		g_excode = 1;
	}
}
