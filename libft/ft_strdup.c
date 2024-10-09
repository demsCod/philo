/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:42:10 by mdembele          #+#    #+#             */
/*   Updated: 2024/05/17 15:42:13 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char	*tab;

	tab = malloc(sizeof(char) * (ft_strlen(s)));
	if (!tab)
		return (NULL);
	tab = (char *)s;
	return (tab);
}
