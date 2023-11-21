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

/*
|notes|
to read text file pointed by file descriptor,
one line at a time(?)
malloc and returns the line that's read
if nothing to read or error, return NULL

read returns num of bytes read
else return -1
*/
