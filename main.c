#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include "treemap.h"
#include "list.h"
#define MAX 100
// la funcion imprimirInstrucciones se usara para imprimir las opciones que tendra el usuario dentro del switch

typedef struct{
  char palabra[1000];
  int frecuencia;
} Palabra;

typedef struct{
  char id[100];
  char titulo[1000];
  int numCaracteres;
  int numPalabras;
  Palabra *palabrasXlibro; // arreglo de palabras en el libro para contar su frecuencia
} Libro;

void imprimirInstrucciones();
int lower_than_string(void* , void* );
int validarInstruccion();

int cargarArchivo(const char * nombreArchivo, TreeMap * mapaXtitulo, TreeMap * mapaXid)
{  
  FILE * archivo = fopen(nombreArchivo, "r");
  if(archivo == NULL) return 1;
  
  char linea[1000];
  char titulo[1000] = ""; // Inicializamos el título vacío
    // Leer el título del libro y omitir la parte no deseada
  while(fgets(linea, sizeof(linea), archivo)){
    if(strstr(linea, "﻿The Project Gutenberg eBook of ")!= NULL) break; // Se encontró la parte no deseada, se detiene la búsqueda
    strcat(titulo, linea);// Concatenar la línea actual al título
    if(strcmp(linea, "\n") == 0)break;// Comprobar si hemos llegado al final del título
  }
  // Dividir la línea en palabras asi contar hasta 5, que serian "The Project Gutenberg eBook of"
  char *palabra = strtok(linea, " ");
  int palabrasContadas = 0; 

  while(palabra != NULL){// Recorrer cada palabra en la línea
      palabrasContadas++; 
      if(palabrasContadas > 5){//si hemos contado las 5 palabras
          strcat(titulo, palabra);//Concatenar la palabra actual al título
          strcat(titulo, " "); //Agregar un espacio entre las palabras
      }
      // Obtener la siguiente palabra en la línea
      palabra = strtok(NULL, " ");
  }
  
  Libro *libro = (Libro *)malloc(sizeof(Libro));
  strcpy(libro->id, nombreArchivo);
  libro->numPalabras = 0;
  libro->numCaracteres = 0;
  strcpy(libro->titulo, titulo);
  printf("Titulo: %s\n", libro->titulo);
  
  libro->palabrasXlibro = (Palabra *)malloc(MAX * sizeof(Palabra));
  bool leyendoTexto = false; // Variable para rastrear si estamos leyendo el texto, comienza en falso asumiendo que no estamos leyendo el texto
  
//******************hasta aqui esta perfecto**************************

  while (fgets(linea, sizeof(linea), archivo)) {
      if (strstr(linea, "*** START") != NULL) {
          // Encontramos la línea que marca el inicio del texto
          leyendoTexto = true; // Comenzar a leer el texto
          continue; // Saltar esta línea
      }

    //aqui empezamos a leer el texto
      if(leyendoTexto){
          //contar palabras
          char *palabra = strtok(linea, " ");
          while(palabra != NULL){
            libro->numPalabras++;
            //contar caracteres
            libro->numCaracteres += strlen(palabra);
            palabra = strtok(NULL, " ");
          }/*
            //agregar palabras al mapa
            if(searchTreeMap(mapaXtitulo, titulo) == NULL){
              //si no existe el titulo en el mapa
              libro->palabrasXlibro[libro->numPalabras-1].frecuencia = 1;
              strcpy(libro->palabrasXlibro[libro->numPalabras-1].palabra, palabra);
              //insertTreeMap(mapaXtitulo, titulo, libro->palabrasXlibro[libro->numPalabras-1]);
            }else{
              //si existe el titulo en el mapa
              PairTree *pair = searchTreeMap(mapaXtitulo, titulo);
              Palabra * palabraEncontrada = pair->value;
              palabraEncontrada->frecuencia++;
              strcpy(palabraEncontrada->palabra, palabra);
              //insertTreeMap(mapaXtitulo, titulo, palabraEncontrada);
            }
*/
          if (strstr(linea, "*** END") != NULL) {
              // Encontramos la línea que marca el final del texto
              break; // Terminar la lectura
          }
      }
  }// Una vez que hayas procesado el título, puedes continuar desde donde se detuvo
  printf("Numero de palabras: %d\n", libro->numPalabras);
  printf("Numero de caracteres: %d\n", libro->numCaracteres);
  
  // Un mapa para realizar un seguimiento de la frecuencia de las palabras
  /*TreeMap *frecuenciaPalabras = createTreeMap(lower_than_string);
  printf("token: %s\n", libro->titulo);
  int i = 0;
  while(fgets(linea, sizeof(linea), archivo)){ // leemos el archivo linea por linea
    char *token = strtok(linea, " "); // dividimos la linea en tokens
    //printf("token: %s\n", token);
    //si token lee espacios strcmp(token, " ")!=0
    while(token != NULL && libro->numPalabras < 1000){
      libro->numPalabras++;
      libro->numCaracteres+= strlen(token);
      strcpy(libro->palabrasXlibro->palabra,token);
      // Buscar si la palabra ya existe en el mapa de frecuencias
      PairTree *par = searchTreeMap(frecuenciaPalabras, token); // buscamos la palabra en el mapa de frecuencias
      if (par != NULL) {
        // La palabra ya existe, incrementa su frecuencia
        Palabra *palabraExistente = par->value;
        palabraExistente->frecuencia++;
      }else{
          // La palabra no existe, la agregamos al mapa de frecuencias
          Palabra nuevaPalabra;
          strcpy(nuevaPalabra.palabra, token);
          nuevaPalabra.frecuencia = 1;
          insertTreeMap(frecuenciaPalabras, nuevaPalabra.palabra, &nuevaPalabra);
      }
      // Copiar la palabra en el arreglo de palabras del libro
      strcpy(libro->palabrasXlibro[i].palabra, token);

      token = strtok(NULL, " ");
      i++;

      //printf("token: %s\n", tituloPerLibro);

      
    }
  }*/
  // Insertar el libro en el mapaXtitulo y mapaXid (debes implementar esto)
  //insertTreeMap(mapaXtitulo, libro->titulo, libro);
  //insertTreeMap(mapaXid, &(libro->id), libro);
  
  free(libro);
  free(libro->palabrasXlibro);
  //free(frecuenciaPalabras);
  fclose(archivo);
  return 0;
}

