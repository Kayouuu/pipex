# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/06 13:55:52 by psaulnie          #+#    #+#              #
#    Updated: 2022/01/26 14:23:00 by psaulnie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = srcs/main.c srcs/path.c srcs/forking.c srcs/destroy.c
OBJS = ${SRCS:.c=.o}
SRCS_BONUS = srcs_bonus/main_bonus.c srcs_bonus/path_bonus.c \
srcs_bonus/forking_bonus.c srcs_bonus/here_doc_bonus.c \
srcs_bonus/destroy_bonus.c srcs_bonus/process_bonus.c
LIBFT_SRCS = libft/ft_atoi.c libft/ft_bzero.c libft/ft_calloc.c \
libft/ft_isalnum.c libft/ft_isalpha.c libft/ft_isascii.c \
libft/ft_isdigit.c libft/ft_isprint.c libft/ft_itoa.c \
libft/ft_memchr.c libft/ft_memcmp.c libft/ft_memcpy.c \
libft/ft_memmove.c libft/ft_memset.c libft/ft_putchar_fd.c \
libft/ft_putstr_fd.c libft/ft_putendl_fd.c \
libft/ft_putnbr_fd.c libft/ft_split.c libft/ft_strchr.c libft/ft_strdup.c \
libft/ft_striteri.c libft/ft_strjoin.c \
libft/ft_strlcat.c libft/ft_strlcpy.c libft/ft_strlen.c libft/ft_strncmp.c \
libft/ft_strnstr.c libft/ft_strrchr.c libft/ft_strtrim.c libft/ft_substr.c \
libft/ft_tolower.c libft/ft_toupper.c  libft/ft_strmapi.c \
libft/ft_lstnew.c libft/ft_lstadd_front.c libft/ft_lstsize.c libft/ft_lstlast.c \
libft/ft_lstadd_back.c libft/ft_lstdelone.c libft/ft_lstclear.c \
libft/ft_lstiter.c libft/ft_lstmap.c libft/get_next_line.c \
libft/get_next_line_utils.c
OBJS_BONUS = ${SRCS_BONUS:.c=.o}
LIBFT = libft/
LIBFT_LIB = libft/libft.a
CFLAGS = -Wall -Wextra -Werror
CC = gcc
NAME = pipex
NAME_BONUS = pipex_bonus

all:	${NAME}

${NAME}: ${OBJS} ${LIBFT_LIB} inc/pipex.h Makefile
		${CC} ${CFLAGS} ${OBJS} ${LIBFT_LIB} -o ${NAME}

clean:
		rm -f ${OBJS} ${OBJS_BONUS}
		make -C ${LIBFT} clean

fclean: clean
		rm -f ${NAME} ${NAME_BONUS}
		make -C ${LIBFT} fclean

re: fclean all

bonus: ${NAME_BONUS}

${NAME_BONUS}: ${OBJS_BONUS} ${LIBFT_LIB} inc/pipex_bonus.h Makefile
	${CC} ${CFLAGS} ${OBJS_BONUS} ${LIBFT_LIB} -o ${NAME_BONUS}

${LIBFT_LIB}: libft/libft.h ${LIBFT_SRCS}
		make -C libft all

.PHONY:	all clean fclean re bonus
