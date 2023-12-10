#include "get_next_line.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

/* usecase example of 'create read write open close' */

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
	if (fd == -1)
		return (0);

	/*try to read it*/
	bytesread = read(fd, buf, byteswrite);
	if (bytesread == -1 )
		return (0);
	buf[bytesread] = '\0';

	/*print it out*/
	printf("%s\n", buf);
}
