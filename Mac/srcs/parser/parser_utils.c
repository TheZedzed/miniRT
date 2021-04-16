#include "minirt.h"

int	parse_unit(int positive, int unit, double *value, char **s)
{
	double			nb;
	int				sign;

	sign = 1;
	nb = ft_atoi(*s);
	if (**s == '-' && !nb)
		sign = -1;
	(*s) += nblen(sign, (int)nb);
	if (**s == '.')
		make_left(s, &nb);
	*value = (sign * nb);
	if ((positive && nb < 0) || (unit && fabs(nb) > 1))
		return (1);
	return (0);
}

int	parse_values(int positive, int unit, t_vect *el, char **s)
{
	int	error;

	error = 0;
	if (parse_unit(positive, unit, &el->x, s))
		error = 1;
	if (!error && *(*s)++ != ',')
		error = 1;
	if (!error && parse_unit(positive, unit, &el->y, s))
		error = 1;
	if (!error && *(*s)++ != ',')
		error = 1;
	if (!error && parse_unit(positive, unit, &el->z, s))
		error = 1;
	return (error);
}

int	parse_colors(int positive, int unit, t_vect *el, char **s)
{
	int	error;

	error = 0;
	if (parse_unit(positive, unit, &el->x, s) || el->x > 255)
		error = 1;
	if (!error && *(*s)++ != ',')
		error = 1;
	if (!error && (parse_unit(positive, unit, &el->y, s) || el->y > 255))
		error = 1;
	if (!error && *(*s)++ != ',')
		error = 1;
	if (!error && (parse_unit(positive, unit, &el->z, s) || el->z > 255))
		error = 1;
	if (!error)
	{
		el->x /= 255;
		el->y /= 255;
		el->z /= 255;
	}
	return (error);
}

int	parse_prop(t_prop *el, char **s)
{
	int	error;

	error = 0;
	if (parse_colors(1, 0, &el->diffuse, s))
		error = 1;
	if (!error && consume_space(s))
		error = 1;
	if (!error && parse_unit(1, 1, &el->reflection, s))
		error = 1;
	if (!error && consume_space(s))
		error = 1;
	if (!error && (parse_unit(1, 0, &el->refraction, s)
			|| (el->refraction && el->refraction < 1)))
		error = 1;
	return (error);
}
