#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

void loadDocuments(TreeMap* tree, const char* fileNames) {
    char* token = strtok(fileNames, " ");
    while (token != NULL) {
        // Aquí puedes abrir y leer el contenido del archivo con el nombre en 'token'
        // Luego, insertar el contenido en el TreeMap utilizando insertTreeMap
        // Ejemplo:
        FILE* file = fopen(token, "r");
        if (file) {
            char line[256];
            while (fgets(line, sizeof(line), file)) {
                // Inserta cada línea en el TreeMap
                insertTreeMap(tree, strdup(token), strdup(line));
            }
            fclose(file);
        }
        token = strtok(NULL, " ");
    }
}
int lower_than_string(void* key1, void* key2){
  char* k1=(char*) key1;
  char* k2=(char*) key2;
  if(strcmp(k1,k2)<0) return 1;
  return 0;
}

int main() {
    TreeMap* documentTree = createTreeMap(lower_than_string);

    printf("Ingrese nombres de archivos txt separados por espacio:\n");
    char fileNames[500]; // Suponemos que el usuario no ingresará más de 500 caracteres
    fgets(fileNames, sizeof(fileNames), stdin);

    // Elimina el carácter de nueva línea del final si está presente
    size_t len = strlen(fileNames);
    if (len > 0 && fileNames[len - 1] == '\n') {
        fileNames[len - 1] = '\0';
    }

    loadDocuments(documentTree, fileNames);

    // Ahora, documentTree contiene el contenido de los archivos cargados

    // Puedes realizar operaciones adicionales en el TreeMap, como buscar o imprimir contenido
    // Ejemplo:
    Pair* first = firstTreeMap(documentTree);
    while (first) {
        printf("Archivo: %s\n%s", (char*)first->key, (char*)first->value);
        first = nextTreeMap(documentTree);
    }

    // Limpia la memoria antes de salir del programa
    // Debes liberar la memoria asignada para las claves y valores
    // y, finalmente, el TreeMap
    eraseTreeMap(documentTree, "nombre_de_archivo.txt");
    // Luego, puedes liberar la memoria de todas las claves y valores en el TreeMap y finalmente, liberar el TreeMap.
    // ... (haz lo mismo para todos los elementos en el TreeMap)
    // Finalmente, libera el TreeMap
    free(documentTree);

    return 0;
}
/*Este código crea un programa principal que solicita al usuario que ingrese los nombres de archivos de texto separados por espacios, lee el contenido de esos archivos y lo almacena en un TreeMap utilizando la función loadDocuments. Luego, muestra el contenido del TreeMap. No olvides liberar la memoria al final del programa para evitar pérdidas de memoria.*/





