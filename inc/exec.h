/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 14:39:04 by mapontil          #+#    #+#             */
/*   Updated: 2022/04/06 15:09:55 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell_struct.h"

// excode.c
void	wait_excode(int pid, int status);

// handle_builtins.c
int		is_builtin(char *str);
void	which_builtin(t_cmd *cmd, t_data *data, int n);
int		handle_builtin(t_cmd *cmd, t_data *data);

// handle_redirect.c
void	ft_handle_redirect_out(t_cmd *cmd);
void	ft_handle_redirect_in(t_cmd *cmd);

// perror_exit.c
void	ft_perror_exit(const char *str, int code);
void	ft_command_not_found(const char *str);

// pipex.c
void	last_cmd(t_cmd *cmd, t_data *data);
void	ft_exec(t_cmd *cmd, t_data *data);
void	pipex(t_cmd *cmd, t_data *data);

// pipex2.c
void	start_exec(t_cmd *cmd, t_data *data);

// red_parsing.c
int		process_in(t_cmd *cmd, char **in, int *n, t_data *data);
void	empty_redout(char *out);
int		process_out(t_cmd *cmd, char **out, int *n);
int		red_parsing(t_cmd	*cmd, char *line);

// red_process.c
int		in_x1_red(t_cmd *cmd, char **in, int n);
int		out_no_perm(t_cmd *cmd, char *out);
void	out_no_file(t_cmd *cmd, char *out, int n);
int		remove_red(char *out);

// red_tab.c
int		red_count(char *line, char c);
int		red_stlen(char *line);
char	*red_substr(char *line, char c);
char	**fill_red_tab(char *line, char c);

#endif