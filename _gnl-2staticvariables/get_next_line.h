#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct  	s_list
{
    void			*content;
    struct s_list	*next;
}   				t_list;

char	*get_next_line(int fd);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(void *content);
int	    ft_lstsize(t_list *lst);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	*ft_calloc(size_t count, size_t n);
size_t	ft_strlen(const char *s);
void	ft_bzero(void *s, size_t n);
char	*ft_strdup(const char *src);
char	*ft_charjoin(char const *s1, char const s2);
void	*ft_memcpy(void *dest, const void *src, size_t n);

# endif

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 2
# endif
