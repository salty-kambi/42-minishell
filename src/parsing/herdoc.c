/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuau <lsuau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:50:04 by lsuau             #+#    #+#             */
/*   Updated: 2022/03/24 13:14:43 by lsuau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	g_excode;

void	in_x2_name(t_cmd *cmd)
{
	static int	x;
	char		*t;
	char		*n;

	t = ft_strdup("temp_infile_");
	n = ft_itoa(x);
	cmd->in = ft_strjoin(t, n);
	if (t)
		free(t);
	if (n)
		free(n);
	x++;
	cmd->red_in = 1;
	return ;
}

void	heredoc_fork(t_env *env, char *name, char *del)
{
	char	*s;
	int		fd;

	signal(SIGINT, &sig_her);
	if (name)
		fd = open(name, O_CREAT | O_WRONLY, 0644);
	while (1)
	{
		s = readline("> ");
		if (!s)
			exit(0);
		if (!stcmp(s, del))
		{
			free(s);
			break ;
		}
		if (her_replace_env_line(env, &s))
			exit(1);
		if (name)
			write_nl(fd, s);
		free(s);
	}
	if (name)
		close(fd);
	exit(0);
}

int	heredoc_red(t_data *data, t_cmd *cmd, char *in, int n)
{
	int	pid;
	int	status;

	signal(SIGINT, &signal_herdoc);
	if (!n)
	{
		in_x2_name(cmd);
		if (!cmd->in)
			return (1);
	}
	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
		heredoc_fork(data->env, cmd->in, in);
	waitpid(pid, &status, 0);
	if (status)
	{
		g_excode = status;
		return (1);
	}
	return (0);
}
