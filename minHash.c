#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h>




int main() {

    /* Ricavo il path dove sono contenuti i D documenti da confrontare */
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
        filePaths = realloc(filePaths, (fileCount + 1) * sizeof(char *));
        filePaths[fileCount] = fullPath;
        fileCount++;

        if (filePaths == NULL || filePaths[fileCount - 1] == NULL) {
            perror("Errore nell'allocazione della memoria");
            return 1;
            }
        }

    closedir(dir);

    for(int i=0; i<fileCount; i++){
        printf("%s\n", filePaths[i]);
    }

    return 0;
 }

