/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:22:37 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/06 17:08:08 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../includes/libft.h"
#include "../../includes/error.h"

void	ft_close_fd(int *fd)
{
	if (*fd == -1)
		return ;
	if (close(*fd) == -1)
		error_log("ft_close_fd: close() failed:", true);
	*fd = -1;
}
