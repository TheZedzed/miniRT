/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:36:07 by azeraoul          #+#    #+#             */
/*   Updated: 2021/01/18 16:36:53 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	char	*res;

	res = 0;
	ptr = (char *)s;
	while (*ptr)
	{
		if (*ptr == (unsigned char)c)
			res = ptr;
		++ptr;
	}
	if ((unsigned char)c == '\0')
		return (ptr);
	return (res);
}
