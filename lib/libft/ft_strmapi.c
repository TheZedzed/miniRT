/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:29:46 by azeraoul          #+#    #+#             */
/*   Updated: 2021/03/22 21:01:21 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ret;
	size_t			len;
	unsigned int	i;

	i = 0;
	len = ft_strlen(s);
	ret = ft_calloc(len + 1, sizeof(char));
	if (!ret)
		return (NULL);
	while (i < len)
	{
		ret[i] = (*f)(i, s[i]);
		i++;
	}
	return (ret);
}
