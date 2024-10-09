#include <stddef.h>
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

size_t	ft_strlen(const char *dest);
char	*get_next_line(int fd);
void	ft_strcat(const char *dest, char *src);
void	ft_clean(char *victim);
char	*ft_cpynl(char *dest, char *src);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
#endif
