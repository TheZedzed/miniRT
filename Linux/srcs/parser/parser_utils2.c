#include "minirt.h"

int	consume_space(char **s)
{
	if (ft_isspace(**s))
	{
		while (**s && ft_isspace(**s))
			++(*s);
		if (**s == '-' || ft_isdigit(**s))
			return (0);
	}
	return (1);
}

int	nblen(int sign, int nb)
{
	int	len;

	len = 1;
	if (nb < 0)
		++len;
	if (sign < 0)
		++len;
	while (nb <= -10 || nb >= 10)
	{
		nb /= 10;
		++len;
	}
	return (len);
}

int	check_end(char *s)
{
	if (s)
	{
		while (*s != '\n' && ft_isspace(*s))
			++s;
		if (*s && *s != '\n')
			return (-3);
	}
	return (0);
}

void	make_left(char **s, double *nb)
{
	unsigned int	exp;
	double			nb2;
	double			res;

	++(*s);
	exp = 10;
	res = *nb;
	while (**s && ft_isdigit(**s))
	{
		nb2 = (**s - 48);
		if (res >= 0)
			res += (nb2 / exp);
		else
			res -= (nb2 / exp);
		++(*s);
		exp *= 10;
	}
	*nb = res;
}
