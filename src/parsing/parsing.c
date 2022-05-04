/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuau <lsuau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 15:02:28 by lsuau             #+#    #+#             */
/*   Updated: 2022/04/05 16:48:02 by lsuau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void	find_path(char **paths, char *cmd, char *s)
{
	int	x;

	x = 0;
	while (paths[x])
	{
		ft_strcpy(s, paths[x]);
		ft_strcat(s, "/");
		ft_strcat(s, cmd);
		if (!access(s, X_OK))
			return ;
		x++;
	}
	ft_strcpy(s, "");
}

char	*pathing(t_env *env, char *cmd)
{
	char	**paths;
	char	*s;
	char	buf[PATH_MAX];

	if (ft_strrchr(cmd, '/') && !access(cmd, F_OK))
		return (ft_strdup(cmd));
	while (env && stcmp(env->name, "PATH"))
		env = env->next;
	if (!cmd || cmd[0] == '/' || is_builtin(cmd))
		return (ft_strdup(""));
	if (env)
		paths = ft_split(env->value, ':');
	else
		paths = ft_split(getcwd(buf, PATH_MAX), 0);
	if (!paths)
		return (0);
	s = malloc(sizeof(char) * (longest_in_tab(paths) + stlen(cmd) + 2));
	if (!s)
		return (0);
	find_path(paths, cmd, s);
	free_tab(paths);
	return (s);
}

int	cmd_parsing(t_data *data, char **line_split)
{
	int		x;
	t_cmd	*t;

	x = 0;
	while (line_split[x] && check_line_split(line_split[x]))
	{
		t = cmd_lstnew(data);
		if (!t)
			return (cmd_lstclear(data));
		cmd_lstadd_back(&data->cmds, t);
		if (red_parsing(t, line_split[x]))
			return (cmd_lstclear(data));
		if (replace_env_line(data->env, &line_split[x]))
			return (cmd_lstclear(data));
		t->cmd = cmd_split(line_split[x]);
		if (!t->cmd)
			return (cmd_lstclear(data));
		remove_cmd_quotes(t->cmd);
		t->path = pathing(data->env, t->cmd[0]);
		if (!t->path)
			return (cmd_lstclear(data));
		x++;
	}
	data->nb_cmd = x;
	return (0);
}

int	update_old_pwd(char **pwd)
{
	char	buf[PATH_MAX];

	if (getcwd(buf, PATH_MAX))
	{
		if (*pwd)
			free(*pwd);
		*pwd = ft_strdup(buf);
		if (!*pwd)
			return (1);
	}
	return (0);
}

int	le_parsing(t_data *data, char *line)
{
	char	**line_split;

	data->nb_cmd = 0;
	if (!line || check_quote_n_pipe(line) || check_red(line))
		return (1);
	line_split = pipe_split(line);
	if (!line_split || update_old_pwd(&data->pwd))
		return (mess_error(0, 0, 1));
	replace_tab(line_split);
	if (cmd_parsing(data, line_split))
	{
		free_tab(line_split);
		return (mess_error(0, 0, 1));
	}
	free_tab(line_split);
	return (0);
}
