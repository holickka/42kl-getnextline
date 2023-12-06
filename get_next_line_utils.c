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
