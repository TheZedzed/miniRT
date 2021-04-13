/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 03:13:54 by azeraoul          #+#    #+#             */
/*   Updated: 2021/04/12 08:30:54 by aclerac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "scene.h"
#include "parser.h"
#include "inter.h"
#include "ray_tracer.h"
#include "multithreading.h"
#include "ray_tracer.h"

int	set_texture(t_scene *el)
{
	int	error;

	error = 3;
	el->txt.img = (char *)mlx_xpm_file_to_image(el->mlx,
			"./textures/test.xpm", &el->txt.w, &el->txt.h);
	if (el->txt.img)
		el->txt.data = mlx_get_data_addr(el->txt.img, &el->txt.bpp,
			&el->txt.lz, &el->txt.endian);
	if (el->txt.data)
		error = 0;
	return (error);
}

void	scene_to_bmp(t_scene s, char *path)
{
	int	fd;
	int	i;
	int	j;

	fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	i = s.h - 1;
	write(fd, (char []){'B', 'M'}, 2);
	write(fd, (int []){54 + (s.w * s.h) * 4, 0x00, 0x36, 0x28, s.w, s.h,
		0x200001, 0, 0, 0x00130b, 0x00130b, 0, 0}, 52);
	while (i >= 0)
	{
		j = -1;
		while (++j < s.w)
			write(fd, (char *)s.img_data + i * s.lz + j * 4, 4);
		i--;
	}
	close(fd);
}

int	draw(t_scene *el)
{
	t_scene	childs[4];

	init_base(&el->base, &(el->cam_current->axe));
	setup_multithreading(*el, childs);
	lunch_multithreading(childs);
	mlx_put_image_to_window(el->mlx, el->win, el->img, 0, 0);
	if (el->save)
	{
		scene_to_bmp(*el, "./shining.bmp");
		free_all(el);
	}
	return (0);
}

int	change_camera(int direction, t_scene *el)
{
	int	useless;

	useless = 0;
	if (el->cam_head == el->cam_tail)
		useless = 1;
	if (!useless)
	{
		if (direction == LEFT)
			el->cam_current = el->cam_current->back;
		else
			el->cam_current = el->cam_current->next;
	}
	return (useless);
}
