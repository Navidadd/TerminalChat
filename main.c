#include <stdio.h>
#include <stdlib.h>
#include <libssh/libssh.h>
#include "filereader.h"
#include "connection.h"

int main() {

    ssh_session sshSession = sshConnect();

    // Ejecutar algún comando remoto (puedes cambiar "ls" por el comando que desees)
    ssh_channel channel = ssh_channel_new(sshSession);
    if (channel == NULL) {
        fprintf(stderr, "Error creando el canal SSH\n");
        ssh_disconnect(sshSession);
        ssh_free(sshSession);
        return -1;
    }

    if (ssh_channel_open_session(channel) != SSH_OK) {
        fprintf(stderr, "Error abriendo la sesión SSH: %s\n", ssh_get_error(sshSession));
        ssh_channel_free(channel);
        ssh_disconnect(sshSession);
        ssh_free(sshSession);
        return -1;
    }

    // Ejecutar el comando remoto
    if (ssh_channel_request_exec(channel, "mkdir extraterrestre") != SSH_OK) {
        fprintf(stderr, "Error ejecutando el comando remoto: %s\n", ssh_get_error(sshSession));
        ssh_channel_close(channel);
        ssh_channel_free(channel);
        ssh_disconnect(sshSession);
        ssh_free(sshSession);
        return -1;
    }

    // Leer y mostrar la salida del comando remoto
    char buffer[256];
    int nbytes;
    while ((nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0)) > 0) {
        fwrite(buffer, 1, nbytes, stdout);
    }

    // Cerrar la conexión
    ssh_channel_send_eof(channel);
    ssh_channel_close(channel);
    ssh_channel_free(channel);
    ssh_disconnect(sshSession);
    ssh_free(sshSession);

    return 0;
}
