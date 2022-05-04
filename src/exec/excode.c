/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 12:34:39 by mapontil          #+#    #+#             */
/*   Updated: 2022/03/15 11:12:55 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	g_excode;

void	wait_excode(int pid, int status)
{
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
			g_excode = 130;
		else if (WTERMSIG(status) == 3)
		{
			write(1, "Quit: 3", 8);
			g_excode = 131;
		}
		else
			g_excode = WTERMSIG(status);
		write(1, "\n", 1);
	}
	else if (WIFEXITED(status))
		g_excode = WEXITSTATUS(status);
}
