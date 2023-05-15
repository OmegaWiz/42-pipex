# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/05 10:18:10 by kkaiyawo          #+#    #+#              #
#    Updated: 2023/05/15 15:08:43 by kkaiyawo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	pipex

SRCS			=	pipex.c pipex_init.c pipex_execute.c pipex_free.c \
					pipex_error.c arg_split.c ft_strprepend.c
LIBS			=	libft/libft.a

SRC_DIR			=	./src/
LIB_DIR			=	./lib/
BUILD_DIR		=	./build/

SRC				=	${addprefix ${BUILD_DIR},${SRCS}}
LIB				=	${addprefix ${LIB_DIR},${LIBS}}
OBJ				=	${SRC:.c=.o}

CC				=	gcc
CFLAG			=	-g -Wall -Wextra -Werror -O3 -fsanitize=address

all:			${LIB} ${BUILD_DIR} ${NAME}

clean:
					rm -f ${OBJ}

fclean:			clean
					rm -f $(NAME)

cleanlib:
					find ${LIB_DIR} -mindepth 1 -maxdepth 1 -exec make cleanb -C {} \;

fcleanlib:
					find ${LIB_DIR} -mindepth 1 -maxdepth 1 -exec make fcleanb -C {} \;

re:				fclean all

${BUILD_DIR}:
					mkdir -p ${BUILD_DIR}

${BUILD_DIR}%.o:${SRC_DIR}%.c
						${CC} ${CFLAG} -c -o $@ $^

${NAME}:		${OBJ}
					${CC} ${OBJ} ${wildcard ${LIB_DIR}*/*.a} -o ${NAME} ${CFLAG}

${LIB}:
					find ${LIB_DIR} -mindepth 1 -maxdepth 1 -exec make bonus -C {} \;

.PHONY:			all clean fclean re bonus
