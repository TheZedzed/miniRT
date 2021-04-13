/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_elem_nd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclerac <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 14:54:15 by aclerac           #+#    #+#             */
/*   Updated: 2021/04/08 07:37:20 by aclerac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "scene.h"
#include "parser.h"

int	parse_obj(char *line, t_scene *el)
{
	char	*end;
	int	error;

	error = 0;
	end = line;
	if (!ft_strncmp(line, "sp", 2))
		error = parse_sphere(line, &end, el);
	else if (!ft_strncmp(line, "sq", 2))
		error = parse_square(line, &end, el);
	else if (!ft_strncmp(line, "tr", 2))
		error = parse_triangle(line, &end, el);
	else if (!ft_strncmp(line, "pl", 2))
		error = parse_plane(line, &end, el);
	else if (!ft_strncmp(line, "ci", 2))
		error = parse_circle(line, &end, el);
	else if (!ft_strncmp(line, "cy", 2))
		error = parse_cylinder(line, &end, el);
	else if (!ft_strncmp(line, "co", 2))
		error = parse_cone(line, &end, el);
	else
		error = 3;
	if (!error)
		error = check_end(end);
	return (error);
}

int	parse_line(char *line, t_scene *el)
{
	char	*end;
	int	error;

	error = 0;
	end = NULL;
	while (ft_isspace(*line))
		++line;
	if (!ft_strncmp(line, "//", 2) || !*line)
		return (error);
	else if (*line == 'A')
		error = parse_ambient(line, &end, el);
	else if (*line == 'R')
		error = parse_resolution(line, &end, el);
	else if (*line == 'c' && ft_isspace(*(line + 1)))
		error = parse_camera(line, &end, el);
	else if (*line == 'l')
		error = parse_light(line, &end, el);
	else if (ft_strchr("sctp", *line)) 
		error = parse_obj(line, el);
	else
		error = 3;
	if (!error)
		error = check_end(end);
	return (error);
}

int	parse_rt(t_scene *el, char *rt)
{
	int		error;
	int		fd;
	int		status;
	char	*line;

	error = 0;
	status = 42;
	fd = open(rt, O_RDONLY);
	if (fd == -1)
		error = -2;
	while (!error && status > 0)
	{
		status = get_next_line(fd, &line);
		if (status == -1)
			error = -1;
		if (status > 0)
			error = parse_line(line, el);
		free(line);
	}
	close(fd);
	if (!el->cam_head || !el->w || !el->h)
		error = -5;
	return (error);
}
