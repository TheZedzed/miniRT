#include "minirt.h"

int	sub_parse_cylinder(t_mikmak *m, char **line)
{
	int	error;

	error = 0;
	if (consume_space(line))
		error = 42;
	if (!error && parse_values(0, 0, &m->pos, line))
		error = 43;
	if (!error && consume_space(line))
		error = 42;
	if (!error && parse_values(0, 1, &m->nor, line))
		error = 44;
	if (!error && consume_space(line))
		error = 42;
	if (!error && parse_unit(1, 0, &m->d1, line))
		error = 45;
	if (!error && consume_space(line))
		error = 42;
	if (!error && parse_unit(1, 0, &m->d2, line))
		error = 46;
	return (error);
}

int	sub_parse_cone(t_mikmak *m, char **line)
{
	int	error;

	error = 0;
	if (consume_space(line))
		error = 48;
	if (!error && parse_values(0, 0, &m->pos, line))
		error = 49;
	if (!error && consume_space(line))
		error = 48;
	if (!error && parse_values(0, 1, &m->nor, line))
		error = 50;
	if (!error && consume_space(line))
		error = 48;
	if (!error && parse_unit(1, 0, &m->d2, line))
		error = 51;
	if (!error && consume_space(line))
		error = 48;
	if (!error && parse_unit(1, 0, &m->d1, line))
		error = 52;
	return (error);
}

int	parse_cylinder(char *line, char **end, t_scene *el)
{
	t_mikmak	m;
	t_prop		prop;
	int			error;

	line += 2;
	error = sub_parse_cylinder(&m, &line);
	if (!error && consume_space(&line))
		error = 42;
	if (!error && parse_prop(&prop, &line))
		error = 47;
	if (!error)
		error = scene_add_cylinder(el, m, prop);
	*end = line;
	return (error);
}

int	parse_cone(char *line, char **end, t_scene *el)
{
	t_mikmak	m;
	t_prop		prop;
	int			error;

	line += 2;
	error = sub_parse_cone(&m, &line);
	if (!error && consume_space(&line))
		error = 48;
	if (!error && parse_prop(&prop, &line))
		error = 53;
	if (!error)
		error = scene_add_cone(el, m, prop);
	*end = line;
	return (error);
}
