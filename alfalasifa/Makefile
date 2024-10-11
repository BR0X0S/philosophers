# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oumondad <oumondad@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/16 16:15:58 by oumondad          #+#    #+#              #
#    Updated: 2024/10/11 16:39:05 by oumondad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = philosophers.c parcing.c lists.c

OBJ = ${SRC:.c=.o}

CC = cc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

all : ${NAME}

${NAME} : ${OBJ}
	${CC} ${CFLAGS} ${OBJ} -o ${NAME}

clean :
	rm -rf ${OBJ} ${BOBJ}

fclean : clean
	rm -rf ${NAME} ${BNAME}

re : fclean all

.PHONY : re all clean fclean

.SECONDARY: $(OBJ)