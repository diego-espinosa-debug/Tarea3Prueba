/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "treemap.h"
#define MAX 100
// la funcion imprimirInstrucciones se usara para imprimir las opciones que tendra el usuario dentro del switch
void imprimirInstrucciones(){

  printf("\n----------------------------------------------\n");
  printf("                    Menú: \n");
  printf("----------------------------------------------\n\n");
  printf("(1) Cargar documentos \n");
  printf("(2) Mostrar documentos ordenados \n");
  printf("(3) Buscar un libro por título \n");
  printf("(4) Palabras con mayor frecuencia \n");
  printf("(5) Palabras más relevantes \n");
  printf("(6) Buscar por palabra \n");
  printf("(7) Mostrar palabra en su contexto dentro del libro \n");
  printf("(0) Salir\n");
}
int lower_than_string(void* key1, void* key2){
  char* k1=(char*) key1;
  char* k2=(char*) key2;
  if(strcmp(k1,k2)<0) return 1;
  return 0;
}
int validarInstruccion(){

  char aux[10];

  while(1) { // se hace un bucle hasta que el usuario ingrese un dato entre 0 y 7
    printf("Que desea hacer: ");

    if (scanf("%7s", aux) != 1){
      printf("");
      printf("debe escribir un numero valido\n\n");
      while(getchar() != '\n');

    } else {
        int instruccion;

        if(strlen(aux) == 1 && aux[0] >= '0' && aux[0] <= '7'){
          instruccion = atoi(aux);
          while(getchar() != '\n');
          return instruccion;
        } else {
            printf("debe escribir un numero valido\n\n");  
            imprimirInstrucciones();
          while(getchar() != '\n');
      } 
    }  
  }
}

//idea de structs
Voy a escribir mis sugerencias de struct por si sirven de algo 
estructura para la informacion de un libro otra opcion 
typedef struct{
  int id;
  char titulo[1000];
  int numPalabras;
  int numCaracteres;
} Libro;

 para las palabras en un libro y su frecuencia 
 typedef struct[
   char palabra[100];
   int frecuencia;
 ] Palabra;

 un mapa para organizar las palabras de un libro y su frecuencia
 typedef struct{
  Palabra palabras[1000];
  int numPalabras;
  
 }MapaPalabras;

un mapa para los titulos para buscar los libros por titulo mas facil 

typedef struct{
  char palabra[1000];
  ListaLibros libros;
}MapaTitulos;

una lista de libros (hay que tner encuenta los 2 typedef) 
typedef struct NodoLibro{
Libro libro;
struct NodoLibro* siguiente;
} NodoLibro;

typedef struct{
  NodoLibro* cabeza(o heap lo que prefieran);
}ListaLibros;

un treemap para buscar palabras en los libros mas facil

typedef struct NodoIndice{
  char palabra[10000];
  ListaLibros libros;
  struct NodoIndice* izquierda;
  struct NodoIndice* derecha;
} NodoIndice

typedef struct{
  NodoIndice* raiz;
  NodoIndice* raiz;
} Treemap

  Esta estructura consta de tres partes clave:

  Libro: Representa un libro con su ID, título y contenido. Esto permite almacenar información detallada de cada libro.

  PalabraContexto: Representa una palabra y su contexto. Incluye la palabra en sí, un mapa de libros que contienen la palabra y una lista de posiciones en el libro donde se encuentra la palabra. Esto permite mantener información sobre las palabras y sus contextos.

  Biblioteca: La estructura principal que contiene mapas para almacenar libros por título, palabras y su contexto, y una lista de palabras comunes. Esta estructura organiza y almacena todos los datos necesarios para las funcionalidades del programa.


// Estructura para almacenar información de un libro
typedef struct {
  int id; //es el nombre del archivo + .txt
  char titulo[MAX];  // Título del libro
  int numPalabras;
  int numCaracteres;
} Libro;

const char *get_csv_field(char * tmp, int k)
{
  int open_mark = 0;
  char* ret = (char*) malloc (MAX*sizeof(char));
  int ini_i = 0, i = 0;
  int j=0;

  while(tmp[i+1]!= '\0'){
    if(tmp[i]=='\"'){
      open_mark = 1-open_mark;
      if(open_mark) ini_i = i+1;
      i++;
      continue;
    }
    if(open_mark || tmp[i] != ' '){
      if(k==j) ret[i-ini_i] = tmp[i];
      i++;
      continue;
    }
    if(tmp[i]==' '){
      if(k==j){
        ret[i-ini_i] = 0;
        return ret;
      }
      j++;
      ini_i = i+1;
    }
    i++;
  }
  if(k==j){
    ret[i-ini_i]=0;
    return ret;
  }

  return NULL;
}

void cargarDocumentos(TreeMap * map, const char* archivos)
{
  FILE * archivo = fopen(archivos, "r");
  if (archivo == NULL) {
    printf("***No se pudo abrir el archivo***\n");
    return;
  }
  char linea[MAX];
  fgets(linea, MAX, archivo);
  while (fgets(linea, MAX, archivo) != NULL)
  {
    Libro * libro = (Libro *) malloc(sizeof(Libro));
    
  }
  fclose(archivo);
  printf("***Documentos cargados***\n");
  return;
}
struct TreeNode {
    Pair* pair; //key, value
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int main(void)
{
  int instruccion;
  char entrada[1021];
  TreeMap* map = createTreeMap(lower_than_string);
  
  do{
    imprimirInstrucciones();
    instruccion = validarInstruccion();
    switch (instruccion)
    {
      case 1:
        printf("\n");
        printf("Ingrese nombres de archivos separados por espacios o el nombre de una carpeta: ");
        fgets(entrada, 1021, stdin);
        //adjunte un texto de gutenberg de ejemplo
        //separo los archivos por espacio y los guardo en el mismo mapa
        cargarDocumentos(map, entrada);
        //funcion cargarDocumentos();
        break;
      case 2:

        
        break;
      case 3:

        
        break;
      case 4:

        
        break;
      case 5:

        
        break;
      case 6:

        
        break;
      case 7:

        
        break;
    }
  }while(instruccion != 0);
  printf("\n***Programa finalizado***");
  return 0;
}

*/