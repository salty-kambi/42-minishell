/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 11:54:31 by mapontil          #+#    #+#             */
/*   Updated: 2022/03/04 18:16:55 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void	signal_c(int signum)
{
	(void)signum;
	g_excode = 1;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_handler(void)
{
	struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &signal_c);
}

void	signal_child(int signum)
{
	(void)signum;
}

void	signal_child_handler(t_data *data)
{
	tcsetattr(0, TCSANOW, &data->term_base);
	signal(SIGQUIT, &signal_child);
	signal(SIGINT, &signal_child);
}
