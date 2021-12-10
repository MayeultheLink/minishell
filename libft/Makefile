# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mde-la-s <mde-la-s@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/26 15:31:23 by mde-la-s          #+#    #+#              #
#    Updated: 2021/09/02 17:45:40 by mde-la-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

SRCS	=	ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_memccpy.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c

BONUS	=	ft_lstadd_back.c \
		ft_lstadd_front.c \
		ft_lstdelone.c \
		ft_lstlast.c \
		ft_lstnew.c \
		ft_lstsize.c

OBJS	=	${SRCS:.c=.o}

OBJSBONUS = 	${BONUS:.c=.o}

CC	=	clang

CFLAGS	=	-Wall -Wextra -Werror

all	:	 ${NAME}

$(NAME)	: ${OBJS}
	${CC} ${CFLAGS} -c ${SRCS}
	ar rcs ${NAME} ${OBJS}

bonus:	${OBJSBONUS}
		${CC} ${CFLAGS} -c ${BONUS}
		ar rcs ${NAME} ${OBJSBONUS}

clean	:
	rm -f ${OBJS} ${OBJSBONUS}

fclean	: clean
	rm -f ${NAME}

re		: fclean all

.PHONY : all clean fclean re
