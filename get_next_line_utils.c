#include "get_next_line.h"
#define UINT_MAX 4294967295

void	*ft_calloc(size_t count, size_t n)
{
	size_t			i;
	unsigned char	*tab;

	i = 0;
	if (n != 0 && count > UINT_MAX / n)
		return (NULL);
	tab = (unsigned char *)malloc(count * n);
	if (tab != NULL)
	{
		while (i < count * n)
			tab[i++] = 0;
		return (tab);
	}
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *src)
{
	int		i;
	char	*dest;

	i = 0;
	dest = (char *)malloc((ft_strlen(src) + 1) * sizeof(char));
	if (dest != NULL)
	{
		while (src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
		return (dest);
	}
	return (NULL);
}

char	*ft_charjoin(char const *s1, char const s2)
{
	int		i;
	char	*tab;

	i = 0;
	if (!s1)
		s1 = ft_strdup("");
	tab = (char *)malloc((ft_strlen(s1) + 2) * sizeof(char));
	if (!tab)
		return (NULL);
	while (*s1)
		tab[i++] = *s1++;
	tab[i++] = s2;
	tab[i] = '\0';
	return (tab);
}
