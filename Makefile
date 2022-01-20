NAME = philo
NAME_BONUS = philo_bonus

SRC = srcs/main.c srcs/ft_utils.c srcs/activities.c
SRC_BONUS = ./philo_bonus/philo_bonus.c

HEADER = ./include/
HEADER_BONUS = ./bonus/include

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

FLAGS = -Wall -Werror -Wextra -O2

all: $(NAME) $(HEADER)

bonus: $(NAME_BONUS) $(HEADER_BONUS)

$(NAME): $(OBJ) $(HEADER)
	gcc $(OBJ) -o $(NAME) -pthread

$(NAME_BONUS): $(OBJ_BONUS) $(HEADER_BONUS)
	gcc $(OBJ_BONUS) -o $(NAME_BONUS) -pthread

%.o:	%.c
	gcc $(FLAGS) -c $< -o $@ -pthread

clean:
	rm -f $(OBJ) $(OBJ_BONUS)

fclean:	clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

re_bonus: fclean bonus

.PHONY: clean fclean all re re_bonus