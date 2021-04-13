/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclerac <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 09:13:45 by aclerac           #+#    #+#             */
/*   Updated: 2021/04/12 08:20:58 by aclerac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h" 
#include "inter.h"
#include "ray_tracer.h"


unsigned int	text_color(t_scene *el, t_inter *inter)
{
	t_vect vp = sub(&inter->obj.pos, &inter->point);
	normalize(&vp);
	double phi = acos(-dot(&((t_vect){0, 1, 0}), &vp));
	double u;
	double v = phi / M_PI;
	double theta = (acos(dot(&vp, &((t_vect){1, 0, 0})) / sin(phi))) / (2 * M_PI);
	t_vect tmp;
	tmp = cross(&((t_vect){0, 1, 0}), &((t_vect){1, 0, 0}));
	if (dot(&tmp, &vp) > 0)
		u = theta;
	else 
		u = 1 - theta;
	int x = (int)(u * el->txt.w) * (el->txt.bpp / 8);
	int y = (int)(v * el->txt.h) * el->txt.lz;
	return ((unsigned int)el->txt.data[x + y]);
}

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

	tmp.x = ray->x * base->x_axis.x + ray->y * base->y_axis.x + ray->z *
		base->z_axis.x;
	tmp.y = ray->x * base->x_axis.y + ray->y * base->y_axis.y + ray->z *
		base->z_axis.y;
	tmp.z = ray->x * base->x_axis.z + ray->y * base->y_axis.z + ray->z *
		base->z_axis.z;
	*ray = tmp;
	normalize(ray);
}

void	ray_at(t_inter *inter, t_scene *el, int i, int j)
{
	double	ratio;
	double	fov;
	double	h;
	double	w;
	double	r0;
	double	r1;
	double	r2;
	double	dx;
	double	dy;

	h = el->h;
	w = el->w;
	ratio = w / h;
	fov = tan(el->cam_current->fov * (M_PI / (180 * 2)));
	if (el->antialiasing > 1)
	{
		r1 = (double)rand() / RAND_MAX;
		r2 = (double)rand() / RAND_MAX;
		r0 = sqrt(-2 * log(r1));
		dx = r0 * cos(2 * M_PI * r2);
		dy = r0 * sin(2 * M_PI * r2);
	}
	else
	{
		dx = 0;
		dy = 0;
	}
	inter->ray.dir.x = (2 * ((double)(j + 0.5 + dx) / w) - 1) * ratio * fov;
	inter->ray.dir.y = (1 - 2 * ((double)(i + 0.5 + dy) / h)) * fov;
	inter->ray.dir.z = -1;
	normalize(&inter->ray.dir);
	rotate(&inter->ray.dir, &el->base);
	vector(&inter->ray.org, el->cam_current->pos.x, el->cam_current->pos.y, el->cam_current->pos.z);// have to recode a func?
}

void	Ray(t_ray *ray, t_vect *org, t_vect *dir)
{
	vector(&ray->org, org->x, org->y, org->z);
	vector(&ray->dir, dir->x, dir->y, dir->z);
	normalize(&ray->dir);
}
