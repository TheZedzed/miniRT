/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 15:58:22 by azeraoul          #+#    #+#             */
/*   Updated: 2021/04/16 13:37:56 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*psrc;
	unsigned char	*pdst;

	psrc = (unsigned char *)src;
	pdst = (unsigned char *)dst;
	while (n--)
	{
		*pdst++ = *psrc;
		if (*psrc++ == (unsigned char)c)
			return (pdst);
	}
	return (NULL);
}
