/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megajoin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 11:56:49 by mapontil          #+#    #+#             */
/*   Updated: 2022/03/04 14:42:49 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

char	*megajoin(int n, ...)
{
	va_list	args;
	char	*temp;
	char	*temp2;
	int		i;

	i = -1;
	va_start(args, n);
	while (++i < n)
	{
		if (i == 0)
			temp = ft_strdup(va_arg(args, char *));
		else
		{
			temp2 = temp;
			temp = ft_strjoin(temp, va_arg(args, char *));
			if (temp2)
				free(temp2);
			if (!temp)
				return (NULL);
		}
	}
	return (temp);
}
