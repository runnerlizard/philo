#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c > 64) && (c < 91))
		return (1);
	if ((c > 96) && (c < 123))
		return (2);
	if ((c > 47) && (c < 58))
		return (4);
	return (0);
}
