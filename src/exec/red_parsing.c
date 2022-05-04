/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:46:26 by lsuau             #+#    #+#             */
/*   Updated: 2022/04/06 15:10:44 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	process_in(t_cmd *cmd, char **in, int *n, t_data *data)
{
	int	r;
	int	last;

	r = 0;
	last = tablen(in) - 1;
	if (in[*n][1] == '<')
	{
		if (heredoc_red(data, cmd, in[*n] + 2, last - *n))
			return (1);
	}
	else
	{
		r = in_x1_red(cmd, in + *n, last - *n);
	}
	*n += 1;
	return (r);
}

void	empty_redout(char *out)
{
	int	fd;

	fd = open(out, O_WRONLY | O_TRUNC);
	close(fd);
}

int	process_out(t_cmd *cmd, char **out, int *n)
{
	int	last;
	int	r;

	r = 0;
	last = tablen(out) - 1;
	cmd->red_out = remove_red(out[*n]);
	if (!access(out[*n], F_OK))
	{
		if (access(out[*n], W_OK))
			r = out_no_perm(cmd, out[*n]);
		else if (*n == last)
			cmd->out = ft_strdup(out[*n]);
		else if (!cmd->red_out)
			empty_redout(out[*n]);
	}
	else
		out_no_file(cmd, out[*n], last - *n);
	if ((last == *n || r == -1) && !cmd->out)
		r = 1;
	*n += 1;
	return (r);
}

int	red_process(t_cmd *cmd, char **in, char **out, char *order)
{
	int	x;
	int	n[2];
	int	r;

	x = 0;
	n[0] = 0;
	n[1] = 0;
	while (order[x])
	{
		if (order[x] == '<')
			r = process_in(cmd, in, n, cmd->data);
		else if (order[x] == '>')
			r = process_out(cmd, red_env(cmd->data->env, out, n[1]), n + 1);
		if (r)
			return (r + 1);
		x++;
	}
	return (0);
}

int	red_parsing(t_cmd	*cmd, char *line)
{
	char	**in;
	char	**out;
	char	*order;

	order = red_order(line);
	in = fill_red_tab(line, '<');
	out = fill_red_tab(line, '>');
	if (check_red_mall(line, out, in, order))
		return (1);
	if (check_ambiguous(cmd, out) || check_ambiguous(cmd, in))
	{
		red_multifree(in, out, order);
		return (0);
	}
	if (red_process(cmd, in, out, order))
		return (red_multifree(in, out, order));
	red_multifree(in, out, order);
	return (0);
}
