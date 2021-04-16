/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_norm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 22:36:22 by azeraoul          #+#    #+#             */
/*   Updated: 2021/04/06 15:10:18 by aclerac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	vector(t_vect *a, double x, double y, double z)
{
	a->x = x;
	a->y = y;
	a->z = z;
}

double	norm2(t_vect *a)
{
	return (a->x * a->x + a->y * a->y + a->z * a->z);
}

double	norm(t_vect *a)
{
	return (sqrt(norm2(a)));
}

void	normalize(t_vect *a)
{
	double	n;

	n = norm(a);
	if (n)
	{
		n = 1 / n;
		a->x *= n;
		a->y *= n;
		a->z *= n;
	}
}
