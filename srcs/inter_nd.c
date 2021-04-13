/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclerac <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 13:48:14 by aclerac           #+#    #+#             */
/*   Updated: 2021/04/12 10:01:10 by aclerac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray_tracer.h"

t_vect	norm_cylinder(t_inter *inter, t_obj *obj)
{
	t_vect	normal;
	t_vect	tmp;
	t_vect	foo;

	foo = scalar(1.0001, &inter->point);
	if (inter->point.y == obj->pos.y + obj->height)
		normal = obj->normal;
	else if (inter->point.y == obj->pos.y)
		normal = scalar(-1, &obj->normal);
	else
	{
		if (obj->normal.x)
			tmp = add(&obj->pos, &((t_vect){obj->height / 2, 0, 0}));
		else if (obj->normal.y)
			tmp = add(&obj->pos, &((t_vect){0, obj->height / 2, 0}));
		else if (obj->normal.z)
			tmp = add(&obj->pos, &((t_vect){0, 0, obj->height / 2}));
		normal = sub(&foo, &tmp);
		if (obj->normal.x)
			normal = sub(&normal, &((t_vect){normal.x, 0, 0}));
		else if (obj->normal.y)
			normal = sub(&normal, &((t_vect){0, normal.y, 0}));
		else if (obj->normal.z)
			normal = sub(&normal, &((t_vect){0, 0, normal.z}));
	}
	return (normal);
}

t_vect	normalize_obj(t_inter *inter, t_obj *obj)
{
	t_vect	normal;

	if (obj->type == SPHERE)
		normal = sub(&inter->point, &obj->pos);
	else if (obj->type == CYLINDER)
		normal = norm_cylinder(inter, obj);
	else
		normal = obj->normal;
	if (dot(&inter->ray.dir, &normal) > 0)
		normal = scalar(-1, &normal);
	normalize(&normal);
	return (normal);
}

int	intersection(t_inter *inter, t_scene *env)
{
	t_vect		scaled;
	double		t_loc;
	t_obj		*current;

	inter->t = INFINITY;
	current = env->obj_head;
	while (current)
	{
		t_loc = (current->intersection)(&inter->ray, current);
		if (t_loc > 0 && t_loc < inter->t)
		{
			inter->t = t_loc;
			inter->obj = *current;
		}
		current = current->next;
	}
	if (inter->t != INFINITY)
	{
		scaled = scalar(inter->t, &inter->ray.dir);
		inter->point = add(&inter->ray.org, &scaled);
		inter->normal = normalize_obj(inter, &inter->obj);
		return (1);
	}
	return (0);
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
