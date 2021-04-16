#include "minirt.h"

unsigned int	text_color(t_scene *el, t_inter *inter)
{
	t_vect	tmp;
	t_vect	vp;
	double	d[4];
	int		i[2];

	vp = sub(&inter->obj.pos, &inter->point);
	normalize(&vp);
	d[0] = acos(-dot(&((t_vect){0, 1, 0}), &vp));
	d[2] = d[0] / M_PI;
	d[3] = (acos(dot(&vp, &((t_vect){1, 0, 0})) / sin(d[0]))) / (2 * M_PI);
	tmp = cross(&((t_vect){0, 1, 0}), &((t_vect){1, 0, 0}));
	if (dot(&tmp, &vp) > 0)
		d[1] = d[3];
	else
		d[1] = 1 - d[3];
	i[0] = (int)(d[1] * el->txt.w)*(el->txt.bpp / 8);
	i[1] = (int)(d[2] * el->txt.h)*el->txt.lz;
	return ((unsigned int)el->txt.data[i[0] + i[1]]);
}

int	set_texture(t_scene *el)
{
	int	error;

	error = 3;
	el->txt.img = (char *)mlx_xpm_file_to_image(el->mlx,
			"./textures/txt.xpm", &el->txt.w, &el->txt.h);
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
	if (el->save)
	{
		scene_to_bmp(*el, "./shining.bmp");
		free_all(el);
	}
	mlx_put_image_to_window(el->mlx, el->win, el->img, 0, 0);
	return (0);
}
