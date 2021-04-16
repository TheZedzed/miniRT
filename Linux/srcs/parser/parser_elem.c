#include "minirt.h"

int	parse_ambient(char *line, char **end, t_scene *el)
{
	static int	done;
	int			error;

	++line;
	error = 0;
	if (done)
		error = 4;
	if (!done && consume_space(&line))
		error = 5;
	if (!error && parse_unit(1, 1, &el->amb.ratio, &line))
		error = 6;
	if (!error && consume_space(&line))
		error = 5;
	if (!error && parse_colors(1, 0, &el->amb.intensity, &line))
		error = 7;
	done = 1;
	*end = line;
	return (error);
}

int	parse_resolution(char *line, char **end, t_scene *el)
{
	static int	done;
	int			error;

	++line;
	error = 0;
	if (done)
		error = 8;
	if (!done && consume_space(&line))
		error = 9;
	if (!error && parse_unit(1, 0, &el->w, &line))
		error = 10;
	if (!error && consume_space(&line))
		error = 9;
	if (!error && parse_unit(1, 0, &el->h, &line))
		error = 10;
	if (el->w > 1920)
		el->w = 1920;
	if (el->h > 1080)
		el->h = 1080;
	done = 1;
	(*end) = line;
	return (error);
}

int	parse_camera(char *line, char **end, t_scene *el)
{
	t_vect	pos;
	t_vect	norm;
	double	fov;
	int		error;

	++line;
	error = 0;
	if (consume_space(&line))
		error = 11;
	if (parse_values(0, 0, &pos, &line))
		error = 12;
	if (!error && consume_space(&line))
		error = 11;
	if (!error && parse_values(0, 1, &norm, &line))
		error = 13;
	if (!error && consume_space(&line))
		error = 11;
	if (!error && parse_unit(1, 0, &fov, &line))
		error = 14;
	if (fov > 180)
		error = 14;
	if (!error)
		error = scene_add_cam(el, pos, norm, fov);
	*end = line;
	return (error);
}

int	parse_light(char *line, char **end, t_scene *el)
{
	t_vect	pos;
	t_vect	color;
	double	ratio;
	int		error;

	++line;
	error = 0;
	if (consume_space(&line))
		error = 15;
	if (!error && parse_values(0, 0, &pos, &line))
		error = 16;
	if (!error && consume_space(&line))
		error = 15;
	if (!error && parse_unit(1, 1, &ratio, &line))
		error = 17;
	if (!error && consume_space(&line))
		error = 15;
	if (!error && parse_colors(1, 0, &color, &line))
		error = 18;
	if (!error)
		error = scene_add_lum(el, pos, ratio, color);
	*end = line;
	return (error);
}
