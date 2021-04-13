/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:01:26 by azeraoul          #+#    #+#             */
/*   Updated: 2021/01/19 13:16:42 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ptr;

	ptr = (const unsigned char *)s;
	while (n)
	{
		if (*ptr == (unsigned char)c)
			return ((void *)ptr);
		++ptr;
		--n;
	}
	return (0);
}
