/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgaunt <edgaunt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 17:29:33 by edgaunt           #+#    #+#             */
/*   Updated: 2014/11/09 18:32:40 by edgaunt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*cp1;
	unsigned char	*cp2;

	i = 0;
	cp1 = (unsigned char*)s1;
	cp2 = (unsigned char*)s2;
	while (i < n)
	{
		if (cp1[i] != cp2[i])
			return (cp1[i] - cp2[i]);
		i++;
	}
	return (0);
}
