#include <stdio.h>
#include <fcntl.h>
#include <pthread.h>
#include "libft.h"
#include "ft_printf.h"

int main (int argc, char *argv[])
{
	ft_putstr_fd(argv[1], 1);
	ft_printf("\n%d\n", argc);
	return (argc);
}
