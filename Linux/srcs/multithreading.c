#include "minirt.h"

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
		childs[i].tid = i;
		childs[i].stop = floor(step * (i + 1));
		childs[i].start = last;
		last = ceil(childs[i].stop);
	}
}

void	lunch_multithreading(t_scene *childs)
{
	pthread_t	threads[NB_THREADS];
	int			i;

	i = -1;
	while (++i < NB_THREADS)
		pthread_create(&threads[i], NULL, ray_tracer, &childs[i]);
	i = -1;
	while (++i < NB_THREADS)
		pthread_join(threads[i], NULL);
}
