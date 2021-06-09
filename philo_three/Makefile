# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/05 19:56:52 by sel-fadi          #+#    #+#              #
#    Updated: 2021/06/07 11:28:01 by sel-fadi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=philo_two

SRC = philo_two.c outils.c

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra

CC = gcc

all: $(NAME)

$(NAME):
	@$(CC) $(FLAGS) $(SRC) -o $(NAME)

fclean:
	@rm -rf $(NAME)

re : fclean all

.PHONY: fclean all re