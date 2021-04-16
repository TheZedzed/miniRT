#include "minirt.h"

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

int	camera_rotation(int direction, t_scene *el)
{
	double	x;
	double	y;
	double	step;
	int		useless;

	step = 0.1;
	useless = 0;
	x = el->cam_current->axe.x;
	y = el->cam_current->axe.y;
	if (direction == CRGT || direction == CTOP)
		step = -0.1;
	if (fabs(x + step) > 1 || fabs(y + step) > 1)
		useless = 1;
	if (!useless)
	{
		if (direction == CLFT || direction == CRGT)
			el->cam_current->axe.x += step;
		else
			el->cam_current->axe.y += step;
	}
	return (useless);
}

int	action_key(int keynote, t_scene *el)
{
	int	useless;

	useless = 1;
	if (keynote == ESC)
		free_all(el);
	else if (keynote == RIGHT || keynote == LEFT)
		useless = change_camera(keynote, el);
	else if (keynote == CLFT || keynote == CRGT
		|| keynote == CTOP || keynote == CBOT)
		useless = camera_rotation(keynote, el);
	if (!useless)
		draw(el);
	return (0);
}

int	get_obj(int button, int x, int y, t_scene *el)
{
	t_inter			ray;
	char			*pos;
	unsigned int	color;

	color = 0x00ffffff;
	ray_at(&ray, el, y, x);
	if (button && intersection(&ray, el))
	{
		pos = ft_itoa((int)ray.obj.pos.x);
		mlx_string_put(el->mlx, el->win, x, y + 00, color, pos);
		free(pos);
		pos = ft_itoa((int)ray.obj.pos.y);
		mlx_string_put(el->mlx, el->win, x, y + 10, color, pos);
		free(pos);
		pos = ft_itoa((int)ray.obj.pos.z);
		mlx_string_put(el->mlx, el->win, x, y + 20, color, pos);
		free(pos);
	}
	return (0);
}
