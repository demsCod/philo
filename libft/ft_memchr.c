/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:45:28 by mdembele          #+#    #+#             */
/*   Updated: 2024/05/19 19:17:52 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*str;
	size_t		num;

	if (!s || !c || !n)
		return (NULL);
	num = 0;
	str = (const char *)s;
	if ((char)c == '\0')
		return ((void *)s + ft_strlen(str));
	while (num <= n)
	{
		if (str[num] == c)
			return ((void *)s + num);
		num++;
	}
	return (NULL);
}
