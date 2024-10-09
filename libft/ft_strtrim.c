/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:39:27 by mdembele          #+#    #+#             */
/*   Updated: 2024/05/17 15:39:30 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int	verif_set(const char *set, char letter)
{
	int	i;

	i = 0;
	if (set == NULL)
		return (0);
	if (!(letter))
		return (1);
	while (set[i])
	{
		if (letter == set[i])
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		top;
	int		maximus;
	size_t	minus;
	char	*strrim;

	i = 0;
	minus = 0;
	maximus = 0;
	top = 1;
	while (s1[i])
	{
		if (top == 1 && verif_set(set, s1[i]) == 1)
			maximus++;
		else
			top = 0;
		i++;
	}
	top = 1;
	i = ft_strlen(s1) - 1;
	minus = ft_strlen(s1);
	while (i > 0)
	{
		if (top == 1 && verif_set(set, s1[i]) == 1)
			minus--;
		else
			top = 0;
		i--;
	}
	strrim = ft_substr(s1, maximus, minus);
	return (strrim);
}
