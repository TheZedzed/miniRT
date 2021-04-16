#include "minirt.h"

int	scene_add_sphere(t_scene *el, double radius, t_vect pos, t_prop prop)
{
	t_obj	*new_node;

	new_node = malloc(sizeof(t_obj));
	if (new_node == NULL)
		return (-4);
	new_node->intersection = &inter_ray_sphere;
	new_node->type = SPHERE;
	new_node->pos = pos;
	new_node->prop = prop;
	new_node->radius = radius;
	update_scene_obj(el, new_node);
	return (0);
}

int	scene_add_square(t_scene *el, t_mikmak m, t_prop prop)
{
	t_obj	*new_node;

	new_node = malloc(sizeof(t_obj));
	if (new_node == NULL)
		return (-4);
	new_node->intersection = &inter_ray_square;
	new_node->type = SQUARE;
	new_node->normal = m.nor;
	new_node->pos = m.pos;
	new_node->prop = prop;
	new_node->size = m.d1;
	update_scene_obj(el, new_node);
	return (0);
}

int	scene_add_triangle(t_scene *el, t_mikmak m, t_vect c, t_prop prop)
{
	t_obj	*new_node;
	t_vect	ab;
	t_vect	ac;

	new_node = malloc(sizeof(t_obj));
	if (new_node == NULL)
		return (-4);
	new_node->intersection = &inter_ray_triangle;
	new_node->type = TRIANGLE;
	new_node->prop = prop;
	new_node->a = m.pos;
	new_node->b = m.nor;
	new_node->c = c;
	ab = sub(&new_node->b, &new_node->a);
	ac = sub(&new_node->c, &new_node->a);
	new_node->normal = cross(&ab, &ac);
	update_scene_obj(el, new_node);
	return (0);
}

int	scene_add_plane(t_scene *el, t_vect normal, t_vect pos, t_prop prop)
{
	t_obj	*new_node;

	new_node = malloc(sizeof(t_obj));
	if (new_node == NULL)
		return (-4);
	new_node->intersection = &inter_ray_plane;
	new_node->type = PLAN;
	new_node->pos = pos;
	new_node->prop = prop;
	new_node->normal = normal;
	update_scene_obj(el, new_node);
	return (0);
}

int	scene_add_circle(t_scene *el, t_mikmak m, t_prop prop)
{
	t_obj	*new_node;

	new_node = malloc(sizeof(t_obj));
	if (new_node == NULL)
		return (-4);
	new_node->intersection = &inter_ray_circle;
	new_node->type = CIRCLE;
	new_node->pos = m.pos;
	new_node->radius = m.d1;
	new_node->prop = prop;
	new_node->normal = m.nor;
	update_scene_obj(el, new_node);
	return (0);
}
