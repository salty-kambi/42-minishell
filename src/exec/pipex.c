/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 10:51:42 by mapontil          #+#    #+#             */
/*   Updated: 2022/04/06 15:17:35 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

static void	last_cmd_exec(t_cmd *cmd, t_data *data)
{
	if (!is_builtin(cmd->cmd[0]) && !cmd->path[0] && (cmd->in || cmd->out)
		&& cmd->red_in != -1 && cmd->red_in != -2 && cmd->red_out != -1
		&& cmd->red_out != -2 && !cmd->cmd[0])
		exit(0);
	if (!cmd->path[0] && !is_builtin(cmd->cmd[0]) && (cmd->red_in != -1
			&& cmd->red_in != -2 && cmd->red_out != -1 && cmd->red_out != -2))
		ft_command_not_found(cmd->cmd[0]);
	if (cmd->in || cmd->red_in == -2)
		ft_handle_redirect_in(cmd);
	if (cmd->out || cmd->red_out == -2)
		ft_handle_redirect_out(cmd);
	if (handle_builtin(cmd, data))
		exit(g_excode);
	else if (execve(cmd->path, cmd->cmd, cmd->envp) == -1)
		ft_perror_exit(cmd->cmd[0], 0);
}

void	last_cmd(t_cmd *cmd, t_data *data)
{
	int		pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid < 0)
		ft_perror_exit("fork", 0);
	if (pid == 0)
	{
		if (data->fd_prev)
		{
			if (dup2(data->fd_prev, STDIN_FILENO) == -1)
				ft_perror_exit("dup2", 0);
			close(data->fd_prev);
		}
		last_cmd_exec(cmd, data);
	}
	if (data->fd_prev)
		close(data->fd_prev);
	wait_excode(pid, status);
	while (waitpid(-1, &status, 0) != -1)
		;
}

void	ft_exec(t_cmd *cmd, t_data *data)
{
	start_exec(cmd, data);
	if (cmd->in)
		ft_handle_redirect_in(cmd);
	if (cmd->out)
		ft_handle_redirect_out(cmd);
	else
	{
		if (is_builtin(cmd->cmd[0]) != 7)
			if (dup2(data->fd[1], STDOUT_FILENO) == -1)
				ft_perror_exit("dup2", 0);
		close(data->fd[1]);
	}
	if (handle_builtin(cmd, data))
		exit(g_excode);
	else if (execve(cmd->path, cmd->cmd, cmd->envp) == -1)
		ft_perror_exit(cmd->cmd[0], 0);
}

static void	launch_exec(t_cmd *cmd, t_data *data)
{
	close(data->fd[0]);
	ft_exec(cmd, data);
}

void	pipex(t_cmd *cmd, t_data *data)
{
	int	pid;

	signal_child_handler(data);
	data->fd_prev = 0;
	if (is_builtin(cmd->cmd[0]) != 1 && is_builtin(cmd->cmd[0]) != 0
		&& data->nb_cmd == 1)
		which_builtin(data->cmds, data, is_builtin(cmd->cmd[0]));
	else
	{
		while (cmd->next)
		{
			pipe(data->fd);
			pid = fork();
			if (pid < 0)
				ft_perror_exit("fork", 0);
			if (pid == 0)
				launch_exec(cmd, data);
			if (data->fd_prev)
				close(data->fd_prev);
			data->fd_prev = data->fd[0];
			close(data->fd[1]);
			cmd = cmd->next;
		}
		last_cmd(cmd, data);
	}
}
