#include <stdio.h>
#include <stdlib.h>

char** getCredentials(){
    FILE *credentials;
    char ip[50], username[50], password[50];
    char** info = malloc(3 * sizeof(char*)); 

    credentials = fopen("credentials.txt", "r");

    if(credentials == NULL){
        fprintf(stderr, "Error en el archivo Credentials");
        return NULL;
    }

    for (int i = 0; i < 3; ++i) {
        info[i] = malloc(50 * sizeof(char));
        if (info[i] == NULL) {
            fprintf(stderr, "Error de asignación de memoria\n");
            fclose(credentials);
            for (int j = 0; j < i; ++j) {
                free(info[j]);
            }
            free(info);
            return NULL;
        }
    }

    if(fscanf(credentials, "ip:%s\nusername:%s\npassword:%s", ip, username, password) != 3){
        fprintf(stderr, "Error al leer el archivo\n");
        fclose(credentials);
        for(int i = 0; i < 3;++i){
            free(info[i]);
        }
        return NULL;
    }
    
    fclose(credentials);
    info[0] = ip;
    info[1] = username;
    info[3] = password;

    return info;
}
