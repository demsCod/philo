/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:39:16 by mdembele          #+#    #+#             */
/*   Updated: 2024/05/17 15:39:19 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*substr;

	substr = malloc(sizeof(char) * len + 1);
	if (!(substr))
		return (NULL);
	ft_strlcpy(substr, s + start, len + 1);
	return (substr);
}
