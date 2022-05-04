/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llitoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 11:45:16 by mapontil          #+#    #+#             */
/*   Updated: 2022/03/04 12:16:09 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

static int	ft_sizenb(long long int n)
{
	int	i;

	i = 1;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*ft_strrev(char *str)
{
	int		i;
	int		j;
	char	tmp;

	j = 0;
	while (str[j + 1])
		j++;
	i = 0;
	while (i < j)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		i++;
		j--;
	}
	return (str);
}

static void	neg_swap(int *neg, long long int *temp)
{
	*neg = 1;
	*temp *= -1;
}

char	*ft_llitoa(long long int nbr)
{
	char			*dst;
	int				i;
	int				neg;
	long long int	temp;

	neg = 0;
	temp = nbr;
	if (nbr == LLONG_MIN)
		return (ft_strdup("-9223372036854775808"));
	dst = malloc((ft_sizenb(temp) + 1) * sizeof(char));
	if (!dst)
		return (0);
	if (temp < 0)
		neg_swap(&neg, &temp);
	i = -1;
	dst[ft_sizenb(nbr)] = '\0';
	if (neg)
		dst[ft_sizenb(nbr) - 1] = '-';
	while (++i < ft_sizenb(nbr) - neg)
	{
		dst[i] = (temp % 10) + 48;
		temp /= 10;
	}
	return (ft_strrev(dst));
}
