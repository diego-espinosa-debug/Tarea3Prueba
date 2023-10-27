/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "treemap.h"

// Estructura para representar un Documentoo
typedef struct Documento {
  char titulo[100];
  char* contenido;
  int totalPalabras;
  int totalCaracteres;
} Documento;

// Función para crear un Documento
Documento* crearDocumento(const char* titulo, const char* contenido) {
  Documento* doc = (Documento*)malloc(sizeof(Documento));
  strcpy(doc->titulo, titulo);
  doc->contenido = strdup(contenido);
  // Calcular la cantidad de palabras y caracteres
  doc->totalPalabras = 0;
  doc->totalCaracteres = 0;
  char* token = strtok(doc->contenido, " ");
  while (token != NULL) {
    doc->totalPalabras++;
    doc->totalCaracteres += strlen(token);
    token = strtok(NULL, " ");
  }
  return doc;
}

// Función para cargar un Documentoo desde un archivo
Documento* loadDocumento(const char* file_name) {
  FILE* file = fopen(file_name, "r");
  if (file == NULL) {
      printf("No se pudo abrir el archivo %s\n", file_name);
      return NULL;
  }
  char titulo[100];
  fgets(titulo, sizeof(titulo), file);
  char contenido[1000];
  char* line;
  strcpy(contenido, "");
  while ((line = fgets(contenido, sizeof(contenido), file)) != NULL) {
      strcat(contenido, line);
  }
  fclose(file);
  return crearDocumento(titulo, contenido);
}

int lower_than_string(void* key1, void* key2) {
  char* k1 = (char*)key1;
  char* k2 = (char*)key2;
  if (strcmp(k1, k2) < 0) return 1;
  return 0;
}

void loadDocumentosFromFolder(TreeMap* tree, const char* folder_path) {
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
      Documento* doc = loadDocumento(file_path);
      if (doc) {
        insertTreeMap(tree, doc->titulo, doc);
        }
    }
  }
  closedir(dir);
}

void showDocumentos(TreeMap* DocumentoIndex) {
  printf("Documentoos ordenados por título:\n");
  Pair* aux = firstTreeMap(DocumentoIndex);
  while (aux != NULL) {
    Documento* doc = (Documento*)aux->value;
    printf("ID: %s\nTítulo: %s\nPalabras: %d\nCaracteres: %d\n",(char*)aux->key, doc->titulo, doc->totalPalabras, doc->totalCaracteres);
    aux = nextTreeMap(DocumentoIndex);
  }
}

int main() {
  TreeMap* DocumentoIndex = createTreeMap(lower_than_string);
  char entrada[1024];
  int option;

  while (1) {
    printf("Menú:\n");
    printf("1. Cargar Documentoos\n");
    printf("2. Mostrar Documentoos ordenados\n");
    printf("0. Salir\n");
    printf("Seleccione una opción: ");
    scanf("%d", &option);
    while (getchar() != '\n'); // Limpiar el búfer del teclado

    switch (option) {
        case 1:
          printf("Ingrese nombres de archivos separados por espacios o el nombre de una carpeta: ");
          fgets(entrada, sizeof(entrada), stdin);
          if (entrada[strlen(entrada) - 1] == '\n') {
            entrada[strlen(entrada) - 1] = '\0';
          }
          if (opendir(entrada)) {
            loadDocumentosFromFolder(DocumentoIndex, entrada);
            printf("Documentoos cargados desde la carpeta %s.\n");
          } else {
            char* token = strtok(entrada, " ");
            while (token != NULL) {
              Documento* doc = loadDocumento(token);
              if (doc) {
                  insertTreeMap(DocumentoIndex, doc->titulo, doc);
              }
              token = strtok(NULL, " ");
            }
              printf("Documentoos cargados desde archivos individuales.\n");
          }
          break;
        case 2:
          showDocumentos(DocumentoIndex);
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
*/