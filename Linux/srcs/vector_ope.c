/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ope.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 22:28:00 by azeraoul          #+#    #+#             */
/*   Updated: 2021/04/06 15:10:56 by aclerac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vect	add(t_vect *a, t_vect *b)
{
	t_vect	new;

	new.x = a->x + b->x;
	new.y = a->y + b->y;
	new.z = a->z + b->z;
	return (new);
}

t_vect	sub(t_vect *a, t_vect *b)
{
	t_vect	new;

	new.x = a->x - b->x;
	new.y = a->y - b->y;
	new.z = a->z - b->z;
	return (new);
}

t_vect	scalar(double t, t_vect *a)
{
	t_vect	new;

	new.x = a->x * t;
	new.y = a->y * t;
	new.z = a->z * t;
	return (new);
}

double	dot(t_vect *a, t_vect *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

t_vect	cross(t_vect *a, t_vect *b)
{
	t_vect	new;

	new.x = a->y * b->z - a->z * b->y;
	new.y = a->z * b->x - a->x * b->z;
	new.z = a->x * b->y - a->y * b->x;
	return (new);
}
