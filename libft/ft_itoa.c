/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:47:22 by mdembele          #+#    #+#             */
/*   Updated: 2024/05/17 15:51:11 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char	*ft_rvtab(char *str)
{
	int		fin;
	int		debut;
	char	*temp;

	temp = malloc(sizeof(char) * 1);
	fin = ft_strlen(str) - 1;
	debut = 0;
	while (fin > debut)
	{
		temp[0] = str[fin];
		str[fin] = str[debut];
		str[debut] = temp[0];
		fin--;
		debut++;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*itoa;
	int		i;
	int		isneg;

	isneg = 0;
	i = 0;
	itoa = malloc(sizeof(char) * 12);
	if (!(itoa))
		return (NULL);
	if (n == 0)
	{
		itoa[0] = '0';
		itoa[1] = '\0';
		return (itoa);
	}
	if (n == -2147483648)
		return ("-2147483648\0");
	if (n < 0)
	{
		n = n * (-1);
		isneg = 1;
	}
	while (n != 0)
	{
		itoa[i] = n % 10 + '0';
		n = n / 10;
		i++;
	}
	if (isneg == 1)
	{
		itoa[i] = '-';
		i++;
	}
	itoa[i] = '\0';
	ft_rvtab(itoa);
	return (itoa);
}
