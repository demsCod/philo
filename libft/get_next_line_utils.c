#include <stddef.h>

size_t	ft_strlen(char *dest)
{
	size_t	i;

	i = 0;
	while (dest[i])
		i++;
	return (i);
}

char	*ft_strcat(char *dest, char *src)
{
	long long	i;
	long long	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	return (dest);
}
char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	ft_clean(char *victim)
{
	size_t	i;

	i = 0;
	while (victim[i] != '\n' && victim[i])
	{
		victim[i] = '\0';
		i++;
	}
	ft_strcpy(victim, victim + i + 1);
}

char	*ft_cpynl(char *dest, char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

