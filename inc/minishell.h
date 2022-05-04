/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 17:32:35 by lsuau             #+#    #+#             */
/*   Updated: 2022/03/04 14:42:56 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <termios.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdarg.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "minishell_struct.h"
# include "built_in.h"
# include "exec.h"
# include "parsing.h"
# include "signal.h"
# include "utils.h"

# ifndef BMAG
#  define BMAG "\e[1;35m"
# endif
# ifndef CRESET
#  define CRESET "\e[0m"
# endif
# ifndef BRED
#  define BRED "\e[1;31m"
# endif
# ifndef BORA
#  define BORA "\e[1;34m"
# endif

extern int	g_excode;

// prompt.c
char	*set_prompt(t_data *data);

#endif