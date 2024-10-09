/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:48:09 by mdembele          #+#    #+#             */
/*   Updated: 2024/05/17 15:48:17 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	void	*s;

	s = malloc(sizeof(elementSize) * elementCount);
	if (!(s))
		return (NULL);
	ft_bzero(s, elementCount);
	return (s);
}
