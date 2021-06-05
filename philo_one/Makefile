# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/05 19:56:52 by sel-fadi          #+#    #+#              #
#    Updated: 2021/06/05 20:05:33 by sel-fadi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=philo_one

SRC = philo_one.c outils.c

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra

CC = gcc

all: $(NAME)

$(NAME):
	@$(CC) $(FLAGS) $(SRC) -Iincludes -o $(NAME) -fsanitize=address

fclean:
	@rm -rf $(NAME)

re : fclean all

.PHONY: fclean all re