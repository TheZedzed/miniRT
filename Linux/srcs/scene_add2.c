#include "minirt.h"

int	scene_add_lum(t_scene *el, t_vect pos, double ratio, t_vect intensity)
{
	t_light	*new_node;

	new_node = malloc(sizeof(t_light));
	if (new_node == NULL)
		return (-4);
	new_node->pos = pos;
	new_node->ratio = ratio;
	new_node->intensity = intensity;
	update_scene_lum(el, new_node);
	return (0);
}

int	scene_add_cam(t_scene *el, t_vect pos, t_vect axe, double fov)
{
	t_cam	*new_node;

	new_node = malloc(sizeof(t_cam));
	if (new_node == NULL)
		return (-4);
	new_node->pos = pos;
	new_node->axe = axe;
	new_node->fov = fov;
	update_scene_cam(el, new_node);
	return (0);
}

int	scene_add_cone(t_scene *el, t_mikmak m, t_prop prop)
{
	t_obj	*new_node;

	new_node = malloc(sizeof(t_obj));
	if (new_node == NULL)
		return (-4);
	new_node->intersection = &inter_ray_cone;
	new_node->type = CONE;
	new_node->pos = m.pos;
	new_node->height = m.d1;
	new_node->prop = prop;
	new_node->radius = m.d2;
	new_node->normal = m.nor;
	update_scene_obj(el, new_node);
	return (0);
}

int	scene_add_cylinder(t_scene *el, t_mikmak m, t_prop prop)
{
	t_obj	*new_node;

	new_node = malloc(sizeof(t_obj));
	if (new_node == NULL)
		return (-4);
	new_node->intersection = &inter_ray_cylinder;
	new_node->type = CYLINDER;
	new_node->pos = m.pos;
	new_node->prop = prop;
	new_node->normal = m.nor;
	new_node->diameter = m.d1;
	new_node->height = m.d2;
	update_scene_obj(el, new_node);
	return (0);
}
