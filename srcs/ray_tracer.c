/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclerac <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 09:13:45 by aclerac           #+#    #+#             */
/*   Updated: 2021/04/12 08:26:07 by aclerac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h" 
#include "inter.h"
#include "ray_tracer.h"

int		final_color(double *color, t_scene *el)
{
	int	aa;
	int	final;
	double	gamma;

	gamma = el->gamma;
	aa = el->antialiasing;
	color[0] = fmin((color[0] * 255.0f / aa) * gamma, 255.0f);
	color[1] = fmin((color[1] * 255.0f / aa) * gamma, 255.0f);
	color[2] = fmin((color[2] * 255.0f / aa) * gamma, 255.0f);
	if (SEPIA)
		calc_sepia(color);
	final = ((int)color[0] << 16) | ((int)color[1] << 8) | (int)color[2];
	return (final);
}

void	refracted_ray(t_scene *el, t_inter *ray, double n1, double n2)
{
	double	ratio = n1 / n2;
	double	cosI = -dot(&ray->normal, &ray->ray.dir);
	double	sinT2 = ratio * ratio * (1 - cosI * cosI);

	if (sinT2 <= 1)
	{
		double	cosT = sqrt(1 - sinT2);

		t_vect	tmp3 = scalar(10e-8, &ray->normal);
		ray->point = add(&ray->point, &tmp3);
		ray->ray.org = ray->point;

		t_vect	tp = scalar(ratio, &ray->ray.dir);
		t_vect	tmp = scalar(ratio * cosI - cosT, &ray->normal);
		ray->ray.dir = add(&tp, &tmp);

		//sortie
		ratio = n2 / n1;
		intersection(ray, el);
		ray->normal = scalar(-1, &ray->normal);
		cosI = -dot(&ray->normal, &ray->ray.dir);
		sinT2 = ratio * ratio * (1 - cosI * cosI);
		if (sinT2 <= 1)
		{
			tmp3 = scalar(10e-4, &ray->normal);
			ray->point = add(&ray->point, &tmp3);
			ray->ray.org = ray->point;
			cosT = sqrt(1 - sinT2);
			tp = scalar(ratio, &ray->ray.dir);
			tmp = scalar(-1 * (ratio * cosI - cosT), &ray->normal);
			ray->ray.dir = add(&tp, &tmp);
		}
	}
}

void	get_color(t_scene *el, t_inter *ray, double *param, double *color)
{
	double	indice;

	if (intersection(ray, el))
	{
		indice = ray->obj.prop.refraction;
		if (el->set_text && ray->obj.type == SPHERE)
			*color = text_color(el, ray);
		else 
		{
			if (ray->obj.type == SPHERE)
				if (indice > 1)
					refracted_ray(el, ray, 1, indice);
			get_reflect(el, ray, param, color);
		}
	}
}

void 	*ray_tracer(void *param)
{
	int	toz[3];
	t_inter	primary_ray;
	double	up;
	t_scene	*el;

	el = (t_scene *)param;
	toz[0] = el->start_index - 1;
	while (++toz[0] < el->stopp_index)
	{
		toz[1] = -1;
		while (++toz[1] < el->w)
		{
			double	color[3] = {0};//vector ?
			double	param[2] = {1, 5};//coef and reflect depth from parse ?

			toz[2] = -1;
			while (++toz[2] < el->antialiasing)
			{
				ray_at(&primary_ray, el, toz[0], toz[1]);
				get_color(el, &primary_ray, param, color);
			}
			el->img_data[(int)el->w * toz[0] + toz[1]] = final_color(color, el);
		}
		up = ((toz[0] - el->start_index) / (el->stopp_index - el->start_index)) * 100;
		//printf("\033[%d;%dHT[%03d] : [%3.f%%]", el->threadid + 1, 0, el->threadid, up);
	}
	return (NULL);
}
