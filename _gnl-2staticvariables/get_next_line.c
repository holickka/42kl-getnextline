#include "get_next_line.h"

static void	ft_del(void	*mylist)
{
    free(mylist);
}

static char	*ft_chrdup(char c)
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

static char	*ft_combinestring(t_list *lst)
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

static void	createbuffer(char **buffer, char **oribuffer, int fd, int *bytesread)
{
    *buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
    *bytesread = read(fd, *buffer, BUFFER_SIZE);
    *oribuffer = *buffer;
}

static void	destroybuffer(char **buffer, char **oribuffer)
{
    free(*oribuffer);
    *buffer = NULL;
}

static int	scanbuffer(char **buffer, t_list **tab)
{
    while (**buffer && **buffer != '\n')
        ft_lstadd_back(tab, ft_lstnew(ft_chrdup(*(*buffer)++)));
    if (**buffer == '\n')
    {
        ft_lstadd_back(tab, ft_lstnew(ft_chrdup(*(*buffer)++)));
        return (0);
    }
    return (1);
}

char	*get_next_line(int fd)
{
    static char *buffer;
    static char *oribuffer;
    char        *result;
    t_list      *tab;
    int         bytesread;

    bytesread = 1;
    tab = NULL;
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    while (bytesread > 0)
    {
        if (!buffer)
            createbuffer(&buffer, &oribuffer, fd, &bytesread);
        if (!scanbuffer(&buffer, &tab))
            break ;
        if (!(*buffer))
            destroybuffer(&buffer, &oribuffer);
    }
    result = ft_combinestring(tab);
    ft_lstclear(&tab, &ft_del);
    return (result);
}
