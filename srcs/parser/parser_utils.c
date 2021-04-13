/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclerac <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 14:45:50 by aclerac           #+#    #+#             */
/*   Updated: 2021/04/06 15:06:13 by aclerac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parser.h"

int	consume_space(char **s)
{
	if (ft_isspace(**s))
	{
		while (**s && ft_isspace(**s))
			++(*s);
		if (**s == '-' || ft_isdigit(**s))
			return (0);
	}
	return (1);
}

int	nblen(int nb)
{
	int	len;

	len = 1;
	if (nb < 0)
		++len;
	while (nb <= -10 || nb >= 10)
	{
		nb /= 10;
		++len;
	}
	return (len);
}

int	check_end(char *s)
{
	if (s)
	{
		while (*s != '\n' && ft_isspace(*s))
			++s;
		if (*s && *s != '\n')
			return (-3);
	}
	return (0);
}

