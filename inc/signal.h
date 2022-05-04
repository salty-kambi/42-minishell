/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 14:51:41 by mapontil          #+#    #+#             */
/*   Updated: 2022/03/01 14:52:54 by mapontil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include "minishell_struct.h"

// signal.c
void	signal_c(int signum);
void	signal_handler(void);
void	signal_child(int signum);
void	signal_child_handler(t_data *data);

// signal2.c
void	signal_herdoc(int signum);
void	sig_her(int signum);

#endif