void cargarDocumentos(TreeMap * mapaXtitulo, TreeMap * mapaXid)
{
  char entrada[1021]; // entrada de usuario
  printf("\n Ingrese nombres de archivos separados por espacios o el nombre de una carpeta: ");
  fgets(entrada, sizeof(entrada), stdin);

  char* nombreArchivo = strtok(entrada, " \n"); // separar los archivos por el espacio

  while(nombreArchivo != NULL){ // ciclo para recorrer los archivos
    char* fin= nombreArchivo + strlen(nombreArchivo)-1;
    while(fin > nombreArchivo && isspace((unsigned char)*fin)){
      fin--;
    }
    fin[1] = '\0';
    
    if (cargarArchivo(nombreArchivo, mapaXtitulo, mapaXid) != 0) {
      printf("Error al cargar el archivo: %s\n", nombreArchivo);
    }
    
    nombreArchivo= strtok(NULL, "\n");
  }
}

//funcion lista segun lo que dice el readme, comprobar uso
void DocOrdenados(TreeMap * map) //con mapa arbol porque esta ordenado por titulo
{
  if(map == NULL){ // verificar si el mapa esta vacio
    printf("No hay archivos cargados\n");
    exit(EXIT_FAILURE);
  }
  
  PairTree * par= firstTreeMap(map); // primer par
  while(par != NULL){ // ciclo para recorrer los archivos
    char *titulo = par->key; // titulo del libro
    Libro *libro = par->value; // contenido del strcut libro
    printf("Libro: %s\n", titulo); 
    printf("Id: %d\n", libro->id);
    printf("Palabras: %d\n", libro->numPalabras);
    printf("Caracteres: %d\n", libro->numCaracteres);
    par = nextTreeMap(map); // siguiente par
  }
}

//prototipo funcion lista, falta mejorar
/*void busquedaDeLibro(TreeMap * mapaXtitulo)
{
  char palabrasBuscar[1000];
  printf("Ingrese el titulo que desee buscar: \n");
  fgets(palabrasBuscar, sizeof(palabrasBuscar), stdin);
  palabrasBuscar[strcspn(palabrasBuscar, "\n")] = '\0';
  printf("Palabras buscadas: %s\n", palabrasBuscar);
  char *token = strtok(palabrasBuscar, " ");
  List * listaDeLibros = createList();
  
  while(token!=NULL){
    printf("token: %s\n", token);
    PairTree * par = searchTreeMap(mapaXtitulo, token);
    printf("par: %p\n", par);
    if(par == NULL){ //si no encuentra la palabra se descartan todos los libros
      printf("No se encontro el libro\n");
      free(listaDeLibros);
      return;
    }else{
      //guardar los libros q contienen esa palabra en una lista
      //si existe el libro en el arbol, buscar todos los libros desde el inicio del arbol
      PairTree * par = firstTreeMap(mapaXtitulo); // primer par
      while(par != NULL){
        Libro *libro = par->key; // titulo del libro
        if(strcmp(libro->titulo, token) == 0){ // comprobar si el libro tiene esa palabra
          pushBack(listaDeLibros, libro);// guardar libro en lista
        }
        par = nextTreeMap(mapaXtitulo);// siguiente par
      }
    }
    char *token = strtok(palabrasBuscar, " ");// obtener palabra siguiente
  }
  //si se encuentra entonces se muestra el libro
  Libro *libro = firstList(listaDeLibros);
  while(libro != NULL){
    printf("Libro: %s\n", libro->titulo);
    libro = nextList(listaDeLibros);
  }
  return;
}
*/

