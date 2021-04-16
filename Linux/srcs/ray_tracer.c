#include "minirt.h" 

int	final_color(double *c, t_scene *el)
{
	int		final;
	double	tmp[6];

	tmp[0] = el->gamma;
	tmp[1] = el->aliasing;
	tmp[2] = el->amb.ratio;
	tmp[3] = el->amb.intensity.x;
	tmp[4] = el->amb.intensity.y;
	tmp[5] = el->amb.intensity.z;
	c[0] = fmin((tmp[2] * tmp[3] + ((c[0] * 255 / tmp[1])) * tmp[0]), 255);
	c[1] = fmin((tmp[2] * tmp[4] + ((c[1] * 255 / tmp[1])) * tmp[0]), 255);
	c[2] = fmin((tmp[2] * tmp[5] + ((c[2] * 255 / tmp[1])) * tmp[0]), 255);
	if (el->sepia)
		calc_sepia(c);
	final = ((int)c[0] << 16) | ((int)c[1] << 8) | (int)c[2];
	return (final);
}

void	refracted_out(t_scene *el, t_inter *ray, double ratio, double *param)
{
	t_vect	tmp[3];

	param[0] = ratio;
	intersection(ray, el);
	ray->normal = scalar(-1, &ray->normal);
	param[1] = -dot(&ray->normal, &ray->ray.dir);
	param[2] = param[0] * param[0] * (1 - param[1] * param[1]);
	if (param[2] <= 1)
	{
		tmp[0] = scalar(10e-4, &ray->normal);
		ray->point = add(&ray->point, &tmp[0]);
		ray->ray.org = ray->point;
		param[3] = sqrt(1 - param[2]);
		tmp[2] = scalar(param[0], &ray->ray.dir);
		tmp[1] = scalar(-1 * (param[0] * param[1] - param[3]), &ray->normal);
		ray->ray.dir = add(&tmp[2], &tmp[1]);
	}
}

void	refracted_ray(t_scene *el, t_inter *ray, double n1, double n2)
{
	double	param[4];
	t_vect	tmp[3];

	param[0] = n1 / n2;
	param[1] = -dot(&ray->normal, &ray->ray.dir);
	param[2] = param[0] * param[0] * (1 - param[1] * param[1]);
	if (param[2] <= 1)
	{
		param[3] = sqrt(1 - param[2]);
		tmp[0] = scalar(10e-8, &ray->normal);
		ray->point = add(&ray->point, &tmp[0]);
		ray->ray.org = ray->point;
		tmp[1] = scalar(param[0], &ray->ray.dir);
		tmp[2] = scalar(param[0] * param[1] - param[3], &ray->normal);
		ray->ray.dir = add(&tmp[1], &tmp[2]);
		refracted_out(el, ray, n2 / n1, param);
	}
}

void	recursive(t_scene *el, t_inter *ray, double *param, double *color)
{
	double	indice;

	if (intersection(ray, el))
	{
		indice = ray->obj.prop.refraction;
		if (el->set_txt && ray->obj.type == SPHERE)
			*color = text_color(el, ray);
		else
		{
			if (el->do_refract && ray->obj.type == SPHERE && indice > 1)
				refracted_ray(el, ray, 1, indice);
			get_reflect(el, ray, param, color);
		}
	}
}

void	get_color(t_scene *el, t_inter *ray, int *param, double *color)
{
	double	coef[2];

	coef[0] = 1;
	color[0] = 0;
	color[1] = 0;
	color[2] = 0;
	coef[1] = el->reflect_depth;
	ray_at(ray, el, param[0], param[1]);
	recursive(el, ray, coef, color);
}
