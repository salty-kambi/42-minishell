/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:17:55 by lsuau             #+#    #+#             */
/*   Updated: 2022/04/06 15:12:14 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	in_x1_red(t_cmd *cmd, char **ins, int n)
{
	char	*in;

	replace_env_line(cmd->data->env, ins);
	in = *ins + 1;
	if (access(in, F_OK) || access(in, R_OK))
	{
		cmd->in = ft_strdup(in);
		if (!cmd->in)
			return (1);
		cmd->red_in = -1;
		return (-1);
	}
	if (!n)
	{
		cmd->in = ft_strdup(in);
		if (!cmd->in)
			return (1);
	}
	return (0);
}

int	out_no_perm(t_cmd *cmd, char *out)
{
	cmd->red_out = -1;
	cmd->out = ft_strdup(out);
	return (-1);
}

void	out_no_file(t_cmd *cmd, char *out, int n)
{
	int	fd;

	fd = open(out, O_CREAT, 0644);
	close(fd);
	if (!n)
		cmd->out = ft_strdup(out);
}

int	remove_red(char *out)
{
	if (out[1] == '>')
	{
		ft_strcpy(out, out + 2);
		return (1);
	}
	ft_strcpy(out, out + 1);
	return (0);
}
