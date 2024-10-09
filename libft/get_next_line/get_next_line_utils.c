#include <stddef.h>

char    *ft_strcat(char  *dest, char *src)
{
    size_t  i;
    size_t  j;

    i = 0;
    j = 0;
    while(dest[i])
        i++;
    while(src[j])
    {
        dest[i] = src[j];
        i++;
        j++;
    }
    dest[i] = '\0';
    return(dest);
}
char    *ft_strcpy(char *dest, char *src)
{
    int i;

    i = 0;
    while(src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return(dest);
}

void    ft_clean(char *victim)
{
    size_t  i;

    i = 0;
    while(victim[i] != '\n' && victim[i])
        i++;
    ft_strcpy(victim, victim + i + 1);
}

char    *ft_cpynl(char *dest, char *src)
{
    size_t  i;

    i = 0;
    while(src[i] && src[i] != '\n')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return(dest);
}

size_t  ft_strlen(char   *dest)
{
    size_t  i;

    i = 0;
    while(dest[i])
        i++;
    return(i);
}