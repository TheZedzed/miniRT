#include "minirt.h"

int	sub_parse_square(t_mikmak *m, char **line)
{
	int	error;

	error = 0;
	if (consume_space(line))
		error = 23;
	if (!error && parse_values(0, 0, &m->pos, line))
		error = 24;
	if (!error && consume_space(line))
		error = 23;
	if (!error && parse_values(0, 1, &m->nor, line))
		error = 25;
	if (!error && consume_space(line))
		error = 23;
	if (!error && parse_unit(1, 0, &m->d1, line))
		error = 26;
	return (error);
}

int	sub_parse_triangle(t_mikmak *m, char **line)
{
	int	error;

	error = 0;
	if (consume_space(line))
		error = 28;
	if (!error && parse_values(0, 0, &m->pos, line))
		error = 29;
	if (!error && consume_space(line))
		error = 28;
	if (!error && parse_values(0, 0, &m->nor, line))
		error = 30;
	if (!error && consume_space(line))
		error = 28;
	return (error);
}

int	sub_parse_circle(t_mikmak *m, char **line)
{
	int	error;

	error = 0;
	if (consume_space(line))
		error = 37;
	if (!error && parse_values(0, 0, &m->pos, line))
		error = 38;
	if (!error && consume_space(line))
		error = 37;
	if (!error && parse_values(0, 1, &m->nor, line))
		error = 39;
	if (!error && consume_space(line))
		error = 37;
	if (!error && parse_unit(1, 0, &m->d1, line))
		error = 40;
	return (error);
}