void palabrasConMayorFrecuencia(TreeMap * mapaXid, List * bloqueo){
  int idLibro;
  printf("Ingrese el ID del libro\n");
  scanf("%d", &idLibro);
  getchar();//podrias ser while(getchar() != '\n'); y en todo getchar po si acaso 
  PairTree * par = searchTreeMap(mapaXid, &idLibro);
  if(par == NULL){
    printf("No se ha encontrado el Libro.\n");
    return;
  }
  Libro *libro = par->value;

  //formula frecuencia es:
  //  veces que aparece p en d             numero de documentos
  //(--------------------------) * log(----------------------------------)
  //  numero de palabras en d           num de docs q tienen la palabra p 

  
  
}

void palabraContexto(){
  char nombreArchivoProv[100]; //uso provicional para funcion
  strcpy(nombreArchivoProv, "10.txt");
  FILE * archivoProv = fopen(nombreArchivoProv, "r");
  if(archivoProv == NULL) return; 
  
  char palabraBuscada[100];
  printf("Ingrese la palabra que desea buscar: \n");
  scanf("%s", palabraBuscada);
  char lineaProv[100];
  while(fgets(lineaProv, sizeof(lineaProv), archivoProv)){
    char *palabraText = strtok(lineaProv, " \t\n");
    while(palabraText != NULL){
      palabraText = strtok(lineaProv, " \t\n");
      if(strcmp(palabraText,palabraBuscada) == 0){
        printf("El contecto de la palabra buscada es: %s\n", lineaProv);
        fclose(archivoProv);
        return;
      }
    }
  } 
  printf("no se encontro la palabre buscada\n");
  fclose(archivoProv);
}

