#include<stdio.h>
#include<stdlib.h>
#include<libssh/libssh.h>
#include"filereader.h"

ssh_session sshConnect(){

    credentials* userCredentials = getCredentials("credentials.txt");
    if (userCredentials == NULL) {
        fprintf(stderr, "Error al obtener las credenciales\n");
        return NULL;
    }

    ssh_session session = ssh_new();
    if (session == NULL) {
        fprintf(stderr, "Error creando la sesión SSH\n");
        return NULL;
    }

    ssh_options_set(session, SSH_OPTIONS_HOST, userCredentials->ip);
    ssh_options_set(session, SSH_OPTIONS_USER, userCredentials->username);

    // Conectar a la sesión SSH
    if (ssh_connect(session) != SSH_OK) {
        fprintf(stderr, "Error conectando a la sesión SSH: %s\n", ssh_get_error(session));
        ssh_free(session);
        return NULL;
    }

    // Autenticar la sesión SSH (por ejemplo, usando contraseña)
    if (ssh_userauth_password(session, NULL, userCredentials->password) != SSH_AUTH_SUCCESS) {
        fprintf(stderr, "Error de autenticación: %s\n", ssh_get_error(session));
        ssh_disconnect(session);
        ssh_free(session);
        return NULL;
    }


return session;
}
