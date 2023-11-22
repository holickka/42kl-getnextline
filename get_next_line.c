#include "get_next_line.h"
/*
char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*dest;
	static int	i;
	int			a;

	i = 0;
	a = 0;
	buffer = (char *)ft_calloc(BUFFER_SIZE, sizeof(char));
	if (!buffer)
		return (NULL);
	bytesread = read(fd, buffer, BUFFER_SIZE);
	if (bytesread > 0)
	{
		dest = (char *)ft_calloc(ft_strlen(buffer), sizeof(char));
		if (!dest)
			return (NULL);
		while (buffer[i] && buffer[i] != '\n')
			dest[a++] = buffer[i++]
		i++;
		return (dest);
	}
	return (NULL);
}
*/
int	test()
{
	static int	*a;
	a = 0;
	a++;
	return (a);
}
int	main()
{
	printf("%d", test());
	printf("%d", test());

}
/* read content from file to buffer */


/*
| notes |
| main task |
to read text file pointed by file descriptor,
one line at a time
malloc and returns the line that's read
if nothing to read or error, return NULL

| about read() |
read() returns num of bytes read
on error read() return -1

read() stores data read in 'buffer',
BUFFER_SIZE defines how many bytes to read
*/