/*
void palabraRelevante(TreeMap *mapaXtitulo, TreeMap *mapaXid){
  char tituloLibro[1000];
  printf("Ingrese el titulo del libro: \n");
  fgets(tituloLibro, sizeof(tituloLibro), stdin);
  tituloLibro[strcspn(tituloLibro, "\n")] = '\0';
  for(int i = 0; tituloLibro[i]; i++){ // colocamos el titulo en minuscula para poder buscar sin importar las mayusculas 
    tituloLibro[i] = tolower(tituloLibro[i]);
  }

  PairTree * par = searchTreeMap(mapaXtitulo, tituloLibro);
  if( par == NULL) { // buscamos el libro por el titulo en mapaXtitulo
    printf("No se ha encontrado el libro.\n");   // no se encontro salimos de la funcion 
    return;
  }
  Libro *libro = par->value;
  int numDocumentos = 0;
  for ( int i = 0; i < libro->numPalabras; i++){
    Palabra * palabra = &libro->palabrasXlibro[i];
    double tf = (double)palabra->frecuencia / libro->numPalabras; // se calcula el tf
    int numDocumentosConPalabras = 0;

    firstTreeMap(mapaXid);// se inicia la busqueda en mapaXid
    while(nextTreeMap(mapaXid) != NULL){ // se recorren todos los libros en mapaXid
      Libro *otroLibro = mapaXid->current->pairTree->value;
      for(int j = 0; j < otroLibro->numPalabras; j++){ // se cuenta cuantos los libros tienen la palabra
        if(strcmp(otroLibro->palabrasXlibro[j].palabra, palabra->palabra) == 0){
          numDocumentosConPalabras++;
          break; 
        }
      }
    }
    double idf = log((double)numDocumentos / numDocumentosConPalabras); // se calcula el idf
    double tfidf = tf * idf; //calcula el tf-idf
    palabra->frecuencia = tfidf;
    //se almacena el valor tf-idf en la struct palabra
  }
  for(int i = 0; i < libro->numPalabras - 1; i++){
    for(int j = i+1; j < libro->numPalabras; j++){ // se ordenan las palabras por relevancia(tf-idf)
      if(libro->palabrasXlibro[j].frecuencia > libro->palabrasXlibro[i].frecuencia){
        Palabra aux = libro->palabrasXlibro[i];
        libro->palabrasXlibro[i] = libro->palabrasXlibro[j];
        libro->palabrasXlibro[j] = aux;

      }
    }
  }
  printf("Las palabras mas relevantes son: \n");
  for(int i = 0; i < 10 && i < libro->numPalabras; i++){
    printf("%s (frecuencia: %lf)\n", libro-palabrasXlibro[i].palabra, libro->palabrasXlibro[i].frecuencia);
  }
  return; // al llegar aca se deberian mostrar las 10 palabras mas relevantes
}
*/
int main()
{
  int instruccion; // guarda la instruccion que ingresa el usuario
  TreeMap* mapaXtitulo = createTreeMap(lower_than_string); //mapa ordenado que tendra como claves el titulo
  TreeMap* mapaXid = createTreeMap(lower_than_string);//mapa ordenado que tendra como claves el id
  
  List * bloqueo = createList();
  
  do{
    imprimirInstrucciones();
    instruccion = validarInstruccion();
    printf("\n");
    switch (instruccion)
    {
      case 1:
        printf("*****Cargar archivos*****\n");
        cargarDocumentos(mapaXtitulo, mapaXid);
        break; 
      case 2:
        printf("*****Mostrar documentos ordenados por titulo*****\n");
        DocOrdenados(mapaXtitulo);
        break;
      case 3:
        printf("*****Buscar libro por titulo*****\n");
        //busquedaDeLibro(mapaXtitulo);
        break;
      case 4:
        printf("*****Buscar palabras con mayor frecuencia*****\n");
        palabrasConMayorFrecuencia(mapaXid, bloqueo);
        break;
      case 5:
        //palabraRelevante(mapaXtitulo, mapaXid);
        
        break;
      case 6:
        //buscarPorPalabra()
        
        break;
      case 7:
        palabraContexto();
        
        break;
    }
  }while(instruccion != 0);
  printf("\n***Programa finalizado***");
  return 0;
}

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
    
int lower_than_string(void* key1, void* key2){
  char* k1=(char*) key1;
  char* k2=(char*) key2;
  if(strcmp(k1,k2)<0) return 1;
  return 0;
}
/*
// en teoria se deberia terminar con el } que esta dedspues del return
while(nexTreeMap(mapmapaXtitulo) != NULL){
  Libro * libro = mapaXtitulo->current->pairTree->value;

  char tituloMinus[1000];
  strcpy(tituloMinus, libro->titulo);

  for(int i = 0; tituloMinus[i]; i++){
    tituloMinus[i] = tolower(tituloMinus[i]);
  }

  if(strcmp(tituloMinus, tituloLibro) == 0){
    printf("Libro encontrado: %s\n", libro->titulo);
    int numDocumentos = getSize(mapaXid);

    for(int i = 0 ; i < libro->numPalabras;i++){
      Palabra * palabra = &libro->mapaPalabras.palabras[i];
      double tf = (double)palabra->frecuencia / libro->numPalabras;
      int numDocumentosConPalabras = 0;

      firstTreeMap(mapaXid);
      while(nexTreeMap(mapaXid) != NULL){
        Libro *otroLibro = mapaXid->current->pairTree->value;
        for(int j = 0; j < otroLibro->numPalabras; j++){
          if(strcmp(otroLibro->mapaPalabras.palabras[j].palabra, palabra->palabra) == 0){
            numDocumentosConPalabras++;
            break;
          }
        }
      }

      double idf = log((double)numDocumentos / numDocumentosConPalabras)
      double tfidf = tf * idf;
      palabra->frecuencia = tfidf;

    }

    for(int i = 0; i < libro->numPalabras - 1; i++){
      for(int j = i+1; j < libro->numPalabras; j++){
        if(libro->mapaPalabras.palabras[j].frecuencia < libro->mapaPalabras.palabras[i].frecuencia){
          Palabra aux = libro->mapaPalabras.palabras[i];
          libro->mapaPalabras.palabras[i] = libro->mapaPalabras.palabras[j];
          libro->mapaPalabras.palabras[j] = aux;

        }
      }
    }

    printf("Las palabras mas relevantes son: \n");
    for(int i = 0; i < 10 && i < libro->numPalabras; i++){
      printf("%s (frecuencia: %d)\n", libro->mapaPalabras.palabras[i].palabra, libro->mapaPalabras.palabras[i].frecuencia);
    }
    return;


*/