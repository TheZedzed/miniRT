/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclerac <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 10:56:04 by aclerac           #+#    #+#             */
/*   Updated: 2021/04/11 22:02:21 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define ERR_M5 "Parsing failed, can't load a scene\n"
# define ERR_M4 "Parsing failed, malloc object failed\n"
# define ERR_M3 "Parsing failed, wrong end line format\n"
# define ERR_M2 "Failed to open rt file\n"
# define ERR_M1 "Failed to read line from rt file\n"
# define ERR_1 "Usage: ./miniRT <scene>.rt [--save]\n"
# define ERR_2 "Mlx error during process\n"
# define ERR_3 "Parsing failed, wrong begining line format\n"

# define ERR_4 "Parsing failed, ambient already done\n"
# define ERR_5 "Parsing failed, wrong spaces from ambiant information\n"
# define ERR_6 "Parsing failed, wrong values from ambiant information\n"
# define ERR_7 "Parsing failed, wrong colors from ambiant information\n"

# define ERR_8 "Parsing failed, resolution already done\n"
# define ERR_9 "Parsing failed, wrong spaces from resolution information\n"
# define ERR_10 "Parsing failed, wrong values from resolution information\n"

# define ERR_11 "Parsing failed, wrong spaces from camera information\n"
# define ERR_12 "Parsing failed, wrong position from camera information\n"
# define ERR_13 "Parsing failed, wrong axe from camera information\n"
# define ERR_14 "Parsing failed, wrong fov from camera information\n"

# define ERR_15 "Parsing failed, wrong spaces from light information\n"
# define ERR_16 "Parsing failed, wrong position from light information\n"
# define ERR_17 "Parsing failed, wrong ratio from light information\n"
# define ERR_18 "Parsing failed, wrong color from light information\n"

# define ERR_19 "Parsing failed, wrong spaces from sphere information\n"
# define ERR_20 "Parsing failed, wrong position from sphere information\n"
# define ERR_21 "Parsing failed, wrong diameter from sphere information\n"
# define ERR_22 "Parsing failed, wrong color,re,ra from sphere information\n"

# define ERR_23 "Parsing failed, wrong spaces from square information\n"
# define ERR_24 "Parsing failed, wrong position from square information\n"
# define ERR_25 "Parsing failed, wrong axe from square information\n"
# define ERR_26 "Parsing failed, wrong size from square information\n"
# define ERR_27 "Parsing failed, wrong color,re,ra from square information\n"

# define ERR_28 "Parsing failed, wrong spaces from triangle information\n"
# define ERR_29 "Parsing failed, wrong pointA from triangle information\n"
# define ERR_30 "Parsing failed, wrong pointB from triangle information\n"
# define ERR_31 "Parsing failed, wrong pointC from triangle information\n"
# define ERR_32 "Parsing failed, wrong color,re,ra from triangle information\n"

# define ERR_33 "Parsing failed, wrong spaces from plane information\n"
# define ERR_34 "Parsing failed, wrong position from plane information\n"
# define ERR_35 "Parsing failed, wrong axe from plane information\n"
# define ERR_36 "Parsing failed, wrong color,re,ra from plane information\n"

# define ERR_37 "Parsing failed, wrong spaces from circle information\n"
# define ERR_38 "Parsing failed, wrong position from circle information\n"
# define ERR_39 "Parsing failed, wrong axe from circle information\n"
# define ERR_40 "Parsing failed, wrong radius from circle information\n"
# define ERR_41 "Parsing failed, wrong color,re,ra from circle information\n"

# define ERR_42 "Parsing failed, wrong spaces from cyl information\n"
# define ERR_43 "Parsing failed, wrong position from cyl information\n"
# define ERR_44 "Parsing failed, wrong axe from cyl information\n"
# define ERR_45 "Parsing failed, wrong diameter from cyl information\n"
# define ERR_46 "Parsing failed, wrong height from cyl information\n"
# define ERR_47 "Parsing failed, wrong color,re,ra from cyl information\n"

# define ERR_48 "Parsing failed, wrong spaces from cone information\n"
# define ERR_49 "Parsing failed, wrong position from cone information\n"
# define ERR_50 "Parsing failed, wrong axe from cone information\n"
# define ERR_51 "Parsing failed, wrong radius from cone information\n"
# define ERR_52 "Parsing failed, wrong height from cone information\n"
# define ERR_53 "Parsing failed, wrong color,re,ra from cone information\n"

int	check_end(char *s);
int	consume_space(char **s);
int	nblen(int nb);

int	parse_prop(t_prop *el, char **s);
int	parse_colors(int positive, int unit, t_vect *el, char **s);
int	parse_unit(int positive, int unit, double *value, char **s);
int	parse_values(int positive, int unit, t_vect *el, char **s);

int	parse_ambient(char *line, char **end, t_scene *el);
int	parse_resolution(char *line, char **end, t_scene *el);
int	parse_camera(char *line, char **end, t_scene *el);
int	parse_light(char *line, char **end, t_scene *el);
int	parse_obj(char *line, t_scene *el);

int	parse_square(char *line, char **end, t_scene *el);
int	parse_sphere(char *line, char **end, t_scene *el);
int	parse_triangle(char *line, char **end, t_scene *el);
int	parse_plane(char *line, char **end, t_scene *el);
int	parse_circle(char *line, char **end, t_scene *el);
int	parse_cylinder(char *line, char **end, t_scene *el);
int	parse_cone(char *line, char **end, t_scene *el);

int	parse_rt(t_scene *scene, char *rt);
int	parse_line(char *line, t_scene *el);

#endif
