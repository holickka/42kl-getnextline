#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buffer;
	static int	i;
	char		*dest;
	int			a;

	i = 0;
	a = 0;
	/* create buffer to store read data */
	buffer = (char *)ft_calloc(BUFFER_SIZE, sizeof(char));
	if (!buffer)
		return (NULL);
	bytesread = read(fd, buffer, BUFFER_SIZE);
	if (bytesread > 0)
	{
		if (buffer[i] != '\n')
			i++;
			count++;
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
	
	/*create a new file*/
	fd = open("file.txt", O_RDWR | O_CREAT, 0666);
	if (fd == -1)
		return (0);

	/*write something into file*/
	byteswrite = write(fd, data, strlen(data));
	if (byteswrite == -1)
		return (0);
	
	/*close it to reset pointer after write*/
	close(fd);

	/*open it again*/
	fd = open("file.txt", O_RDWR);

	/*try to read it*/
	bytesread = read(fd, buf, byteswrite);
	if (bytesread == -1 )
		return (0);
	buf[bytesread] = '\0';

	/*print it out*/
	printf("%s\n", buf);

//	while (get_next_line())
//		printf("%s\n", get_next_line());
}

/* read content from file to buffer */


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
