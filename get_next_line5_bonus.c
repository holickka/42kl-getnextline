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

static int	scanbuffer(char *buffer, t_list **tab, char **leftover)
{
    int i;

    i = 0;
    while (buffer[i] && buffer[i] != '\n')
        ft_lstadd_back(tab, ft_lstnew(ft_chrdup(buffer[i++])));
    if (buffer[i] == '\n')
    {
        ft_lstadd_back(tab, ft_lstnew(ft_chrdup(buffer[i++])));
        if (buffer[i])
        {
            *leftover = ft_calloc(ft_strlen(&buffer[i]) + 1, sizeof(char));
            ft_memcpy(*leftover, &buffer[i], ft_strlen(&buffer[i]));
        }
        return (0);
    }
    if (!buffer[i])
        ft_bzero(buffer, BUFFER_SIZE + 1);
    return (1);
}

static void	loadleftover(char *buffer, char **leftover)
{
    ft_memcpy(buffer, *leftover, ft_strlen(*leftover));
    free(*leftover);
    *leftover = NULL;
}

/* FOPEN_MAX is from stdio.h, max num of files allowed open */

char	*get_next_line(int fd)
{
    static char *leftover[FOPEN_MAX];
    char        buffer[BUFFER_SIZE + 1];
    char        *result;
    t_list      *tab;

    tab = NULL;
    if (fd < 0 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX)
        return (NULL);
    ft_bzero(buffer, BUFFER_SIZE + 1);
    if (leftover[fd])
        loadleftover(buffer, &leftover[fd]);
    if (!leftover[fd] && scanbuffer(buffer, &tab, &leftover[fd]))
    {
        while (read(fd, buffer, BUFFER_SIZE) > 0)
        {
            if (!scanbuffer(buffer, &tab, &leftover[fd]))
                break ;
        }
    }
    result = ft_combinestring(tab);
    ft_lstclear(&tab, &ft_del);
    return (result);
}
