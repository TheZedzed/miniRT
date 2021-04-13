/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_elem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclerac <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 14:50:44 by aclerac           #+#    #+#             */
/*   Updated: 2021/04/07 08:12:54 by aclerac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "scene.h"
#include "parser.h"

int	parse_ambient(char *line, char **end, t_scene *el)
{
	static int	done;
	int		error;

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
	int		error;

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
	int	error;

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
	int	error;

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

int	parse_sphere(char *line, char **end, t_scene *el)
{
	t_vect	pos;
	t_prop	prop;
	double	diam;
	int	error;

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
	int		error;

	line += 2;
	error = 0;
	if (consume_space(&line))
		error = 23;
	if (!error && parse_values(0, 0, &m.pos, &line))
		error = 24;
	if (!error && consume_space(&line))
		error = 23;
	if (!error && parse_values(0, 1, &m.nor, &line))
		error = 25;
	if (!error && consume_space(&line))
		error = 23;
	if (!error && parse_unit(1, 0, &m.d1, &line))
		error = 26;
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
	int		error;

	line += 2;
	error = 0;
	if (consume_space(&line))
		error = 28;
	if (!error && parse_values(0, 0, &m.pos, &line))
		error = 29;
	if (!error && consume_space(&line))
		error = 28;
	if (!error && parse_values(0, 0, &m.nor, &line))
		error = 30;
	if (!error && consume_space(&line))
		error = 28;
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
	int	error;

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
	int		error;

	line += 2;
	error = 0;
	if (consume_space(&line))
		error = 37;
	if (!error && parse_values(0, 0, &m.pos, &line))
		error = 38;
	if (!error && consume_space(&line))
		error = 37;
	if (!error && parse_values(0, 1, &m.nor, &line))
		error = 39;
	if (!error && consume_space(&line))
		error = 37;
	if (!error && parse_unit(1, 0, &m.d1, &line))
		error = 40;
	if (!error && consume_space(&line))
		error = 37;
	if (!error && parse_prop(&prop, &line))
		error = 41;
	if (!error)
		error = scene_add_circle(el, m, prop);
	*end = line;
	return (error);
}

int	parse_cylinder(char *line, char **end, t_scene *el)
{
	t_mikmak	m;
	t_prop		prop;
	int		error;

	line += 2;
	error = 0;
	if (consume_space(&line))
		error = 42;
	if (!error && parse_values(0, 0, &m.pos, &line))
		error = 43;
	if (!error && consume_space(&line))
		error = 42;
	if (!error && parse_values(0, 1, &m.nor, &line))
		error = 44;
	if (!error && consume_space(&line))
		error = 42;
	if (!error && parse_unit(1, 0, &m.d1, &line))
		error = 45;
	if (!error && consume_space(&line))
		error = 42;
	if (!error && parse_unit(1, 0, &m.d2, &line))
		error = 46;
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
	int		error;

	line += 2;
	error = 0;
	if (consume_space(&line))
		error = 48;
	if (!error && parse_values(0, 0, &m.pos, &line))
		error = 49;
	if (!error && consume_space(&line))
		error = 48;
	if (!error && parse_values(0, 1, &m.nor, &line))
		error = 50;
	if (!error && consume_space(&line))
		error = 48;
	if (!error && parse_unit(1, 0, &m.d2, &line))
		error = 51;
	if (!error && consume_space(&line))
		error = 48;
	if (!error && parse_unit(1, 0, &m.d1, &line))
		error = 52;
	if (!error && consume_space(&line))
		error = 48;
	if (!error && parse_prop(&prop, &line))
		error = 53;
	if (!error)
		error = scene_add_cone(el, m, prop);
	*end = line;
	return (error);
}

int	parse_unit(int positive, int unit, double *value, char **s)
{
	double	nb2;
	double	nb;
	unsigned int	exp;

	exp = 10;
	nb = ft_atoi(*s);
	(*s) += nblen((int)nb);
	if (**s == '.')
	{
		++(*s);
		while (**s && ft_isdigit(**s))
		{
			nb2 = (**s - 48);
			if (nb >= 0)
				nb += (nb2 / exp);
			else
				nb -= (nb2 / exp);
			++(*s);
			exp *= 10;
		}
	}
	*value = nb;
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
	if (!error && (parse_unit(1, 0, &el->refraction, s) || (el->refraction && el->refraction < 1)))
		error = 1;
	return (error);
}

