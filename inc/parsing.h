/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuau <lsuau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 14:44:02 by mapontil          #+#    #+#             */
/*   Updated: 2022/03/15 15:54:19 by lsuau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell_struct.h"

// cmd_lst.c
void	cmd_lstadd_back(t_cmd **alst, t_cmd *new);
int		cmd_lstclear(t_data *data);
char	**env_lst_to_tab(t_env *env);
t_cmd	*cmd_lstnew(t_data *data);

// cmd_split.c
void	remove_cmd_quotes(char **cmd);
int		token_count(char *line);
int		cmd_stlen(char *line);
char	*cmd_substr(char *line);
char	**cmd_split(char *line);

// env_in_line_2.c
int		is_spe_env(char c, int dq);
char	*put_value(char *line, int x, char *value);

// env_in_line.c
int		check_env_char(char *line, int y);
char	*search_env(t_env *env, char *line);
char	*insert_value(char *line, int *x, int dq, char *value);
int		replace_env_line(t_env *env, char **old_line);

// env_in_line_her.c
int		her_replace_env_line(t_env *env, char **old_line);

// env_starter.c
t_env	*find_env(t_env *env, char *name);
void	env_lstadd_back_2(t_env **env, char *name, char *value);
int		check_shlvl_value(char *value);
char	*update_shlvl(char *value);
void	env_starter(t_env **env);

// env.c
t_env	*env_lstnew(const char *var);
void	env_lstadd_back(t_env **alst, t_env *new);
void	env_lstclear(t_data *data);
t_env	*env_init(t_data *data, char **envp);
int		env_lstsize(t_env *env);

// herdoc.c
void	in_x2_name(t_cmd *cmd);
void	heredoc_fork(t_env *env, char *name, char *del);
int		heredoc_red(t_data *data, t_cmd *cmd, char *in, int n);

// parsing_error_2.c
int		red_error(char c);
int		wrong_redcara(char *line);

// parsing_error.c
int		mess_error(char c, const char *s, int n);
int		check_pipe(char *line, int sq, int dq);
int		check_first_pipe(char *line);
int		check_quote_n_pipe(char *line);
int		check_red(char *line);

// parsing.c
void	find_path(char **paths, char *cmd, char *s);
char	*pathing(t_env *env, char *cmd);
int		cmd_parsing(t_data *data, char **line_split);
int		le_parsing(t_data *data, char *line);

// pipe_split.c
int		check_line_split(char *line);
int		char_count(char	*line, char c);
int		next_pipe(char *line, int n);
char	**pipe_split(char *line);

#endif