#include "get_next_line.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

/* usecase example of 'create read write open close', gnl with multiple fds */

int	main()
{
	int		fd;
	int		fd2;
	int		byteswrite;
	char	data[] = "Hello\nWorld\n\n";
	char	data2[] = "Whale\nWindy\n\n";

	/*create a new file*/
	fd = open("file.txt", O_RDWR | O_CREAT, 0666);
	fd2 = open("file2.txt", O_RDWR | O_CREAT, 0666);

	if (fd == -1 || fd2 == -1)
		return (0);

	/*write something into file*/
	byteswrite = write(fd, data, strlen(data));
	write(fd2, data2, strlen(data2));
	if (byteswrite == -1)
		return (0);

	/*close it to reset pointer after write*/
	close(fd);
	close(fd2);

	/*open it again*/
	fd = open("file.txt", O_RDWR);
	fd2 = open("file2.txt", O_RDWR);

	if (fd == -1 || fd2 == -1)
		return (0);

	/*try to read with getnextline and print by line */
	printf("Getnextline:\n");
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd2));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd2));
}
