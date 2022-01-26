# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Cluco <cluco@student.21-school.ru>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/24 15:22:11 by Cluco             #+#    #+#              #
#    Updated: 2022/01/26 14:49:55 by Cluco            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_BONUS = philo_bonus

SRC_BONUS = srcs/main.c srcs/ft_utils.c srcs/activities.c

HEADER_BONUS = ./include

OBJ_BONUS = $(SRC_BONUS:.c=.o)

FLAGS = -Wall -Werror -Wextra -O2

bonus: $(NAME_BONUS) $(HEADER_BONUS)

$(NAME_BONUS): $(OBJ_BONUS) $(HEADER_BONUS) Makefile
	gcc $(OBJ_BONUS) -o $(NAME_BONUS) -pthread

%.o:	%.c
	gcc $(FLAGS) -c $< -o $@ -pthread

clean:
	rm -f $(OBJ_BONUS)

fclean:	clean
	rm -f $(NAME_BONUS)

re: fclean bonus

.PHONY: clean fclean re
