#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
int open_port(void)
{
	int fd;                                   /* File descriptor for the port */

	fd = open("/dev/cu.usbmodem1421", O_RDWR | O_NOCTTY | O_NDELAY);
	if (fd > 0)
	{
		printf("It works !");
	}
	else
	{
		printf("You lose !");
	}
	return (fd);
}

char read_myo_data(char *raw_data)
{
	if (raw_data[0] == '1')
		return (1);
	else if (raw_data[0] == '2')
		return (2);
	else if (raw_data[0] == '3')
		return (3);
	else if (raw_data[0] == '4')
		return (4);
	else if (raw_data[0] == '5')
		return (5);
	else if (raw_data[0] == '6')
		return (6);
	return (7);
}

int send_to_arduino(char *buf, int fd)
{
	char		byte;

	byte = read_myo_data(buf);
	write(fd, &byte, 1);
	return (0);
}

int main(int ac, char **av)
{
	int fd2;
	char buf[512];
	int ret;

	
	fd2 = open_port();
	while (1)
	{
		ret = read(0, buf, 512);
		buf[ret] = 0;
		printf("%s",buf);
		send_to_arduino(buf, fd2);
	}
	return (0);
}
