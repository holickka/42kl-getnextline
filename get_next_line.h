#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

char	*get_next_line(int fd);
void	*ft_calloc(size_t count, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *src);
char	*ft_charjoin(char const *s1, char const s2);

# endif

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 2
# endif
