/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclerac <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 09:10:37 by aclerac           #+#    #+#             */
/*   Updated: 2021/04/12 08:23:18 by aclerac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_TRACER_H
# define RAY_TRACER_H
void			Ray(t_ray *ray, t_vect *org, t_vect *dir);
void			rotate(t_vect *ray, t_base *base);
unsigned int	text_color(t_scene *env, t_inter *inter);
void    		init_base(t_base *base, t_vect *axe);
void			*ray_tracer(void *el);
void			ray_at(t_inter *inter, t_scene *env, int i, int j);
void			calc_sepia(double *color);
void			get_reflect(t_scene *env, t_inter *ray, double *param, double *color);
int				in_shadow(t_scene *env, t_inter *ray, t_inter *shadow_ray, t_light *light);
void			reflected_ray(t_inter *ray);
void			lambert_color(double lambert, t_inter *ray, t_light *light, double *color);
#endif
