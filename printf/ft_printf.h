#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_putnbr_fd (unsigned int n);
int		ft_print_sign (int n);
int		ft_hub_int(char c, int d);
int		fl(char c, unsigned long d);
int		ft_count (int d);
int		ft_putpercent(char c);
int		ft_putchar(int n);
int		ft_putstr_fd(char *s, int fd);
void	ft_write_hex(unsigned long d, int registr);
int		ft_hex_length(unsigned long n);
int		ft_hex (unsigned long n, int registr);
int		ft_print_p (unsigned long p);
int		ft_printf (const char *input, ...);
#endif
