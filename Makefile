NAME = philo
NAME_BONUS = philo_bonus

SRC = philo.c message.c ft_putnbr_fd.c
SRC_BONUS = ./philo_bonus/philo_bonus.c message.c ft_putnbr_fd.c

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

FLAGS = -Wall -Werror -Wextra -O2

all: $(NAME) philo.h

bonus: $(NAME_BONUS) philo.h

$(NAME): $(OBJ) Makefile philo.h 
	gcc $(OBJ) -o $(NAME) -pthread

$(NAME_BONUS): $(OBJ_BONUS) Makefile philo.h 
	gcc $(OBJ_BONUS) -o $(NAME_BONUS) -pthread

%.o:	%.c
	gcc $(FLAGS) -c $< -o $@ -pthread

clean:
	rm -f $(OBJ) $(OBJ_BONUS)

fclean:	clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: clean fclean all re