/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:00:31 by mdembele          #+#    #+#             */
/*   Updated: 2024/05/24 21:00:29 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

int	ft_checknl(char *str)
{
	size_t	i;

	i = 0;
	if (*str)
		return(0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	stash[1000000];
	char		*buff;
	char		*line;
	int			check;

	check = 1;
	if (fd == -1)												/* si le fd est incorecte on retourne null*/
		return (NULL);
	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	*buff = '\0';
	if(buff == NULL)
		return (NULL);
	if ((ft_strlen(stash)) > 0)
		ft_clean(stash);
	while (check > 0  && ft_checknl(stash) != 1)
	{
		check = read(fd, buff, BUFFER_SIZE);
		if (check == -1)
			return (free(buff), NULL);

		buff[check] = '\0';
		ft_strcat(stash, buff);
		if (*stash == '\0')
			break ;
	}
	line = malloc(sizeof(char) * ft_strlen(stash) + 1);     /*malloc de la variable qu'on va renvoyer*/
	*line = '\0';
	if (line == NULL)                      /*si le malloc echoue on renvoie. null*/
		return (free(buff), NULL);
	if (check == 0 && ft_strlen(stash) == 0)
		return (free(line),free(buff), NULL);
	ft_cpynl(line, stash);
	return (free(buff), line);
}

/*int	main(void)
{
	int		fd;
	char	*line;

	fd = open("GNL.txt", O_RDWR);
	ft_putstr_fd("012345678901234567890123456789\n0", fd);
	close(fd);
	fd = open("GNL.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
}*/
