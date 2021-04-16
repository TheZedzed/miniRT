/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 22:51:47 by azeraoul          #+#    #+#             */
/*   Updated: 2021/04/16 14:11:20 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <math.h>
# include <pthread.h>
# include <stdio.h>
# include <time.h>
# include "libft.h"
# include "mlx.h"
# include "debug.h"

typedef struct s_vect
{
	double	x;
	double	y;
	double	z;
}				t_vect;

typedef struct s_amb
{
	t_vect	intensity;
	double	ratio;
}				t_amb;

typedef struct s_light
{
	t_vect			pos;
	double			ratio;
	t_vect			intensity;
	struct s_light	*next;
}				t_light;

typedef struct s_cam
{
	t_vect			pos;
	t_vect			axe;
	double			fov;
	struct s_cam	*next;
	struct s_cam	*back;
}				t_cam;

typedef struct s_base
{
	t_vect	x_axis;
	t_vect	y_axis;
	t_vect	z_axis;
}				t_base;

typedef struct s_ray
{
	t_vect	org;
	t_vect	dir;
}				t_ray;

typedef enum e_type
{
	PLAN,
	SPHERE,
	TRIANGLE,
	CYLINDER,
	SQUARE,
	CIRCLE,
	CONE,
}				t_type;

typedef struct s_prop
{
	t_vect	diffuse;	
	double	reflection;
	double	refraction;
}				t_prop;

typedef struct s_obj
{
	t_vect			normal;
	double			radius;
	double			diameter;
	double			height;
	double			size;
	t_vect			a;
	t_vect			b;
	t_vect			c;
	t_vect			pos;
	t_prop			prop;
	t_type			type;
	double			(*intersection)(t_ray *, struct s_obj *);
	struct s_obj	*next;
}				t_obj;

typedef struct s_inter
{
	t_ray		ray;
	t_vect		point;
	t_vect		normal;
	t_obj		obj;
	double		t;
}				t_inter;
typedef struct s_text
{
	int		w;
	int		h;
	int		bpp;
	int		lz;
	int		endian;
	void	*img;
	char	*data;
}				t_text;

typedef struct s_scene
{
	t_text		txt;
	void		*mlx;
	void		*win;
	void		*img;
	int			*img_data;
	double		w;
	double		h;
	int			bpp;
	int			endian;
	int			lz;
	t_cam		*cam_current;
	t_cam		*cam_head;
	t_cam		*cam_tail;
	t_obj		*obj_head;
	t_obj		*obj_tail;
	t_light		*lum_head;
	t_light		*lum_tail;
	t_amb		amb;
	t_base		base;
	char		*title;
	int			set_txt;
	int			tid;
	int			start;
	int			stop;
	int			save;
	double		gamma;
	int			reflect_depth;
	int			do_refract;
	int			aliasing;
	int			sepia;
}				t_scene;

typedef struct s_mikmak
{
	t_vect	pos;
	t_vect	nor;
	double	d1;
	double	d2;
}				t_mikmak;

typedef double			(*t_inter_ray)(t_ray *ray, t_obj *obj);
typedef unsigned int	t_uint;

/*
** vector operation
*/
double	dot(t_vect *a, t_vect *b);
t_vect	cross(t_vect *a, t_vect *b);
t_vect	scalar(double t, t_vect *a);
t_vect	sub(t_vect *a, t_vect *b);
t_vect	add(t_vect *a, t_vect *b);

/*
** ray
*/
void	vector(t_vect *vector, double x, double y, double z);
void	Ray(t_ray *ray, t_vect *org, t_vect *dir);
void	normalize(t_vect *el);
double	norm(t_vect *el);
double	norm2(t_vect *el);

/*
** utils
*/
int		print_error(t_scene *env, int err);
void	random_value(double *a, double *b);

/*
** save
*/
void	scene_to_bmp(t_scene el, char *path);

/*
** render
*/
int		draw(t_scene *el);
void	setup_multithreading(t_scene daddy, t_scene *childs);
void	lunch_multithreading(t_scene *childs);

/*
** texture
*/
int		set_texture(t_scene *el);
t_uint	text_color(t_scene *el, t_inter *inter);

/*
** set base
*/
void	rotate(t_vect *ray, t_base *base);
void	init_base(t_base *base, t_vect *axe);

