# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyacini <kyacini@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/31 14:24:36 by kyacini           #+#    #+#              #
#    Updated: 2023/09/02 14:29:33 by kyacini          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	src/add_spaces.c \
		src/list_cmd.c \
		src/main.c \
		src/utils.c \
		src/utils_list.c \
		src/quotes.c \
		src/quotes_b.c \
		src/parsing.c \
		src/variables.c \
		src/utils_var.c \
		src/split_func.c \
		src/split_func_b.c \

OBJS =	objs/add_spaces.o \
		objs/list_cmd.o\
		objs/main.o\
		objs/utils.o\
		objs/utils_list.o\
		objs/quotes.o \
		objs/quotes_b.o \
		objs/parsing.o \
		objs/variables.o \
		objs/utils_var.o \
		objs/split_func.o \
		objs/split_func_b.o \

NAME = minishell

CC = gcc

INC = include/

RM = rm -rf

CFLAGS = -Wall -Werror -Wextra

LIB = ./libft/libft.a

all : ${NAME}

objs/%.o : src/%.c
	mkdir -p ./objs
	$(CC)  -I${INC} -c $< -o $@ ${CFLAGS} -lreadline

%.o : %.c
	$(CC)  -I${INC} -c $< -o $@ ${CFLAGS} -lreadline

${NAME} : ${OBJS}
	make -C ./libft bonus
	$(CC) ${OBJS} -o ${NAME} ${LIB} ${CFLAGS} -lreadline

clean:
		$(RM) ${OBJS}
		$(RM) ./objs
		make clean -C ./libft

fclean: clean
		$(RM) $(NAME)
		$(RM) ./libft/libft.a

re:	fclean all

.PHONY:        all clean fclean re