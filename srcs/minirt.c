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

static int	camera_rotation(int direction, t_scene *el)
{
	double	x;
	double	y;
	double	step;
	int	useless;

	step = 0.1;
	useless = 0;
	x = el->cam_current->axe.x;
	y = el->cam_current->axe.y;
	if (direction == CRGT || direction == CBOT)
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

static int	action_key(int keynote, t_scene *el)
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

static int	get_obj(int button, int x, int y, t_scene *el)
{
	t_inter		ray;
	char		*pos;
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

void		sub_init(t_scene *env)
{
	env->save = 0;
	env->gamma = 1 / 2.2;
	env->set_text = 0;
	env->antialiasing = 1;
	env->mlx = NULL;
	env->win = NULL;
	env->img = NULL;
	env->img_data = NULL;
	env->cam_head = NULL;
	env->cam_tail = NULL;
	env->obj_head = NULL;
	env->obj_tail = NULL;
	env->lum_head = NULL;
	env->lum_tail = NULL;
}

int		print_error(t_scene *env, int err)
{
	if (err == -5)
		write(2, ERR_M5, ft_strlen(ERR_M5));
	else if (err == -4)
		write(2, ERR_M4, ft_strlen(ERR_M4));
	else if (err == -3)
		write(2, ERR_M3, ft_strlen(ERR_M3));
	else if (err == -2)
		write(2, ERR_M2, ft_strlen(ERR_M2));
	else if (err == -1)
		write(2, ERR_M1, ft_strlen(ERR_M1));
	else if (err == 1)
		write(2, ERR_1, ft_strlen(ERR_1));
	else if (err == 2)
		write(2, ERR_2, ft_strlen(ERR_2));
	else if (err == 3)
		write(2, ERR_3, ft_strlen(ERR_3));
	else if (err == 4)
		write(2, ERR_4, ft_strlen(ERR_4));
	else if (err == 5)
		write(2, ERR_5, ft_strlen(ERR_5));
	else if (err == 6)
		write(2, ERR_6, ft_strlen(ERR_6));
	else if (err == 7)
		write(2, ERR_7, ft_strlen(ERR_7));
	else if (err == 8)
		write(2, ERR_8, ft_strlen(ERR_8));
	else if (err == 9)
		write(2, ERR_9, ft_strlen(ERR_9));
	else if (err == 10)
		write(2, ERR_10, ft_strlen(ERR_10));
	else if (err == 11)
		write(2, ERR_11, ft_strlen(ERR_11));
	else if (err == 12)
		write(2, ERR_12, ft_strlen(ERR_12));
	else if (err == 13)
		write(2, ERR_13, ft_strlen(ERR_13));
	else if (err == 14)
		write(2, ERR_14, ft_strlen(ERR_14));
	else if (err == 15)
		write(2, ERR_15, ft_strlen(ERR_15));
	else if (err == 16)
		write(2, ERR_16, ft_strlen(ERR_16));
	else if (err == 17)
		write(2, ERR_17, ft_strlen(ERR_17));
	else if (err == 18)
		write(2, ERR_18, ft_strlen(ERR_18));
	else if (err == 19)
		write(2, ERR_19, ft_strlen(ERR_19));
	else if (err == 20)
		write(2, ERR_20, ft_strlen(ERR_20));
	else if (err == 21)
		write(2, ERR_21, ft_strlen(ERR_21));
	else if (err == 22)
		write(2, ERR_22, ft_strlen(ERR_22));
	else if (err == 23)
		write(2, ERR_23, ft_strlen(ERR_23));
	else if (err == 24)
		write(2, ERR_24, ft_strlen(ERR_24));
	else if (err == 25)
		write(2, ERR_25, ft_strlen(ERR_25));
	else if (err == 26)
		write(2, ERR_26, ft_strlen(ERR_26));
	else if (err == 27)
		write(2, ERR_27, ft_strlen(ERR_27));
	else if (err == 28)
		write(2, ERR_28, ft_strlen(ERR_28));
	else if (err == 29)
		write(2, ERR_29, ft_strlen(ERR_29));
	else if (err == 30)
		write(2, ERR_30, ft_strlen(ERR_30));
	else if (err == 31)
		write(2, ERR_31, ft_strlen(ERR_31));
	else if (err == 32)
		write(2, ERR_32, ft_strlen(ERR_32));
	else if (err == 33)
		write(2, ERR_33, ft_strlen(ERR_33));
	else if (err == 34)
		write(2, ERR_34, ft_strlen(ERR_34));
	else if (err == 35)
		write(2, ERR_35, ft_strlen(ERR_35));
	else if (err == 36)
		write(2, ERR_36, ft_strlen(ERR_36));
	else if (err == 37)
		write(2, ERR_37, ft_strlen(ERR_37));
	else if (err == 38)
		write(2, ERR_38, ft_strlen(ERR_38));
	else if (err == 39)
		write(2, ERR_39, ft_strlen(ERR_39));
	else if (err == 40)
		write(2, ERR_40, ft_strlen(ERR_40));
	else if (err == 41)
		write(2, ERR_41, ft_strlen(ERR_41));
	else if (err == 42)
		write(2, ERR_42, ft_strlen(ERR_42));
	else if (err == 43)
		write(2, ERR_43, ft_strlen(ERR_43));
	else if (err == 44)
		write(2, ERR_44, ft_strlen(ERR_44));
	else if (err == 45)
		write(2, ERR_45, ft_strlen(ERR_45));
	else if (err == 46)
		write(2, ERR_46, ft_strlen(ERR_46));
	else if (err == 47)
		write(2, ERR_47, ft_strlen(ERR_47));
	else if (err == 48)
		write(2, ERR_48, ft_strlen(ERR_48));
	else if (err == 49)
		write(2, ERR_49, ft_strlen(ERR_49));
	else if (err == 50)
		write(2, ERR_50, ft_strlen(ERR_50));
	else if (err == 51)
		write(2, ERR_51, ft_strlen(ERR_51));
	else if (err == 52)
		write(2, ERR_52, ft_strlen(ERR_52));
	else if (err == 53)
		write(2, ERR_53, ft_strlen(ERR_53));
	return (free_all(env));
}

int		parse_arg(t_scene *env, int ac, char **av)
{
	int	error;

	error = 1;
	if (ac == 2 || ac == 3)
	{
		error = 0;
		if (ac == 3)
		{
			if (!ft_strncmp(av[2], "--save", 6))
				env->save = 1;
			else
				error = 1;
		}
	}
	return (error);
}

int		set_mlx(t_scene *el)
{
	int	x;
	int	y;
	int	z;
	int	error;

	error = 2;
	el->title = "miniRT";
	el->cam_current = el->cam_head;
	init_base(&el->base, &el->cam_current->axe);
	el->mlx = mlx_init();
	if (el->mlx)
		el->win = mlx_new_window(el->mlx, el->w, el->h, el->title);
	if (el->win)
		el->img = mlx_new_image(el->mlx, el->w, el->h);
	if (el->img)
		el->img_data = (int *)mlx_get_data_addr(el->img, &x, &y, &z);
	if (el->img_data)
		error = 0;
	return (error);
}

static int	init_scene(t_scene *el, int argc, char **argv)
{
	int	error;

	sub_init(el);
	error = parse_arg(el, argc, argv);
	if (!error)
		error = parse_rt(el, argv[1]);
	if (!error)
		error = set_mlx(el);
	if (!error)
		error = set_texture(el);
	return (error);
}

int	main(int ac, char **av)
{
	t_scene		el;
	int		error;

	error = init_scene(&el, ac, av);
	if (!error)
	{
		srand(time(NULL));
		mlx_hook(el.win, 2, (1L << 0), action_key, &el);
		mlx_hook(el.win, EVNT, MASK, free_all, &el);
		mlx_mouse_hook(el.win, get_obj, &el);
		mlx_hook(el.win, 12, (1L << 15), draw, &el);
		mlx_loop(el.mlx);
	}
	return (print_error(&el, error));
}
