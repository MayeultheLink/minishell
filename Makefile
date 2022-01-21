# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/14 13:42:32 by mde-la-s          #+#    #+#              #
#    Updated: 2022/01/21 19:07:29 by mde-la-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

LIBFT	=	libft/libft.a
SRCS	=	srcs/minishell.c \
			srcs/minishell/launch_minishell.c \
			srcs/minishell/parse_lineofcmd.c \
			srcs/minishell/handler.c \
			srcs/minishell/exit_minishell.c \
			srcs/lexer/split_lineofcmd.c \
			srcs/lexer/deactivate_chars.c \
			srcs/lexer/token.c \
			srcs/parser/check_error.c \
			srcs/parser/cmd.c \
			srcs/parser/parse_lst.c \
			srcs/parser/pipe.c \
			srcs/parser/redirections/create_files.c \
			srcs/parser/redirections/get_redir.c \
			srcs/parser/redirections/redir.c \
			srcs/builtins/echo.c \
			srcs/utils/utils.c \
			srcs/cmd/cmd_manager.c

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
CFLAGSR	=	-Wall -Wextra -Werror -I./headers -lreadline

OBJS	=	${SRCS:.c=.o}

all		:	${NAME}

$(NAME)	:	${OBJS}
		${MAKE} -C ./libft
#		${MAKE} bonus -C ./libft#
		@echo "$(_GREEN)LIBFT OK${_END}"
		${CC} ${CFLAGSR} -o $(NAME) ${OBJS} ${LIBFT}
		@echo "$(_GREEN)MANDATORY OK${_END}"

clean	:
		${MAKE} clean -C libft
		rm -f ${OBJS}

fclean	:	clean
		rm -f ${NAME}

re		:	fclean all

.PHONY	:	all clean fclean re
