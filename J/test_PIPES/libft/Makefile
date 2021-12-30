# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpauline <jpauline@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/11 13:45:20 by jpauline          #+#    #+#              #
#    Updated: 2021/10/19 18:16:15 by jpauline         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	ft_memset.c ft_memcpy.c ft_memccpy.c \
			ft_memmove.c ft_memchr.c ft_memcmp.c \
			ft_bzero.c \
			ft_strlen.c \
			ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
			ft_toupper.c ft_tolower.c \
			ft_strchr.c ft_strrchr.c ft_strncmp.c \
			ft_strlcpy.c ft_strlcat.c ft_strnstr.c \
			ft_atoi.c ft_itoa.c\
			ft_calloc.c ft_strdup.c \
			ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_strmapi.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			\
			ft_strcmp.c \
			get_next_line.c

OBJS	=	${SRCS:.c=.o}

BONUS	=	ft_lstnew.c ft_lstsize.c ft_lstlast.c \
			ft_lstadd_front.c ft_lstadd_back.c \
			ft_lstdelone.c ft_lstclear.c \
			ft_lstiter.c

B_OBJS	=	${BONUS:.c=.o}

NAME	=	libft.a

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -f

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}	:	${OBJS}
	ar rcs ${NAME} ${OBJS}

bonus	:	${OBJS} ${B_OBJS}
	ar rcs ${NAME} ${OBJS} ${B_OBJS}  

all		:	${NAME}

clean	:
	${RM} ${OBJS} ${B_OBJS}

fclean	:	clean
	${RM} ${NAME}

re		:	fclean all

.PHONY	:	all clean fclean re bonus
