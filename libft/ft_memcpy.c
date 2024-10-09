/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:27:32 by mdembele          #+#    #+#             */
/*   Updated: 2024/05/17 17:27:33 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	int					i;
	unsigned char		*destx;
	unsigned const char	*srcx;

	srcx = src;
	destx = dest;
	i = 0;
	while (n--)
	{
		destx[i] = srcx[i];
		i++;
	}
	return (dest);
}
