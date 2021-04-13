/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 22:51:47 by azeraoul          #+#    #+#             */
/*   Updated: 2021/04/12 07:34:49 by aclerac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define SEPIA	0 
# define NB_THREADS	4
# define MIN(a,b) ((a) < (b) ? (a) : (b))
# define MAX(a,b) ((a) > (b) ? (a) : (b))
# ifdef __APPLE__
     #define ESC	0x35
     #define LEFT	0x7b
     #define RIGHT	0x7c
     #define CTOP	0x0d
     #define CBOT	0x01
     #define CLFT	0x00
     #define CRGT	0x02
     #define MASK 1L << 2
     #define EVNT 17
# elif __linux__
     #define ESC	0xff1b
     #define LEFT	0xff51
     #define RIGHT	0xff53
     #define CTOP	0x77
     #define CBOT	0x73
     #define CLFT	0x61
     #define CRGT	0x64
     #define MASK 1L << 5
     #define EVNT 33
# endif

# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include <pthread.h>
# include <stdio.h>
# include <time.h>
# include "libft.h"
# include "mlx.h"

typedef struct	s_vect
{
	double	x;
	double	y;
	double	z;
}				t_vect;

typedef struct	s_amb
{
	t_vect	intensity; 
	double	ratio;
}				t_amb;

typedef struct	s_light
{
	t_vect	pos;
	double	ratio;
	t_vect	intensity; 
	struct s_light *next;
}				t_light;

typedef struct	s_cam
{
	t_vect	pos;
	t_vect	axe;
	double	fov;
	struct s_cam *next;
	struct s_cam *back;
}				t_cam;

typedef struct	s_base
{
	t_vect	x_axis;
	t_vect	y_axis;
	t_vect	z_axis;
}				t_base;

typedef struct	s_ray
{
	t_vect	org;
	t_vect	dir;
}				t_ray;

typedef enum	e_type
{
	PLAN,
	SPHERE,
	TRIANGLE,
	CYLINDER,
	SQUARE,
	CIRCLE,
	CONE,
	CUBE,
}				t_type;

typedef struct	s_prop
{
	t_vect	diffuse;	
	double	reflection;
	double	refraction;
}				t_prop;

typedef struct	s_obj
{
	t_vect	normal;
	double	radius;
	double	diameter;
	double	height;
	double	size;
	t_vect	a;
	t_vect	b;
	t_vect	c;
	t_vect	pos;
	t_prop	prop;
	t_type	type;
	double	(*intersection)(t_ray *, struct s_obj *);
	struct s_obj	*next;
}				t_obj;

typedef struct	s_inter
{
	t_ray		ray;
	t_ray		light_ray;
	t_vect		point;
	t_vect		normal;
	t_obj		obj;
	double		t;
}				t_inter;

typedef struct	s_text
{
	int w;
	int h;
	int bpp;
	int lz;
	int endian;
	void *img;
	char *data;
}				t_text;

typedef struct	s_scene
{
	int			set_text;
	t_text		txt;
	int			threadid;
	int			antialiasing;
	void		*mlx;
	void		*win;
	void		*img;
	int			*img_data;
	double			w;
	double			h;
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
	int 		start_index;
	int			stopp_index;
	int			save;
	double			gamma;
}				t_scene;

typedef	struct	s_mikmak
{
	t_vect	pos;
	t_vect	nor;
	double	d1;
	double	d2;
}				t_mikmak;

typedef	double (*t_inter_ray)(t_ray *ray, t_obj *obj);

double		dot(t_vect *a, t_vect *b);
t_vect		cross(t_vect *a, t_vect *b);
t_vect		scalar(double t, t_vect *a);
t_vect		sub(t_vect *a, t_vect *b);
t_vect		add(t_vect *a, t_vect *b);

void		vector(t_vect *vector, double x, double y, double z);
void		normalize(t_vect *el);
double		norm(t_vect *el);
double		norm2(t_vect *el);
int		set_texture(t_scene *el);
void		scene_to_bmp(t_scene el, char *path);
int			leave(t_scene *el);
int			draw(t_scene *el);
int		change_camera(int direction, t_scene *el);
#endif

