#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*dest;
	int			bytesread;

	if (BUFFER_SIZE <= 0 || fd < 0 )
		return (NULL);
	dest = NULL;
	bytesread = 1;
	while (bytesread > 0)
	{
		/* create buffer to store data frm read */
		if (!buffer)
		{
			buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
			bytesread = read(fd, buffer, BUFFER_SIZE);
		}
		while (*buffer && *buffer != '\n')
			dest = ft_charjoin(dest, *buffer++);
		if (*buffer == '\n')
		{
			dest = ft_charjoin(dest, *buffer++);
			break ;
		}
		if (!*buffer)
			buffer = NULL;
	}
	free(dest);
	return(dest);
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
malloc and returns the line that's read
returned line should include \n
if nothing to read or error, return NULL

| about read() |
read() returns num of bytes read
on error read() return -1
when nothing to read, read() returns 0

read() stores data read in 'buffer',
BUFFER_SIZE defines how many bytes to read
*/
