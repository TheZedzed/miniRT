#include "minirt.h"

void	sub_init(t_scene *el)
{
	ft_memset(el, 0, sizeof(t_scene));
	el->gamma = 1;
	el->reflect_depth = 1;
	el->aliasing = 1;
}

int	set_mlx(t_scene *el)
{
	int	error;

	error = 2;
	el->title = "miniRT";
	el->cam_current = el->cam_head;
	init_base(&el->base, &el->cam_current->axe);
	el->mlx = mlx_init();
	if (el->mlx)
	{
		if (!el->save)
			el->win = mlx_new_window(el->mlx, el->w, el->h, el->title);
		el->img = mlx_new_image(el->mlx, el->w, el->h);
		el->img_data = (int *)mlx_get_data_addr(el->img, &el->bpp,
				&el->lz, &el->endian);
		if (el->img_data)
			error = 0;
	}
	return (error);
}

int	init_scene(t_scene *el, int argc, char **argv)
{
	int	error;

	sub_init(el);
	error = parse_arg(el, argc, argv);
	if (!error)
		error = parse_rt(el, argv[1]);
	if (!error)
		error = set_mlx(el);
	if (!error && el->set_txt)
		error = set_texture(el);
	return (error);
}
