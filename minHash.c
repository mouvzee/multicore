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
    

    FILE *file;
    char ***shingles = NULL;
    char *doc = NULL;
    int numFile = 0;

    for(int i=0; i<fileCount; i++){

        file = fopen(filePaths[i], "r");
        printf("%s\n", filePaths[i]);
        if (file == NULL) {
            fprintf(stderr, "Impossibile aprire il file.\n");
            return 1;
        }

        fseek(file, 0, SEEK_END);  // Sposta il cursore alla fine del file
        size_t fileLength = ftell(file);  // Ottieni la posizione corrente del cursore (quindi la lunghezza del file)
        rewind(file);  // Riporta il cursore all'inizio del file

        doc = malloc(fileLength * sizeof(char));
        if (doc == NULL) {
            fprintf(stderr, "Errore durante l'allocazione di memoria per il documento.\n");
            return 1;
        }

        size_t bytesRead = fread(doc, sizeof(char), fileLength, file);

        shingles = realloc(shingles, (numFile + 1) * sizeof(char **));
        shingles[numFile] = malloc((fileLength - MAX_SHINGLE_SIZE + 1)  * sizeof(char *));

        char *token = strtok(doc, " ");
        int index = 0;
        while (token != NULL) {
            shingles[numFile][index] = malloc((strlen(token) + 1) * sizeof(char));
            strcpy(shingles[numFile][index], token);
            index++;
            token = strtok(NULL, " ");

            printf("%d\t%d\n", numFile, index);
        }

        numFile++;
        fclose(file);
    }



    return 0;
}
