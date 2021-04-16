#include "minirt.h"

int	parse_sphere(char *line, char **end, t_scene *el)
{
	t_vect	pos;
	t_prop	prop;
	double	diam;
	int		error;

	line += 2;
	error = 0;
	if (consume_space(&line))
		error = 19;
	if (!error && parse_values(0, 0, &pos, &line))
		error = 20;
	if (!error && consume_space(&line))
		error = 19;
	if (!error && parse_unit(1, 0, &diam, &line))
		error = 21;
	if (!error && consume_space(&line))
		error = 19;
	if (!error && parse_prop(&prop, &line))
		error = 22;
	if (!error)
		error = scene_add_sphere(el, diam / 2, pos, prop);
	*end = line;
	return (error);
}

int	parse_square(char *line, char **end, t_scene *el)
{
	t_mikmak	m;
	t_prop		prop;
	int			error;

	line += 2;
	error = sub_parse_square(&m, &line);
	if (!error && consume_space(&line))
		error = 23;
	if (!error && parse_prop(&prop, &line))
		error = 27;
	if (!error)
		error = scene_add_square(el, m, prop);
	*end = line;
	return (error);
}

int	parse_triangle(char *line, char **end, t_scene *el)
{
	t_mikmak	m;
	t_vect		c;
	t_prop		prop;
	int			error;

	line += 2;
	error = sub_parse_triangle(&m, &line);
	if (!error && parse_values(0, 0, &c, &line))
		error = 31;
	if (!error && consume_space(&line))
		error = 28;
	if (!error && parse_prop(&prop, &line))
		error = 32;
	if (!error)
		error = scene_add_triangle(el, m, c, prop);
	*end = line;
	return (error);
}

int	parse_plane(char *line, char **end, t_scene *el)
{
	t_vect	pos;
	t_vect	norm;
	t_prop	prop;
	int		error;

	line += 2;
	error = 0;
	if (consume_space(&line))
		error = 33;
	if (!error && parse_values(0, 0, &pos, &line))
		error = 34;
	if (!error && consume_space(&line))
		error = 33;
	if (!error && parse_values(0, 1, &norm, &line))
		error = 35;
	if (!error && consume_space(&line))
		error = 33;
	if (!error && parse_prop(&prop, &line))
		error = 36;
	if (!error)
		error = scene_add_plane(el, norm, pos, prop);
	*end = line;
	return (error);
}

int	parse_circle(char *line, char **end, t_scene *el)
{
	t_mikmak	m;
	t_prop		prop;
	int			error;

	line += 2;
	error = sub_parse_circle(&m, &line);
	if (!error && consume_space(&line))
		error = 37;
	if (!error && parse_prop(&prop, &line))
		error = 41;
	if (!error)
		error = scene_add_circle(el, m, prop);
	*end = line;
	return (error);
}
