/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:54:27 by mdembele          #+#    #+#             */
/*   Updated: 2024/05/17 17:44:48 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	*ft_memmove(void *destination, const void *source, size_t size)
{
	unsigned char	tmp[size];

	ft_memcpy(tmp, source, size);
	ft_memcpy(destination, tmp, size);
	return (destination);
}

/*int main(void)
{
	char	src[] = "lorem ipsum dolor sit amet";
	char	*dest;

	dest = src + 1;
	if (dest != ft_memmove(dest, src, 8))
			write(1, "dest's adress was not returned\n", 31);
		write(1, dest, 22);
}
*/
