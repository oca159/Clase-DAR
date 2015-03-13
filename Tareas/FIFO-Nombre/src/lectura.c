#include <stdio.h>
#include <security/pam_appl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>

struct pam_response *reply;

int null_conv(int num_msg, const struct pam_message **msg, struct pam_response **resp, void *appdata_ptr) {

        *resp = reply;
        return PAM_SUCCESS;

}

static struct pam_conv conv = { null_conv, NULL };

int main(int argc, char *argv[]) {
        int fd; /* Descriptor del FIFO */
        int len; /* Bytes leídos del FIFO */
        char buf[PIPE_BUF];
        mode_t mode = 0666;
        if ((mkfifo("fifo1", mode)) < 0)
        {
                perror("mkfifo");
                exit(EXIT_FAILURE);
        }
        /* Apertura del FIFO de sólo lectura */
        if ((fd = open("fifo1", O_RDONLY)) < 0)
        {
                perror("open");
                exit(EXIT_FAILURE);
        }
        
        read(fd,buf,PIPE_BUF - 1);
        close(fd);
        int retval;
        char *user, *pass;   

        if(argc == 3) {

                user = argv[1];
                pass = strdup(argv[2]);

        } else { 

                fprintf(stderr, "Usage: login [username] [password]\n");
                exit(1);

        }

        return authenticate("system-auth", user, pass, buf);

}   

int authenticate(char *service, char *user, char *pass, char *buf) {

        pam_handle_t *pamh = NULL;
        int retval = pam_start(service, user, &conv, &pamh);

        if (retval == PAM_SUCCESS) {

                reply = (struct pam_response *)malloc(sizeof(struct pam_response));
                reply[0].resp = pass;
                reply[0].resp_retcode = 0;

                retval = pam_authenticate(pamh, 0);
                if (retval == PAM_SUCCESS && !strcmp(buf,"D90D-7715\n"))
                        fprintf(stdout, "Authenticated\n");

                else
                        fprintf(stdout, "Not Authenticated\n");

                pam_end(pamh, PAM_SUCCESS);

                return ( retval == PAM_SUCCESS ? 0:1 );

        }

        return ( retval == PAM_SUCCESS ? 0:1 );
}

