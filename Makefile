# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/14 13:42:32 by mde-la-s          #+#    #+#              #
#    Updated: 2022/02/01 12:48:59 by mde-la-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

LIBFT	=	libft/libft.a
SRCS	=	srcs/main/minishell.c \
			srcs/main/launch_minishell.c \
			srcs/main/handler.c \
			srcs/main/parse_lineofcmd.c \
			srcs/main/exit_minishell.c \
			srcs/lexer/split_lineofcmd.c \
			srcs/lexer/deactivate_chars.c \
			srcs/lexer/token.c \
			srcs/parser/parse_lst.c \
			srcs/parser/treat_dollar.c \
			srcs/parser/command/get_cmd.c \
			srcs/parser/command/get_path.c \
			srcs/parser/command/check_error.c \
			srcs/parser/redirections/redir.c \
			srcs/parser/redirections/get_redir.c \
			srcs/parser/redirections/create_files.c \
			srcs/parser/redirections/heredoc.c \
			srcs/parser/redirections/check_error.c \
			srcs/parser/pipe/pipe.c \
			srcs/utils/utils.c \
			srcs/utils/free_stuff.c \
			srcs/execute/fd_pid.c \
			srcs/execute/cmd_manager.c \
			srcs/execute/cmd_manager_utils.c \
			srcs/execute/builtins/env.c \
			srcs/execute/builtins/launch_builtin.c \
			srcs/execute/builtins/path_echo.c \
			srcs/execute/env/free_stuff.c \
			srcs/execute/env/init_env.c \
			srcs/execute/env/mod_env.c \
			srcs/execute/env/utils.c

# Colors
_GREY=$ \x1b[30m
_RED=$ \x1b[31m
_GREEN=$ \x1b[32m
_YELLOW=$ \x1b[33m
_BLUE=$ \x1b[34m
_PURPLE=$ \x1b[35m
_CYAN=$ \x1b[36m
_WHITE=$ \x1b[37m
_END=$ \x1b[0m

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -I./headers 
OBJS	=	${SRCS:.c=.o}

all		:	${NAME}

$(NAME)	:	${OBJS}
		${MAKE} -C ./libft
		@echo "$(_GREEN)LIBFT OK${_END}"
		${CC} ${CFLAGS} -o $(NAME) -lreadline ${OBJS} ${LIBFT}
		@echo "$(_GREEN)MANDATORY OK${_END}"

clean	:
		${MAKE} clean -C libft
		rm -f ${OBJS}

fclean	:	clean
		rm -f ${NAME}

re		:	fclean all

.PHONY	:	all clean fclean re
