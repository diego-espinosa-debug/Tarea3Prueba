#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "treemap.h"

// Estructura para representar un documento
typedef struct Document {
  char title[100];
  char* content;
  int word_count;
  int char_count;
} Document;

// Función para crear un Document
Document* createDocument(const char* title, const char* content) {
  Document* doc = (Document*)malloc(sizeof(Document));
  strcpy(doc->title, title);
  doc->content = strdup(content);
  // Calcular la cantidad de palabras y caracteres
  doc->word_count = 0;
  doc->char_count = 0;
  char* token = strtok(doc->content, " ");
  while (token != NULL) {
    doc->word_count++;
    doc->char_count += strlen(token);
    token = strtok(NULL, " ");
  }
  return doc;
}

// Función para cargar un documento desde un archivo
Document* loadDocument(const char* file_name) {
  FILE* file = fopen(file_name, "r");
  if (file == NULL) {
      printf("No se pudo abrir el archivo %s\n", file_name);
      return NULL;
  }
  char title[100];
  fgets(title, sizeof(title), file);
  char content[1000];
  char* line;
  strcpy(content, "");
  while ((line = fgets(content, sizeof(content), file)) != NULL) {
      strcat(content, line);
  }
  fclose(file);
  return createDocument(title, content);
}

int lower_than_string(void* key1, void* key2) {
  char* k1 = (char*)key1;
  char* k2 = (char*)key2;
  if (strcmp(k1, k2) < 0) return 1;
  return 0;
}

void loadDocumentsFromFolder(TreeMap* tree, const char* folder_path) {
  DIR* dir;
  struct dirent* entry;
  dir = opendir(folder_path);
  if (dir == NULL) {
    printf("No se pudo abrir la carpeta %s\n", folder_path);
    return;
  }
  while ((entry = readdir(dir))) {
    if (entry->d_type == DT_REG) {
      char file_path[1024];
      sprintf(file_path, "%s/%s", folder_path, entry->d_name);
      Document* doc = loadDocument(file_path);
      if (doc) {
        insertTreeMap(tree, doc->title, doc);
        }
    }
  }
  closedir(dir);
}

void showDocuments(TreeMap* documentIndex) {
  printf("Documentos ordenados por título:\n");
  Pair* aux = firstTreeMap(documentIndex);
  while (aux != NULL) {
    Document* doc = (Document*)aux->value;
    printf("ID: %s\nTítulo: %s\nPalabras: %d\nCaracteres: %d\n",(char*)aux->key, doc->title, doc->word_count, doc->char_count);
    aux = nextTreeMap(documentIndex);
  }
}

int main() {
  TreeMap* documentIndex = createTreeMap(lower_than_string);
  char input[1024];
  int option;

  while (1) {
    printf("Menú:\n");
    printf("1. Cargar documentos\n");
    printf("2. Mostrar documentos ordenados\n");
    printf("0. Salir\n");
    printf("Seleccione una opción: ");
    scanf("%d", &option);
    while (getchar() != '\n'); // Limpiar el búfer del teclado

    switch (option) {
        case 1:
          printf("Ingrese nombres de archivos separados por espacios o el nombre de una carpeta: ");
          fgets(input, sizeof(input), stdin);
          if (input[strlen(input) - 1] == '\n') {
            input[strlen(input) - 1] = '\0';
          }
          if (opendir(input)) {
            loadDocumentsFromFolder(documentIndex, input);
            printf("Documentos cargados desde la carpeta %s.\n");
          } else {
            char* token = strtok(input, " ");
            while (token != NULL) {
              Document* doc = loadDocument(token);
              if (doc) {
                  insertTreeMap(documentIndex, doc->title, doc);
              }
              token = strtok(NULL, " ");
            }
              printf("Documentos cargados desde archivos individuales.\n");
          }
          break;
        case 2:
          showDocuments(documentIndex);
          break;
        case 0:
            return 0;
        default:
            printf("Opción no válida. Intente de nuevo.\n");
            break;
    }
  }

  return 0;
}