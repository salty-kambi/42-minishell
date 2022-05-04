/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 10:23:17 by mapontil          #+#    #+#             */
/*   Updated: 2022/03/01 15:04:07 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	g_excode;

char	*set_prompt(t_data *data)
{
	char		*prompt;
	char		buf[PATH_MAX];
	t_prompt	elem;

	if (g_excode)
		elem.status = "💩 ";
	else
		elem.status = "🏵  ";
	getcwd(buf, PATH_MAX);
	elem.curr_dir = ft_strrchr(buf, '/') + 1;
	elem.user = ft_userchr(data);
	prompt = megajoin(10, elem.status, BMAG, elem.curr_dir, BORA, " user:(", \
			BRED, elem.user, BORA, ") ", CRESET);
	if (elem.user)
		free(elem.user);
	if (!prompt)
		prompt = ft_strdup("minimush$ ");
	return (prompt);
}
