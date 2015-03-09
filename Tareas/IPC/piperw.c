#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>

#define BUFSZ PIPE_BUF

void err_quit(char *msg);

int main(int argc, char const *argv[])
{
	
	int fd[2]; /* Matriz de descriptores de archivos del conducto */
	int fdin; /* Descriptor para el archivo de entrada */
	char buf[BUFSZ];
	int pid, len;
	
	/* Crea el conducto */
	if ((pipe(fd)) < 0)
		err_quit("pipe");
	/* Hace fork y cierra los descriptores apropiados */
	if ((pid = fork()) < 0)
		err_quit("fork");
	if (pid == 0)
	{
		/* El hijo es el lector, cerramos el descriptor de escritura */
		close(fd[1]);
		while((len = read(fd[0], buf, BUFSZ)) > 0)
			write(STDOUT_FILENO, buf, len);
		close(fd[0]);
	}
	else
	{
		/* El padre es el escritor, cerramos el descriptor de lectura */
		close(fd[0]);
		if ((fdin = open(argv[1], O_RDONLY)) < 0)
		{
			perror("open");
			/* Enviamos algo ya que no podemos abrir la entrada */
			write(fd[1], "123\n", 4);
		}
		else
		{
			while((len = read(fdin, buf, BUFSZ)) > 0)
				write(fd[1],buf,len);
			close(fdin);
		}
		/* Cerramos el descriptor de escritura */
		close(fd[1]);
	}
	/* Recogemos el estado de la salida */
	waitpid(pid, NULL, 0);
	exit(EXIT_SUCCESS);
}

void err_quit(char *msg){
	perror(msg);
	exit(EXIT_FAILURE);
}

