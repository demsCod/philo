#include <stddef.h>
#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H
#define BUFF_SIZE 10

char    *get_next_line(int fd);
char    *ft_strcat(char  *dest, char *src);
void    ft_clean(char *victim);
char    *ft_cpynl(char *dest, char *src);
size_t  ft_strlen(char   *dest);
#endif