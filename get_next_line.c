#include "get_next_line.h"

static int	ft_isnewline(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if(buffer[i] == '\n')
			return (i + 1);
		i++;
	}
	return (i);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*dest;
	int			bytesread;
	int			a;

	a = 0;
	/* create buffer to store data frm read */
	if (!buffer && fd != -1)
	{
		buffer = (char *)ft_calloc(BUFFER_SIZE, sizeof(char));
		if (!buffer)
			return (NULL);
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread == -1)
			return (NULL);
	}
	if (!*buffer || fd == -1)
		return (NULL);
	/* calloc to store string til nl */
	dest = (char *)ft_calloc((ft_isnewline(buffer) + 1), sizeof(char));
	if (!dest)
		return (NULL);
	while (*buffer && *buffer != '\n')
		dest[a++] = *buffer++;
	if (*buffer == '\n')
		dest[a++] = *buffer++;
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
int	main()
{
	int		fd;
	int		byteswrite;
	int		bytesread;
	char	buf[100];
	char	data[] = "Hello\nWorld";

	// create a new file
	fd = open("file.txt", O_RDWR | O_CREAT, 0666);
	if (fd == -1)
		return (0);

	// write something into file
	byteswrite = write(fd, data, strlen(data));
	if (byteswrite == -1)
		return (0);

	//close it to reset pointer after write
	close(fd);

	// open it again
	fd = open("file.txt", O_RDWR);

	// try to read it
	bytesread = read(fd, buf, byteswrite);
	if (bytesread == -1 )
		return (0);
	buf[bytesread] = '\0';

	// print it out
	printf("%s\n", buf);
}
*/
/*
| notes |
| main task |
to read text file pointed by file descriptor,
one line at a time
malloc and returns the line that's read
returned line should include \n
if nothing to read or error, return NULL

| about read() |
read() returns num of bytes read
on error read() return -1

read() stores data read in 'buffer',
BUFFER_SIZE defines how many bytes to read
*/
