#include "minirt.h"

void	init_base(t_base *base, t_vect *axe)
{
	t_vect	u;

	vector(&u, 0, 1, 0);
	vector(&base->z_axis, axe->x, axe->y, axe->z);
	if (fabs(axe->y) == 1)
		vector(&base->x_axis, 1, 0, 0);
	else
		base->x_axis = cross(&u, &base->z_axis);
	base->y_axis = cross(&base->z_axis, &base->x_axis);
	normalize(&base->x_axis);
	normalize(&base->y_axis);
	normalize(&base->z_axis);
}

void	rotate(t_vect *ray, t_base *base)
{
	t_vect	tmp;

	tmp.x = ray->x * base->x_axis.x + ray->y * base->y_axis.x + ray->z
		* base->z_axis.x;
	tmp.y = ray->x * base->x_axis.y + ray->y * base->y_axis.y + ray->z
		* base->z_axis.y;
	tmp.z = ray->x * base->x_axis.z + ray->y * base->y_axis.z + ray->z
		* base->z_axis.z;
	*ray = tmp;
	normalize(ray);
}

void	random_value(double *a, double *b)
{
	double	r1;
	double	r2;
	double	r0;

	r1 = (double)rand() / RAND_MAX;
	r2 = (double)rand() / RAND_MAX;
	r0 = sqrt(-2 * log(r1));
	*a = r0 * cos(2 * M_PI * r2);
	*b = r0 * sin(2 * M_PI * r2);
}

void	ray_at(t_inter *inter, t_scene *el, int i, int j)
{
	double	tmp[6];
	t_vect	dir;

	tmp[0] = el->h;
	tmp[1] = el->w;
	tmp[3] = tmp[1] / tmp[0];
	tmp[4] = 0;
	tmp[5] = 0;
	tmp[2] = tan(el->cam_current->fov * (M_PI / 360));
	if (el->aliasing > 1)
		random_value(&tmp[4], &tmp[5]);
	dir.x = (2 * ((double)(j + 0.5 + tmp[4]) / tmp[1]) - 1) * tmp[3] * tmp[2];
	dir.y = (1 - 2 * ((double)(i + 0.5 + tmp[5]) / tmp[0])) * tmp[2];
	dir.z = -1;
	Ray(&inter->ray, &el->cam_current->pos, &dir);
	rotate(&inter->ray.dir, &el->base);
}

void	Ray(t_ray *ray, t_vect *org, t_vect *dir)
{
	vector(&ray->org, org->x, org->y, org->z);
	vector(&ray->dir, dir->x, dir->y, dir->z);
	normalize(&ray->dir);
}
