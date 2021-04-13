/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclerac <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 08:17:10 by aclerac           #+#    #+#             */
/*   Updated: 2021/04/12 07:40:36 by aclerac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

void	update_scene_obj(t_scene *env, t_obj *new_node);
void	update_scene_cam(t_scene *env, t_cam *new_node);
void	update_scene_lum(t_scene *env, t_light *new_node);

void free_scene_lum(t_scene *el);
void free_scene_obj(t_scene *el);
void free_scene_cam(t_scene *el);
int	free_all(t_scene *el);

int scene_add_triangle(t_scene *el, t_mikmak m, t_vect c, t_prop prop);
int scene_add_cylinder(t_scene *el, t_mikmak m, t_prop prop);
int scene_add_square(t_scene *el, t_mikmak m, t_prop prop);
int scene_add_sphere(t_scene *el, double radius, t_vect pos, t_prop prop);
int scene_add_plane(t_scene *el, t_vect normal, t_vect pos, t_prop prop);
int scene_add_circle(t_scene *el, t_mikmak m, t_prop prop);
int scene_add_cone(t_scene *el, t_mikmak m, t_prop prop);
int scene_add_lum(t_scene *el, t_vect pos, double ratio, t_vect intensity);
int scene_add_cam(t_scene *el, t_vect pos, t_vect axe, double fov);

#endif
