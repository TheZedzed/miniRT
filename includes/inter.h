/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclerac <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 09:09:18 by aclerac           #+#    #+#             */
/*   Updated: 2021/04/12 08:27:48 by aclerac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTER_H
# define INTER_H
# include "minirt.h"

t_vect	normalize_obj(t_inter *inter, t_obj *obj);
int		intersection(t_inter *inter, t_scene *env);
double	inter_ray_square(t_ray *ray, t_obj *sq);
double	inter_ray_triangle(t_ray *ray, t_obj *tr);
double	inter_ray_cylinder(t_ray *ray, t_obj *cy);
double	inter_ray_plane(t_ray *ray, t_obj *pl);
double	inter_ray_sphere(t_ray *ray, t_obj *sp);
double	inter_ray_circle(t_ray *ray, t_obj *ci);
double	inter_ray_cone(t_ray *ray, t_obj *co);
#endif
