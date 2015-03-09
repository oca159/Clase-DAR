#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>

#define BUFSZ PIPE_BUF

void err_quit(char *msg);

int main(void)
{
	
	FILE *fp; /* flujo FILE para popen */
	char *cmdstring = "cat popen.c";
	char buf[BUFSZ]; /* Buffer for "input" */

	/* Crea el conducto */
	if ((fp = popen(cmdstring, "r")) == NULL)
		err_quit("popen");

	/* Lee la salida de cmdstring */
	while(fgets(buf, BUFSZ, fp) != NULL)
		printf("%s", buf);

	/* Cierra y recoge el estado de salida */
	pclose(fp);
	exit(EXIT_SUCCESS);
}

void err_quit(char *msg){
	perror(msg);
	exit(EXIT_FAILURE);
}

