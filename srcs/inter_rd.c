/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclerac <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 13:48:14 by aclerac           #+#    #+#             */
/*   Updated: 2021/04/12 09:22:44 by aclerac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inter.h"
#include "minirt.h"
#include "ray_tracer.h"

double	poly_cone(double poly[4], double proj_ze, double proj_zd, t_obj *co)
{
	double	t0;
	double	t1;
	double	z1;
	double	z2;

	poly[3] = sqrt(poly[3]);
	t0 = (-poly[1] + poly[3]) / (2 * poly[0]);
	t1 = (-poly[1] - poly[3]) / (2 * poly[0]);
	if (t0 > 0)
	{
		z1 = proj_ze + t0 * proj_zd;
		z2 = proj_ze + t1 * proj_zd;
		if (fabs(z2) <= co->height)
			return (t1);
		if (fabs(z1) <= co->height)
			return (t0);
	}
	return (-1);
}

double	inter_ray_cone(t_ray *ray, t_obj *co)
{
	t_base	co_base;
	t_vect	point;
	double	p[6];
	double	poly[4];
	double	det;

	init_base(&co_base, &co->normal);
	point = sub(&ray->org, &co->pos);
	p[0] = dot(&point, &co_base.x_axis);
	p[1] = dot(&point, &co_base.y_axis);
	p[2] = dot(&point, &co_base.z_axis);
	p[3] = dot(&ray->dir, &co_base.x_axis);
	p[4] = dot(&ray->dir, &co_base.y_axis);
	p[5] = dot(&ray->dir, &co_base.z_axis);
	poly[0] = (co->radius * co->radius) / (co->height * co->height);
	poly[1] = (p[3] * p[3]) + (p[4] * p[4]) - (poly[0] * p[5] * p[5]);
	poly[2] = 2 * (p[0] * p[3] + p[1] * p[4] - (poly[0] * p[2] * p[5]));
	poly[3] = (p[0] * p[0]) + (p[1] * p[1]) - (poly[0] * p[2] * p[2]);
	det = poly[2] * poly[2] - 4 * poly[1] * poly[3];
	if (det >= 0)
		return (poly_cone((double [4]){poly[1], poly[2], poly[3], det},
			p[2], p[5], co));
	return (-1);
}

double	poly_cylinder(double poly[4], double proj_ze, double proj_zd, t_obj *cy)
{
	double	t0;
	double	t1;
	double	z1;
	double	z2;

	poly[3] = sqrt(poly[3]);
	t0 = (-poly[1] + poly[3]) / (2 * poly[0]);
	t1 = (-poly[1] - poly[3]) / (2 * poly[0]);
	if (t0 > 0)
	{
		z1 = proj_ze + t0 * proj_zd;
		z2 = proj_ze + t1 * proj_zd;
		if (z2 >= 0 && z2 <= cy->height)
			return (t1);
		if (z1 >= 0 && z1 <= cy->height)
			return (t0);
	}
	return (-1);
}

double	inter_ray_cylinder(t_ray *ray, t_obj *cy)
{
	t_base	cy_base;
	t_vect	point;
	double	proj[6];
	double	poly[3];
	double	det;

	init_base(&cy_base, &cy->normal);
	point = sub(&ray->org, &cy->pos);
	proj[0] = dot(&point, &cy_base.x_axis);
	proj[1] = dot(&point, &cy_base.y_axis);
	proj[2] = dot(&point, &cy_base.z_axis);
	proj[3] = dot(&ray->dir, &cy_base.x_axis);
	proj[4] = dot(&ray->dir, &cy_base.y_axis);
	proj[5] = dot(&ray->dir, &cy_base.z_axis);
	poly[0] = (proj[3] * proj[3]) + (proj[4] * proj[4]);
	poly[1] = 2 * (proj[0] * proj[3] + proj[1] * proj[4]);
	poly[2] = (proj[0] * proj[0]) + (proj[1] * proj[1])
		- pow(cy->diameter / 2, 2);
	det = poly[1] * poly[1] - 4 * poly[0] * poly[2];
	if (det >= 0)
		return (poly_cylinder((double [4]){poly[0], poly[1], poly[2], det},
			proj[2], proj[5], cy));
	return (-1);
}
