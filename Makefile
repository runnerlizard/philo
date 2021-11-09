NAME = philo
NAME_BONUS = philo_bonus

SRC = philo.c
SRC_BONUS = ./philo_bonus/philo_bonus.c

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

FLAGS = -Wall -Werror -Wextra -pthread

all: $(NAME) 

bonus: $(NAME_BONUS)

$(NAME): $(OBJ) Makefile
	gcc $(OBJ) -o $(NAME)

$(NAME_BONUS): $(OBJ_BONUS) Makefile
	gcc $(OBJ_BONUS) -o $(NAME_BONUS)

%.o:	%.c
	@gcc $(FLAGS) -c $< -o $@

clean:
	@rm $(OBJ) $(OBJ_BONUS)

fclean:	clean
	@rm $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: clean fclean all re