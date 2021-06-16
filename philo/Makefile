# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/05 19:56:52 by sel-fadi          #+#    #+#              #
#    Updated: 2021/06/16 15:38:09 by sel-fadi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=philo

SRC = philo.c outils.c outils_1.c life_circle.c supervisors.c

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