#include "filereader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

credentials* getCredentials(const char* file) {
    FILE* fp = fopen(file, "r");
    if (fp == NULL) {
       fprintf(stderr, "Error al abrir el archivo\n");
        return NULL;
    }

    credentials* datos = malloc(sizeof(credentials));

 //   if (fscanf(fp, "ip:%49s\nnombre:%49s\npassword:%49s",datos->ip, datos->username, datos->password) != 3) {
 //       fprintf(stderr, "Error al leer el archivo\n");
 //       free(datos);
 //       fclose(fp);
 //       return NULL;
 //   }

    int result = fscanf(fp, "ip:%49[^\n]\nusername:%49[^\n]\npassword:%49[^\n]%*1[\n]", datos->ip, datos->username, datos->password);
    if (result != 3) {
        fprintf(stderr, "Error al leer el archivo. Resultado: %d\n", result);
        free(datos);
        fclose(fp);
        return NULL;
    }

    fclose(fp);
    return datos;
}


