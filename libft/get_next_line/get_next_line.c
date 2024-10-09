
#include "get_next_line.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <stddef.h>
#include <unistd.h>

/*ssize_t read(int fd, void *buf, size_t count)*/
int ft_checknl(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(str[i] == '\n')
            return (1);
        i++;
    }
    return (0);
}

char    *get_next_line(int fd)
{
    static  char    stash[1024];
    char            buff[1024];
    char            *line;
    size_t          i;
    int             check;

    check = 0;
    i = 0;
    //buff = malloc(sizeof(char) * BUFF_SIZE + 5);
    //stash = malloc(sizeof(char) * BUFF_SIZE + 5);
    line = malloc(sizeof(char) * 1024);

    if(ft_strlen(stash) > 0)
        ft_clean(stash);
    while(check >= 0 && ft_checknl(stash) != 1)
    {
        check = read(fd, buff, BUFF_SIZE);
        if(check <= 0)
            break;
        buff[check] = '\0';
        ft_strcat(stash, buff);
    }
    if (check == 0)
        return(0);
    ft_cpynl(line, stash);
    return(line);
}


int main(int ac , char** av)
{
    int fd;
    char *line;
    
    fd = open("GNL.txt", O_RDONLY);
    while(1)
    {
        line = get_next_line(fd);
        printf("\n%s", line);
        if(line == NULL)
            break;
        free(line);
    }
}
