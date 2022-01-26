# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Cluco <cluco@student.21-school.ru>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/24 15:22:16 by Cluco             #+#    #+#              #
#    Updated: 2022/01/26 14:49:05 by Cluco            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = srcs/main.c srcs/ft_utils.c srcs/activities.c

HEADER = ./include/

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra -O2

all: $(NAME) $(HEADER)

$(NAME): $(OBJ) $(HEADER) Makefile
	gcc $(OBJ) -o $(NAME) -pthread

%.o:	%.c
	gcc $(FLAGS) -c $< -o $@ -pthread

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re: fclean all

re_bonus: fclean

.PHONY: clean fclean all re
