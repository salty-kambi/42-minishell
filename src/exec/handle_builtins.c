/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuau <lsuau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:05:51 by mapontil          #+#    #+#             */
/*   Updated: 2022/03/23 13:34:57 by lsuau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	is_builtin(char *str)
{
	int		n;
	char	*name;

	n = 0;
	name = ft_lower_case(str);
	if (stcmp(name, "echo") == 0)
		n = 1;
	else if (stcmp(name, "cd") == 0)
		n = 2;
	else if (stcmp(name, "pwd") == 0)
		n = 3;
	else if (stcmp(name, "export") == 0)
		n = 4;
	else if (stcmp(name, "unset") == 0)
		n = 5;
	else if (stcmp(name, "env") == 0)
		n = 6;
	else if (stcmp(name, "exit") == 0)
		n = 7;
	free(name);
	return (n);
}

void	which_builtin(t_cmd *cmd, t_data *data, int n)
{
	if (n == 1)
		echo_builtin(cmd);
	else if (n == 2)
		cd_builtin(cmd, data->env);
	else if (n == 3)
		pwd_builtin(data->pwd);
	else if (n == 4)
		export_builtin(data, cmd);
	else if (n == 5)
		unset_builtin(cmd, &data->env);
	else if (n == 6)
		env_builtin(data->env);
	else if (n == 7)
		exit_builtin(data, cmd);
}

int	handle_builtin(t_cmd *cmd, t_data *data)
{
	int	n;

	n = is_builtin(cmd->cmd[0]);
	if (n)
	{
		which_builtin(cmd, data, n);
		return (1);
	}
	return (0);
}
