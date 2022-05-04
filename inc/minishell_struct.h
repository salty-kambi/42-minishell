/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuau <lsuau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 21:55:30 by lsuau             #+#    #+#             */
/*   Updated: 2022/03/23 13:35:06 by lsuau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCT_H
# define MINISHELL_STRUCT_H

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

//in and out -> file name, null if not specified
//red_in and red_out -> redirection type, 0 by default, 1 if double
//red_in == -1 if file do not exist, file name will be in *in
//if red_in == 1, in file must be deleted
typedef struct s_cmd
{
	char			**cmd;
	char			*path;
	char			*in;
	int				red_in;
	char			*out;
	int				red_out;
	char			**envp;
	struct s_data	*data;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	t_env			*env;
	t_cmd			*cmds;
	int				nb_cmd;
	int				fd[2];
	int				fd_prev;
	int				run;
	char			*pwd;
	struct termios	term_base;
}	t_data;

typedef struct s_prompt
{
	char	*status;
	char	*curr_dir;
	char	*user;
}	t_prompt;

#endif