#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <time.h>

int main(void)
{
	int fd; /* Descriptor del FIFO */
	int len; /* Bytes leídos del FIFO */
	char buf[PIPE_BUF]; /* Se asegura de escrituras atómicas */
	time_t tp;

	/* Nos identificamos */
	printf("I am %d\n", getpid());

	/* Abre el FIFO de sólo escritura */
	if ((fd = open("fifo1", O_WRONLY)) < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}

	/* Genera algunos datos para escribir */
	while(1)
	{
		/* Obtiene la hora actual */
		time(&tp);

		/* Crea la cadena para escribir */
		len = sprintf(buf, "wrfifo %d sends %s", getpid(), ctime(&tp));
		/* Utiliza (len + 1) porque sprintf no cuenta  el null final*/
		if ((write(fd, buf, len + 1)) < 0)
		{
			perror("write");
			close(fd);
			exit(EXIT_FAILURE);
		}
		sleep(3);
	}
	close(fd);
	exit(EXIT_SUCCESS);
}
