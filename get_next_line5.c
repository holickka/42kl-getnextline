#include "get_next_line.h"

void	ft_del(void	*mylist)
{
    free(mylist);
}

char	*ft_chrdup(char c)
{
    char    *dest;
    int     i;

    i = 0;
    if (!c)
        return (NULL);
    dest = (char *)malloc(2 * sizeof(char));
    if (!dest)
        return (NULL);
    dest[i++] = c;
    dest[i] = '\0';
    return (dest);
}

char	*ft_combinestring(t_list *lst)
{
    t_list  *temp;
    char    *tab;
    char    *oritab;

    if(!lst)
        return (NULL);
    tab = ft_calloc((ft_lstsize(lst) + 1), sizeof(char));
    oritab = tab;
    temp = lst;
    while (temp)
    {
        ft_memcpy(tab++, temp->content, 1);
        temp = temp->next;
    }
    return(oritab);
}

void	createbuffer(char **buffer, char **oribuffer, int fd, int *bytesread)
{
    *buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
    *bytesread = read(fd, *buffer, BUFFER_SIZE);
    *oribuffer = *buffer;
}

void	destroybuffer(char **buffer, char **oribuffer)
{
    free(*oribuffer);
    *buffer = NULL;
}

int	scanbuffer(char **buffer, t_list **tab, char **leftover)
{
    int i;

    i = 0;
    while (*buffer[i] && *buffer[i] != '\n')
        ft_lstadd_back(tab, ft_lstnew(ft_chrdup(*buffer[i++])));
    if (*buffer[i] == '\n')
    {
        ft_lstadd_back(tab, ft_lstnew(ft_chrdup(*buffer[i++])));
        if (*buffer[i])
        {
            leftover = ft_calloc(ft_strlen(&buffer[i]) + 1, sizeof(char));
            ft_memcpy(leftover, &buffer[i], ft_strlen(&buffer[i]));
        }
        return (0);
    }
    return (1);
}

char	*get_next_line(int fd)
{
    static char *leftover;
    char        buffer[BUFFER_SIZE + 1];
    char        *result;
    t_list      *tab;

    tab = NULL;
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    ft_bzero(buffer, BUFFER_SIZE + 1);
    while (leftover)
    {
        ft_memcpy(buffer, leftover, ft_strlen(leftover));
        free(leftover);
        if (!scanbuffer(&buffer, &tab, &leftover))
            break ;
    }
    while (read(fd, buffer, BUFFER_SIZE) > 0 && !leftover)
    {
        if (!scanbuffer(&buffer, &tab, &leftover))
            break ;
    }
    result = ft_combinestring(tab);
    ft_lstclear(&tab, &ft_del);
    return (result);
}
