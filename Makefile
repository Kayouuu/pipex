# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/06 13:55:52 by psaulnie          #+#    #+#              #
#    Updated: 2021/12/14 15:30:12 by psaulnie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c path.c first_split.c forking.c
LIBFT = libft/
CFLAGS = -Wall -Wextra -Werror
CC = gcc
NAME = pipex

${NAME}: all

all: libft
		${CC} ${CFLAGS} -o pipex ${SRCS} libft.a

clean:
		rm -f ${OBJS}
		make -C ${LIBFT} clean

fclean: clean
		rm -f ${NAME}
		rm -f libft.a
		make -C ${LIBFT} fclean

re: fclean all

libft:
		make -C ${LIBFT}

.PHONY:	all clean fclean re libft
