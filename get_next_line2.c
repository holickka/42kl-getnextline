#include "get_next_line.h"

char	*get_next_line(int fd)
{

	buffer = (char *)ft_calloc(BUFFER_SIZE, sizeof(char));
	if (!buffer)
		return (NULL);
	/* read content from file to buffer */
	bytesread = read(fd, buffer, BUFFER_SIZE);
	if (bytesread > 0)
		return (buffer)

	return (NULL);
}

int	main()
{
	int	fd;

	char	data[] = "Hello\nWorld";

	fd = open("file.txt", O_RDWR | O_CREAT);
	if (fd == -1)
		return (0);

	if (write(fd, data, strlen(data)) == -1)
		return (0);

	while (get_next_line())
		printf("%s\n", get_next_line());
	return (0);
}

/*
|notes|
to read text file pointed by file descriptor,
one line at a time(?)
malloc and returns the line that's read
if nothing to read or error, return NULL

read returns num of bytes read
else return -1
*/
