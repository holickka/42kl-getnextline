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

void	createbuffer(static char **buffer, int fd)
{
    buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
    bytesread = read(fd, buffer, BUFFER_SIZE);
    oribuffer = buffer;
}

void	destroybuffer(static char *buffer, static char *oribuffer)
{
    free(oribuffer);
    buffer = NULL;
}

void	scanbuffer(static char *buffer)
{
    while (*buffer && *buffer != '\n')
        ft_lstadd_back(&temp, ft_lstnew(ft_chrdup(*buffer++)));
    if (*buffer == '\n')
    {
        ft_lstadd_back(&temp, ft_lstnew(ft_chrdup(*buffer++)));
        break ;
    }
}

char	*get_next_line(int fd)
{
    static char *buffer;
    static char *oribuffer;
    char        *result;
    t_list      *temp;
    int         bytesread;

    bytesread = 1;
    temp = NULL;
    while (bytesread > 0)
    {
        if (!buffer)
            createbuffer(&buffer, fd);
        while (*buffer && *buffer != '\n')
            ft_lstadd_back(&temp, ft_lstnew(ft_chrdup(*buffer++)));
        if (*buffer == '\n')
        {
            ft_lstadd_back(&temp, ft_lstnew(ft_chrdup(*buffer++)));
            break ;
        }
        if (!(*buffer))
            destroybuffer(&buffer, &oribuffer);
    }
    result = ft_combinestring(temp);
    ft_lstclear(&temp, &ft_del);
    return (result);
}
