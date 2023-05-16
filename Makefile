# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/05 10:18:10 by kkaiyawo          #+#    #+#              #
#    Updated: 2023/05/16 08:44:14 by kkaiyawo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### EXECUTABLE ###
NAME			=	pipex

### DIR ###
SRC_DIR			=	./src/
BONUS_DIR		=	./bonus/
LIB_DIR			=	./lib/
BUILD_DIR		=	./build/

### FILES ###
SRC_FILE		=	pipex.c pipex_init.c pipex_execute.c pipex_free.c \
					pipex_error.c arg_split.c ft_strprepend.c pipex_malloc.c
BONUS_FILE		=	pipex_bonus.c pipex_init_bonus.c pipex_execute_bonus.c \
					pipex_free_bonus.c pipex_error_bonus.c arg_split_bonus.c \
					ft_strprepend_bonus.c pipex_malloc_bonus.c
LIB_FILE		=	libft/libft.a

### PATH ###
SRC				=	${addprefix ${BUILD_DIR},${SRC_FILE}}
BONUS			=	${addprefix ${BUILD_DIR},${BONUS_FILE}}
LIB				=	${addprefix ${LIB_DIR},${LIB_FILE}}

### OBJECTS ###
SRC_OBJ			=	${SRC:.c=.o}
BONUS_OBJ		=	${BONUS:.c=.o}

### COMPILATION ###
CC				=	gcc
CFLAG			=	-g -Wall -Wextra -Werror -O3 -fsanitize=address
RM				=	rm -f

all:			${LIB} ${BUILD_DIR} ${NAME}

${NAME}:		${SRC_OBJ}
					${CC} ${CFLAG} ${SRC_OBJ} ${wildcard ${LIB_DIR}*/*.a} -o ${NAME}

bonus:			${LIB} ${BUILD_DIR} ${BONUS_OBJ}
					${CC} ${CFLAG} -o ${NAME} ${BONUS_OBJ} ${LIB}

${LIB}:
					find ${LIB_DIR} -mindepth 1 -maxdepth 1 -exec make bonus -C {} \;

${BUILD_DIR}:
					mkdir -p ${BUILD_DIR}

${BUILD_DIR}%.o:${SRC_DIR}%.c
						${CC} ${CFLAG} -c -o $@ $^

clean:
					${RM} ${SRC_OBJ} ${BONUS_OBJ}
					find ${LIB_DIR} -mindepth 1 -maxdepth 1 -exec make cleanb -C {} \;

fclean:			clean
					${RM} ${NAME}
					find ${LIB_DIR} -mindepth 1 -maxdepth 1 -exec make fcleanb -C {} \;

re:				fclean all

b:				bonus clean

m:				all clean

.PHONY:			all clean fclean re bonus
