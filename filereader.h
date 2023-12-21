#ifndef FILEREADER_H
#define FILEREADER_H

typedef struct {
    char ip[50];
    char username[50];
    char password[50];
} credentials;

credentials* getCredentials(const char* file);

#endif
