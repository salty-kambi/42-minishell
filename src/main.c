/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuau <lsuau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 17:24:33 by lsuau             #+#    #+#             */
/*   Updated: 2022/03/23 14:21:17 by lsuau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	g_excode;

void	data_init(t_data *data, char **envp)
{
	g_excode = 0;
	data->env = env_init(data, envp);
	data->cmds = 0;
	data->nb_cmd = 0;
	data->run = 1;
	data->pwd = 0;
	if (tcgetattr(0, &data->term_base) == -1)
	{
		perror("tcgetattr");
		data->run = 0;
	}
}

static void	ctrld_exit(t_data *data, char *prompt)
{
	tcsetattr(0, TCSANOW, &data->term_base);
	write(1, "exit\n", 5);
	env_lstclear(data);
	free(prompt);
	exit(g_excode);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*line;
	char	*prompt;

	(void) argc;
	(void) argv;
	data_init(&data, envp);
	while (data.run)
	{
		signal_handler();
		prompt = set_prompt(&data);
		line = readline(prompt);
		if (!line)
			ctrld_exit(&data, prompt);
		if (line && line[0])
			add_history(line);
		le_parsing(&data, line);
		if (data.nb_cmd)
			pipex(data.cmds, &data);
		cmd_lstclear(&data);
		free(line);
		free(prompt);
	}
	env_lstclear(&data);
	free(data.pwd);
}