/*
** inter func
*/
t_vect	normalize_obj(t_inter *inter, t_obj *obj);
t_vect	normal_cylinder(t_inter *inter, t_obj *cy);
t_vect	normal_cone(t_inter *ray, t_obj *co);
int		intersection(t_inter *inter, t_scene *env);
double	inter_ray_square(t_ray *ray, t_obj *sq);
double	inter_ray_circle(t_ray *ray, t_obj *ci);
double	inter_ray_triangle(t_ray *ray, t_obj *tr);
double	inter_ray_plane(t_ray *ray, t_obj *pl);
double	inter_ray_sphere(t_ray *ray, t_obj *sp);
double	inter_ray_cylinder(t_ray *ray, t_obj *cy);
double	inter_ray_cone(t_ray *ray, t_obj *co);

/*
** quadra equa
*/
double	poly_cylinder(double poly[4], double ze, double zd, t_obj *cy);
double	poly_cone(double poly[4], double ze, double zd, t_obj *co);

/*
** ray tracer
*/
void	*ray_tracer(void *el);
void	ray_at(t_inter *inter, t_scene *env, int i, int j);
void	calc_sepia(double *color);
void	get_reflect(t_scene *env, t_inter *ray, double *param, double *color);
int		in_shadow(t_scene *env, t_inter *ray, t_inter *sray, t_light *light);
void	reflected_ray(t_inter *ray);
void	lambert_color(double lambert, t_inter *ray, t_light *light, double *co);
void	get_color(t_scene *el, t_inter *ray, int *param, double *color);
int		final_color(double *c, t_scene *el);
void	recursive(t_scene *el, t_inter *ray, double *param, double *color);

/*
** init scene
*/
int		parse_arg(t_scene *el, int ac, char **av);
void	sub_init(t_scene *el);
int		init_scene(t_scene *el, int ac, char **av);
int		set_mlx(t_scene *el);
void	parse_bonus(t_scene *el, int ac, char **av);

/*
** hooks
*/
int		change_camera(int direction, t_scene *el);
int		camera_rotation(int direction, t_scene *el);
int		action_key(int keynote, t_scene *el);
int		get_obj(int button, int x, int y, t_scene *el);

/*
** parser utils
*/
int		check_end(char *s);
int		consume_space(char **s);
int		nblen(int sign, int nb);
int		parse_colors(int positive, int unit, t_vect *el, char **s);
int		parse_unit(int positive, int unit, double *value, char **s);
int		parse_values(int positive, int unit, t_vect *el, char **s);
void	make_left(char **s, double *nb);

/*
** parser
*/
int		parse_rt(t_scene *el, char *rt);
int		parse_line(char *line, t_scene *el);
int		parse_prop(t_prop *el, char **s);
int		parse_ambient(char *line, char **end, t_scene *el);
int		parse_resolution(char *line, char **end, t_scene *el);
int		parse_camera(char *line, char **end, t_scene *el);
int		parse_light(char *line, char **end, t_scene *el);
int		parse_obj(char *line, t_scene *el);
int		parse_square(char *line, char **end, t_scene *el);
int		parse_sphere(char *line, char **end, t_scene *el);
int		parse_triangle(char *line, char **end, t_scene *el);
int		parse_plane(char *line, char **end, t_scene *el);
int		parse_circle(char *line, char **end, t_scene *el);
int		parse_cylinder(char *line, char **end, t_scene *el);
int		parse_cone(char *line, char **end, t_scene *el);
int		sub_parse_cone(t_mikmak *m, char **line);
int		sub_parse_cylinder(t_mikmak *m, char **line);
int		sub_parse_circle(t_mikmak *m, char **line);
int		sub_parse_triangle(t_mikmak *m, char **line);
int		sub_parse_square(t_mikmak *m, char **line);

/*
** update scene
*/
void	update_scene_obj(t_scene *env, t_obj *new_node);
void	update_scene_cam(t_scene *env, t_cam *new_node);
void	update_scene_lum(t_scene *env, t_light *new_node);
int		scene_add_triangle(t_scene *el, t_mikmak m, t_vect c, t_prop prop);
int		scene_add_cylinder(t_scene *el, t_mikmak m, t_prop prop);
int		scene_add_square(t_scene *el, t_mikmak m, t_prop prop);
int		scene_add_sphere(t_scene *el, double radius, t_vect pos, t_prop prop);
int		scene_add_plane(t_scene *el, t_vect normal, t_vect pos, t_prop prop);
int		scene_add_circle(t_scene *el, t_mikmak m, t_prop prop);
int		scene_add_cone(t_scene *el, t_mikmak m, t_prop prop);
int		scene_add_lum(t_scene *el, t_vect pos, double ratio, t_vect intensity);
int		scene_add_cam(t_scene *el, t_vect pos, t_vect axe, double fov);

/*
** free
*/
void	free_scene_lum(t_scene *el);
void	free_scene_obj(t_scene *el);
void	free_scene_cam(t_scene *el);
int		free_all(t_scene *el);

#endif
