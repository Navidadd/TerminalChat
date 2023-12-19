#include <stdio.h>
#include <stdlib.h>
#include <libssh/libssh.h>

int main() {
    ssh_session session = ssh_new();
    if (session == NULL) {
        fprintf(stderr, "Error creando la sesión SSH\n");
        return -1;
    }

    ssh_options_set(session, SSH_OPTIONS_HOST, "...");
    ssh_options_set(session, SSH_OPTIONS_USER, "Ian");

    // Conectar a la sesión SSH
    if (ssh_connect(session) != SSH_OK) {
        fprintf(stderr, "Error conectando a la sesión SSH: %s\n", ssh_get_error(session));
        ssh_free(session);
        return -1;
    }

    // Autenticar la sesión SSH (por ejemplo, usando contraseña)
    if (ssh_userauth_password(session, NULL, "...") != SSH_AUTH_SUCCESS) {
        fprintf(stderr, "Error de autenticación: %s\n", ssh_get_error(session));
        ssh_disconnect(session);
        ssh_free(session);
        return -1;
    }

    // Ejecutar algún comando remoto (puedes cambiar "ls" por el comando que desees)
    ssh_channel channel = ssh_channel_new(session);
    if (channel == NULL) {
        fprintf(stderr, "Error creando el canal SSH\n");
        ssh_disconnect(session);
        ssh_free(session);
        return -1;
    }

    if (ssh_channel_open_session(channel) != SSH_OK) {
        fprintf(stderr, "Error abriendo la sesión SSH: %s\n", ssh_get_error(session));
        ssh_channel_free(channel);
        ssh_disconnect(session);
        ssh_free(session);
        return -1;
    }

    // Ejecutar el comando remoto
    if (ssh_channel_request_exec(channel, "mkdir extraterrestre") != SSH_OK) {
        fprintf(stderr, "Error ejecutando el comando remoto: %s\n", ssh_get_error(session));
        ssh_channel_close(channel);
        ssh_channel_free(channel);
        ssh_disconnect(session);
        ssh_free(session);
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
    ssh_disconnect(session);
    ssh_free(session);

    return 0;
}
