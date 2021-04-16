#include "minirt.h"

double	inter_ray_square(t_ray *ray, t_obj *sq)
{
	double	t0;
	double	proj[2];
	t_vect	v[2];
	t_vect	tmp;
	t_base	sq_base;

	init_base(&sq_base, &sq->normal);
	t0 = inter_ray_plane(ray, sq);
	if (t0 > 0)
	{
		v[0] = scalar(t0, &ray->dir);
		v[1] = add(&ray->org, &v[0]);
		tmp = sub(&v[1], &sq->pos);
		proj[0] = dot(&tmp, &sq_base.x_axis);
		proj[1] = dot(&tmp, &sq_base.y_axis);
		if (fabs(proj[0]) <= sq->size && fabs(proj[1]) <= sq->size)
			return (t0);
	}
	return (-1);
}

double	inter_ray_triangle(t_ray *ray, t_obj *tr)
{
	double	t0;
	double	c[3];
	t_vect	p[11];

	t0 = inter_ray_plane(ray, tr);
	if (t0 > 0)
	{
		p[0] = scalar(t0, &ray->dir);
		p[1] = add(&ray->org, &p[0]);
		p[2] = sub(&tr->b, &tr->a);
		p[3] = sub(&p[1], &tr->a);
		p[4] = sub(&tr->c, &tr->b);
		p[5] = sub(&p[1], &tr->b);
		p[6] = sub(&tr->a, &tr->c);
		p[7] = sub(&p[1], &tr->c);
		p[8] = cross(&p[2], &p[3]);
		p[9] = cross(&p[4], &p[5]);
		p[10] = cross(&p[6], &p[7]);
		c[0] = dot(&p[8], &tr->normal);
		c[1] = dot(&p[9], &tr->normal);
		c[2] = dot(&p[10], &tr->normal);
		if (c[0] >= 0 && c[1] >= 0 && c[2] >= 0)
			return (t0);
	}
	return (-1);
}

double	inter_ray_circle(t_ray *ray, t_obj *ci)
{
	double	t[3];
	t_vect	dist;
	t_vect	point;
	t_vect	tmp;
	t_base	ci_base;

	init_base(&ci_base, &ci->normal);
	t[0] = inter_ray_plane(ray, ci);
	if (t[0] > 0)
	{
		dist = scalar(t[0], &ray->dir);
		point = add(&ray->org, &dist);
		tmp = sub(&point, &ci->pos);
		t[1] = dot(&tmp, &ci_base.x_axis);
		t[2] = dot(&tmp, &ci_base.y_axis);
		if ((t[1] * t[1] + t[2] * t[2]) <= (ci->radius * ci->radius))
			return (t[0]);
	}
	return (-1);
}

double	inter_ray_plane(t_ray *ray, t_obj *pl)
{
	t_vect	tmp;
	double	t0;
	double	denom;

	denom = dot(&pl->normal, &ray->dir);
	if (!denom)
		return (-1);
	tmp = sub(&pl->pos, &ray->org);
	t0 = dot(&pl->normal, &tmp) / denom;
	return (t0);
}

double	inter_ray_sphere(t_ray *ray, t_obj *sp)
{
	double	t[0];
	double	p[4];
	t_vect	tmp;

	p[0] = norm2(&ray->dir);
	tmp = sub(&ray->org, &sp->pos);
	p[1] = 2 * dot(&ray->dir, &tmp);
	p[2] = norm2(&tmp) - (sp->radius * sp->radius);
	p[3] = p[1] * p[1] - 4 * p[0] * p[2];
	if (p[3] >= 0)
	{
		p[3] = sqrt(p[3]);
		t[0] = (-p[1] + p[3]) / (2 * p[0]);
		t[1] = (-p[1] - p[3]) / (2 * p[0]);
		if (t[0] > t[1])
			t[0] = t[1];
		return (t[0]);
	}
	return (-1);
}
