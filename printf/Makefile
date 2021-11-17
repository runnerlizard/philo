NAME	= libftprintf.a

SRCS	= ft_printf.c ft_putchar.c ft_putnbr_fd.c 

OBJS	= $(SRCS:.c=.o)

CFLAGS	= -Wall -Werror -Wextra -O2
	
all:	$(NAME)
		
$(NAME): $(OBJS) Makefile
	ar rcs $(NAME) $(OBJS)
	ranlib $(NAME)

%.o:	%.c
	gcc $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
