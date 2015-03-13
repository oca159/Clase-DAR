#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
 
using namespace std;
 
int main() {
    FILE *in;
    char buff[512];
    char buf[PIPE_BUF]; /* Se asegura de escrituras atómicas */
 
    if(!(in = popen("sudo lsblk -o UUID -f | grep sdb | cut -c1-9 | tail -n 1", "r"))){
        return 1;
    }
 
	fgets(buff, sizeof(buff), in);
    pclose(in);

    int fd; /* Descriptor del FIFO */
    int len; /* Bytes leídos del FIFO */

    /* Abre el FIFO de sólo escritura */
    if ((fd = open("fifo1", O_WRONLY)) < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    /* Genera algunos datos para escribir */
    /* Crea la cadena para escribir */
            
    len = sprintf(buf, "%s", buff);
    /* Utiliza (len + 1) porque sprintf no cuenta  el null final*/
    if ((write(fd, buf, len + 1)) < 0)
    {
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);
    exit(EXIT_SUCCESS);
    return 0;
}