#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h>

#define MAX_SHINGLE_SIZE 3 /*potrei modificarlo a mio piacimento*/


int main() {

    /* Creo il path dove sono contenuti i D documenti da confrontare */
    char path[100];

    if (getcwd(path, sizeof(path)) == NULL) {
        perror("Errore con la getcwd()");
        return 1;
    }
    strcat(path, "/testProgramma");

    printf("\nPath della directory contente i documenti: %s\n\n", path); 


    /* Creo un array contenente tutti i path dei documenti */
    char **filePaths = NULL;
    int fileCount = 0;

    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("Errore nell'apertura della directory");
        return 1;
    }
    
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue; 
        }
        char *fullPath = malloc(strlen(path) + strlen(entry->d_name) + 2); /* +2 perchè separiamo dir e stringa d_name */
        sprintf(fullPath, "%s/%s", path, entry->d_name); /*costruisco il percorso completo in fullpath*/
        filePaths = realloc(filePaths, (fileCount + 1) * sizeof(char *)); /*RICORDATI DI FARE LA FREE*/
        filePaths[fileCount] = fullPath;
        fileCount++;

        if (filePaths == NULL || filePaths[fileCount - 1] == NULL) {
            perror("Errore nell'allocazione della memoria");
            return 1;
            }
        }

    closedir(dir);

    for(int i=0; i<fileCount; i++){   /*print di controllo*/
        printf("%s\n", filePaths[i]);
    }

    const char *documento = "Ciao sono maura e forse sono ritardata perché non so programmare.";
    int shingleSize = 3;
     /*copio documento perché token modifica la stringa originale (non servirà con i documenti aperti in lettura)*/
    char *copy = strdup(documento);
    char *token = strtok(copy, " ");

    printf("Procedo a creare shingles di lunghezza %d:\n", shingleSize);

    int count = 0;
    /*int lunghezza_token = strlen(token);*/
    //printf("%d\n", lunghezza_token);
    while (token != NULL) {
        for (int i = 0; i < shingleSize; i++) {
            int lunghezza_token = strlen(token + i);
            printf("%d\n", lunghezza_token);
            char *shingle = malloc((lunghezza_token +1)* sizeof(char));
            strcat(shingle, token + i);
            if (i < shingleSize - 1) {
                strcat(shingle, " ");
            }
            token = strtok(NULL, " ");
            printf("%d\t", shingle);
        }

        // Stampa o gestione degli shingle
        //free(shingle);
        count++;
    }

    free(copy);

    return 0;
}
