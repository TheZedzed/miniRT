#include "minirt.h" 

void	lambert_color(double lambert, t_inter *ray, t_light *lum, double *col)
{
	double	tmp[4];

	tmp[0] = lum->intensity.x;
	tmp[1] = lum->intensity.y;
	tmp[2] = lum->intensity.z;
	tmp[3] = lum->ratio;
	col[0] += lambert * tmp[0] * tmp[3] * ray->obj.prop.diffuse.x;
	col[1] += lambert * tmp[1] * tmp[3] * ray->obj.prop.diffuse.y;
	col[2] += lambert * tmp[2] * tmp[3] * ray->obj.prop.diffuse.z;
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

int	in_shadow(t_scene *el, t_inter *ray, t_inter *shadow_ray, t_light *lum)
{
	t_vect	tmp;
	t_vect	shadow;

	shadow = sub(&lum->pos, &ray->point);
	if (norm2(&shadow))
	{
		tmp = scalar(10e-8, &ray->normal);
		ray->point = add(&tmp, &ray->point);
		Ray(&shadow_ray->ray, &ray->point, &shadow);
		return (intersection(shadow_ray, el)
			&& (shadow_ray->t * shadow_ray->t) < norm2(&shadow));
	}
	return (1);
}

void	get_reflect(t_scene *env, t_inter *ray, double *param, double *color)
{
	t_inter	shadow_ray;
	t_light	*current;
	double	lambert;

	current = env->lum_head;
	if (intersection(ray, env))
	{
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
		if (param[0] > 0 && --param[1] > 0)
			get_reflect(env, ray, param, color);
	}
}

void	calc_sepia(double *color)
{
	color[0] = color[0] * 0.393 + color[1] * 0.769 + color[2] * 0.189;
	color[1] = color[0] * 0.349 + color[1] * 0.686 + color[2] * 0.168;
	color[2] = color[0] * 0.272 + color[1] * 0.534 + color[2] * 0.131;
	color[0] = fmin(255, color[0]);
	color[1] = fmin(255, color[1]);
	color[2] = fmin(255, color[2]);
}
