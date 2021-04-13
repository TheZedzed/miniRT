/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_add_obj1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclerac <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 08:17:10 by aclerac           #+#    #+#             */
/*   Updated: 2021/04/12 07:35:46 by aclerac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "scene.h"
#include "parser.h"
#include "inter.h"

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
