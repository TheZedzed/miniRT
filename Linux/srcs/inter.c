#include "minirt.h"

int	intersection(t_inter *inter, t_scene *el)
{
	t_vect		scaled;
	double		t_loc;
	t_obj		*current;

	inter->t = INFINITY;
	current = el->obj_head;
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

t_vect	normalize_obj(t_inter *inter, t_obj *obj)
{
	t_vect	normal;

	if (obj->type == SPHERE)
		normal = sub(&inter->point, &obj->pos);
	else if (obj->type == CYLINDER)
		normal = normal_cylinder(inter, obj);
	else if (obj->type == CONE)
		normal = normal_cone(inter, obj);
	else
		normal = obj->normal;
	if (dot(&inter->ray.dir, &normal) > 0)
		normal = scalar(-1, &normal);
	normalize(&normal);
	return (normal);
}

t_vect	normal_cylinder(t_inter *inter, t_obj *cy)
{
	t_vect	tmp;
	double	cos;

	tmp = sub(&inter->point, &cy->pos);
	cos = dot(&tmp, &cy->normal);
	tmp = scalar(cos, &cy->normal);
	tmp = add(&tmp, &cy->pos);
	return (sub(&inter->point, &tmp));
}

t_vect	normal_cone(t_inter *ray, t_obj *co)
{
	t_vect	tmp[3];
	double	cos;

	tmp[0] = sub(&ray->ray.dir, &co->pos);
	cos = ray->t * dot(&ray->ray.dir, &co->normal) * dot(&tmp[0], &co->normal);
	tmp[1] = sub(&ray->point, &co->pos);
	tmp[2] = scalar((1 + pow(tan(co->height), 2)) * cos, &co->normal);
	return (sub(&tmp[1], &tmp[2]));
}
