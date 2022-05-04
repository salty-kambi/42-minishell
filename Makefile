# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mapontil <mapontil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/04 10:06:54 by lsuau             #+#    #+#              #
#    Updated: 2022/04/06 15:21:23 by mapontil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	minishell

INC 		=	inc/minishell.h inc/minishell_struct.h \
				inc/built_in.h \
				inc/exec.h \
				inc/parsing.h \
				inc/signal.h \
				inc/utils.h

SRC			=	main.c \
				prompt.c

BUILT_IN	=	cd_b.c \
				echo_b.c \
				env_b.c \
				exit_b.c \
				export_b.c \
				export2_b.c \
				export3_b.c \
				pwd_b.c \
				unset_b.c

EXEC		=	excode.c \
				handle_builtins.c \
				handle_redirect.c \
				perror_exit.c \
				pipex.c \
				pipex2.c \
				red_parsing.c \
				red_process.c \
				red_tab.c

PARSING		=	cmd_lst.c \
				cmd_split.c \
				env_in_line.c \
				env_in_line_2.c \
				env_in_line_her.c \
				env.c \
				env_starter.c \
				parsing_error.c \
				parsing_error_2.c \
				parsing.c \
				pipe_split.c \
				herdoc.c

SIGNAL		=	signal.c \
				signal2.c

UTILS		=	ft_itoa.c \
				ft_llitoa.c \
				ft_split.c \
				megajoin.c \
				stock_1.c \
				stock_2.c \
				stock_3.c \
				stock_4.c \
				stock_5.c \
				stock_6.c \
				stock_7.c

SRCS		=	${SRC} \
				${addprefix built_in/, ${BUILT_IN}} \
				${addprefix exec/, ${EXEC}} \
				${addprefix parsing/, ${PARSING}} \
				${addprefix signal/, ${SIGNAL}} \
				${addprefix utils/, ${UTILS}}

OBJS		=	${addprefix objs/, ${SRCS:.c=.o}}

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror

all:		${NAME}
objs/%.o:	src/%.c ${INC} Makefile
			@mkdir -p $(dir $@)
			${CC} ${CFLAGS} -c $< -o $@

${NAME}:	${OBJS} ${INC}
			${CC} ${CFLAGS} -lreadline -I  .brew/opt/readline/include/readline -o ${NAME} ${OBJS}

clean:
			rm -rf objs/

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
