/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuau <lsuau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 18:30:04 by lsuau             #+#    #+#             */
/*   Updated: 2022/03/23 14:11:23 by lsuau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	g_excode;

int	mess_error(char c, const char *s, int n)
{
	if (n == 0)
	{
		write(2, "minimush: syntax error near unexpected token `", 46);
		if (c)
			write(2, &c, 1);
		else
			write(2, s, stlen(s));
		write(2, "'\n", 2);
		g_excode = 258;
	}
	else if (n == 1)
	{
		if (g_excode == 512)
			g_excode = 0;
		else if (g_excode == 256)
			g_excode = 1;
		else if (g_excode != 258)
		{
			g_excode = 1;
			write(2, "minimush: malloc error\n", 23);
		}
	}
	return (1);
}

//check if there is blank between pipe
int	check_pipe(char *line, int sq, int dq)
{
	int	x;

	x = 0;
	if (line[x] != '|' || sq || dq)
		return (0);
	x++;
	while (line[x] == ' ')
		x++;
	if (!line[x] || line[x] == '|')
		return (1);
	return (0);
}

int	check_first_pipe(char *line)
{
	int	x;

	x = 0;
	while (line[x] == ' ')
		x++;
	if (line[x] == '|')
		return (1);
	return (0);
}

//check if all quotes are closed and pipe correct
int	check_quote_n_pipe(char *line)
{
	int	x;
	int	sq;
	int	dq;

	sq = 0;
	dq = 0;
	x = 0;
	while (line[x])
	{
		if (line[x] == '\'' && !(dq % 2))
			sq++;
		else if (line[x] == '"' && !(sq % 2))
			dq++;
		else if (check_pipe(line + x, sq % 2, dq % 2))
			return (mess_error('|', 0, 0));
		x++;
	}
	if (sq % 2)
		return (mess_error('\'', 0, 0));
	if (dq % 2)
		return (mess_error('"', 0, 0));
	if (check_first_pipe(line))
		return (mess_error('|', 0, 0));
	return (0);
}

int	check_red(char *line)
{
	int	x;

	x = 0;
	while (line[x])
	{
		if (line[x] == '\'' || line[x] == '"')
			x = skip_quote(line, x);
		if (line[x] == '>' || line[x] == '<')
		{
			if (wrong_redcara(line + x))
				return (1);
		}	
		x++;
	}
	return (0);
}
