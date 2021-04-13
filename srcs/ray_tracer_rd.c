/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclerac <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 09:13:45 by aclerac           #+#    #+#             */
/*   Updated: 2021/04/12 08:24:06 by aclerac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h" 
#include "inter.h"
#include "ray_tracer.h"

void	lambert_color(double lambert, t_inter *ray, t_light *light, double *color)
{
	color[0] += lambert * light->intensity.x * ray->obj.prop.diffuse.x;
	color[1] += lambert * light->intensity.y * ray->obj.prop.diffuse.y;
	color[2] += lambert * light->intensity.z * ray->obj.prop.diffuse.z;
}

void	reflected_ray(t_inter *ray)
{
	t_vect	tmp;
	double	reflect;

	reflect = 2 * dot(&ray->ray.dir, &ray->normal);
	vector(&ray->ray.org, ray->point.x, ray->point.y, ray->point.z);
	tmp = scalar(reflect, &ray->normal);
	ray->ray.dir = sub(&ray->ray.dir, &tmp);
}

int		in_shadow(t_scene *env, t_inter *ray, t_inter *shadow_ray, t_light *light)
{
	t_vect	tmp;
 	t_vect	shadow;

	shadow = sub(&light->pos, &ray->point);
	if (norm2(&shadow))
	{
		tmp = scalar(10e-8, &ray->normal);
		ray->point = add(&tmp, &ray->point);
		Ray(&shadow_ray->ray, &ray->point, &shadow);
		return (intersection(shadow_ray, env) && (shadow_ray->t * shadow_ray->t) < norm2(&shadow));
	}
	return (1);
}

void	get_reflect(t_scene *env, t_inter *ray, double *param, double *color)
{
	t_inter	shadow_ray;
	t_light *current;
	double	lambert;

	current = env->lum_head;
	if (intersection(ray, env))
	{
		//printf("\n%f, %f, %f\n", ray->obj.prop.diffuse.x, ray->obj.prop.diffuse.y, ray->obj.prop.diffuse.z);
		while (current)
 		{
 			if (!in_shadow(env, ray, &shadow_ray, current))
			{
				lambert = dot(&shadow_ray.ray.dir, &ray->normal) * param[0];
				lambert_color(lambert, ray, current, color);
			}
			current = current->next;
		}
		reflected_ray(ray);
		param[0] *= ray->obj.prop.reflection;
		if (param[0] > 0.0 && --param[1] > 0.0)
			get_reflect(env, ray, param, color);
	}
}

void	calc_sepia(double *color)
{
	double	tmp[3];

	tmp[0] = color[0] * 0.393 + color[1] * 0.769 + color[2] * 0.189; 
	tmp[1] = color[0] * 0.349 + color[1] * 0.686 + color[2] * 0.168; 
	tmp[2] = color[0] * 0.272 + color[1] * 0.534 + color[2] * 0.131;
	color[0] = MIN(255, tmp[0]);
	color[1] = MIN(255, tmp[1]);
	color[2] = MIN(255, tmp[2]);
}
