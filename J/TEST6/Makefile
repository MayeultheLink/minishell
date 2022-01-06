# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/14 13:42:32 by mde-la-s          #+#    #+#              #
#    Updated: 2022/01/04 18:33:37 by mde-la-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

LIBFT	=	libft/libft.a
SRCS	=	srcs/minishell.c \
			srcs/launch_cmd.c \
			srcs/str_control.c \
			srcs/utils.c \
			srcs/split_minishell.c \
			srcs/parsing/check_error.c \
			srcs/parsing/cmd.c \
			srcs/parsing/parse_lst.c \
			srcs/parsing/pipe.c \
			srcs/parsing/redirections/create_files.c \
			srcs/parsing/redirections/get_redir.c \
			srcs/parsing/redirections/redir.c \
			srcs/cmd_manager.c

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

CC		=	clang
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
