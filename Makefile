# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/06 13:55:52 by psaulnie          #+#    #+#              #
#    Updated: 2022/01/15 16:56:16 by psaulnie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = srcs/main.c srcs/path.c srcs/forking.c srcs/destroy.c
OBJS = ${SRCS:.c=.o}
SRCS_BONUS = srcs_bonus/main_bonus.c srcs_bonus/path_bonus.c \
srcs_bonus/forking_bonus.c srcs_bonus/here_doc_bonus.c
OBJS_BONUS = ${SRCS_BONUS:.c=.o}
LIBFT = libft/
LIBFT_LIB = libft/libft.a
CFLAGS = -Wall -Wextra -Werror
CC = gcc
NAME = pipex
NAME_BONUS = pipex_bonus

all: ${NAME}

${NAME}: ${OBJS} ${LIBFT_LIB} inc/pipex.h Makefile
		${CC} ${CFLAGS} ${OBJS} ${LIBFT_LIB} -o ${NAME}

clean:
		rm -f ${OBJS} ${OBJS_BONUS}
		make -s -C ${LIBFT} clean

fclean: clean
		rm -f ${NAME} ${NAME_BONUS}
		make -s -C ${LIBFT} fclean

re: fclean all

${NAME_BONUS}: ${OBJS_BONUS} ${LIBFT_LIB} inc/pipex_bonus.h Makefile
	${CC} ${CFLAGS} ${OBJS_BONUS} ${LIBFT_LIB} -o ${NAME_BONUS}

${LIBFT_LIB}:
		make -C ${LIBFT}

.PHONY:	all clean fclean re bonus
