/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:19:32 by azeraoul          #+#    #+#             */
/*   Updated: 2021/04/16 13:29:42 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcat(char *dest, char const *src)
{
	int		dest_len;
	int		src_len;

	dest_len = 0;
	src_len = 0;
	while (dest[dest_len])
		++dest_len;
	while (src[src_len])
	{
		dest[dest_len + src_len] = src[src_len];
		++src_len;
	}
	dest[dest_len + src_len] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	len;

	if (s1 && !s2)
		len = ft_strlen(s1);
	else if (!s1 && s2)
		len = ft_strlen(s2);
	else if (!s1 && !s2)
		len = 0;
	else
		len = ft_strlen(s1) + ft_strlen(s2);
	res = ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (NULL);
	if (s1)
		ft_strcat(res, s1);
	if (s2)
		ft_strcat(res, s2);
	return (res);
}
