/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 03:13:54 by azeraoul          #+#    #+#             */
/*   Updated: 2021/04/15 21:06:44 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	print_error(t_scene *env, int err)
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
	else
		write(2, "Parse failed\n", 13);
	return (free_all(env));
}

void	parse_bonus(t_scene *el, int ac, char **av)
{
	int	i;

	i = 1;
	while (++i < ac)
	{
		if (!ft_strcmp(av[i], "-re"))
			el->reflect_depth = 5;
		else if (!ft_strcmp(av[i], "-t"))
			el->set_txt = 1;
		else if (!ft_strcmp(av[i], "-ra"))
			el->do_refract = 1;
		else if (!ft_strcmp(av[i], "-g"))
			el->gamma = 1 / 2.2;
		else if (!ft_strcmp(av[i], "-a"))
			el->aliasing = 10;
		else if (!ft_strcmp(av[i], "-f"))
			el->sepia = 1;
	}
}

int	parse_arg(t_scene *el, int ac, char **av)
{
	int	error;

	error = 0;
	if (ac < 2)
		error = 1;
	else if (ac >= 2)
	{
		if (ac == 3)
		{
			if (!ft_strcmp(av[2], "--save"))
				el->save = 1;
			else
				error = 1;
		}
		else
			parse_bonus(el, ac, av);
	}
	return (error);
}

void 	*ray_tracer(void *param)
{
	double	color[3];
	int		toz[3];
	t_inter	primary_ray;
	t_scene	*el;

	el = (t_scene *)param;
	toz[0] = el->start - 1;
	while (++toz[0] < el->stop)
	{
		toz[1] = -1;
		while (++toz[1] < el->w)
		{
			toz[2] = -1;
			while (++toz[2] < el->aliasing)
				get_color(el, &primary_ray, toz, color);
			el->img_data[(int)el->w * toz[0] + toz[1]]
				= final_color(color, el);
			printf("\033[%d;%dHT[%03d] : [%3.f%%]", el->tid + 1, 0, el->tid,
				((toz[0] - el->start) / (double)(el->stop - el->start)) * 100);
		}
	}
	printf("\033[H\033[J");
	return (NULL);
}

int	main(int ac, char **av)
{
	t_scene	el;
	int		error;

	error = init_scene(&el, ac, av);
	if (!error)
	{
		srand(time(NULL));
		if (!el.save)
		{
			mlx_hook(el.win, 2, (1L << 0), action_key, &el);
			mlx_hook(el.win, EVNT, MASK, free_all, &el);
			mlx_hook(el.win, 4, (1L << 2), get_obj, &el);
			mlx_hook(el.win, 12, (1L << 15), draw, &el);
			mlx_loop(el.mlx);
		}
		draw(&el);
	}
	return (print_error(&el, error));
}
