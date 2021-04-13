/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithreading.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclerac <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 09:12:06 by aclerac           #+#    #+#             */
/*   Updated: 2021/04/12 07:48:41 by aclerac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray_tracer.h"

static	void clear_screen(void)
{
	printf("\033[H\033[J");
}

void	setup_multithreading(t_scene daddy, t_scene *childs)
{
	short	i;
	double	step;
	double	last;

	last = 0;
	step = daddy.h / NB_THREADS;
	i = -1;
	while (++i < NB_THREADS)
	{
		childs[i] = daddy;
		childs[i].threadid = i;
		childs[i].stopp_index = floor(step * (i + 1));
		childs[i].start_index = last;
		last = ceil(childs[i].stopp_index);
	}
}

void	lunch_multithreading(t_scene *childs)
{
	pthread_t	threads[NB_THREADS];
	int			i;

	i = -1;
	while (++i < NB_THREADS)
		pthread_create(&threads[i], NULL, ray_tracer, &childs[i]);
	setvbuf(stdout, NULL, _IOLBF, 0);
	clear_screen();
	i = -1;
	while (++i < NB_THREADS)
		pthread_join(threads[i], NULL);
}
