NAME = philo
NAME_BONUS = philo_bonus
LIBFT = libft/libft.a
PRINTF = printf/libftprintf.a

SRC = philo.c
SRC_BONUS = ./philo_bonus/philo_bonus.c

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

FLAGS = -Wall -Werror -Wextra -O2 -pthread

all: $(LIBFT) $(PRINTF) $(NAME) 

bonus: $(LIBFT) $(PRINTF) $(NAME_BONUS)

$(LIBFT):
	make -C libft

$(PRINTF):
	make -C printf

$(NAME): $(OBJ) Makefile $(LIBFT) $(PRINTF)
	gcc $(OBJ) -L./libft -lft -L./printf -lftprintf -o $(NAME)

$(NAME_BONUS): $(OBJ_BONUS) Makefile $(LIBFT)
	gcc $(OBJ_BONUS) -L./libft -lft -L./printf -lftprintf -o $(NAME_BONUS)

%.o:	%.c
	gcc $(FLAGS) -I libft -I printf -c $< -o $@

clean:
	make clean -sC libft
	make clean -sC printf
	rm -f $(OBJ) $(OBJ_BONUS)

fclean:	clean
	make fclean -sC libft
	make fclean -sC printf
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: clean fclean all re