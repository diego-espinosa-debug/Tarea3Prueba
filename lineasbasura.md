

/*
void DocOrdenados(List* lista){
  lista->current = firstList(lista);

  while(lista->current != NULL){
    printf("id del libro: %s\n", lista->current->libro.id);
    printf("Titulo del libro: %s\n", lista->current->libro.titulo);
    printf("cantidad de palabras: %d\n", lista->current->libro.numPalabras);
    printf("cantidad de caracteres: %d\n", lista->current->libro.numCaracte);
  }
}
//void busquedaDelLibro(TreeMap * mapaXtitulo){
  char palabrasBuscar[1000];
  printf("Ingrese el titulo que desee buscar: \n");
  fgets(palabrasBuscar, sizeof(palabrasBuscar), stdin);
  palabrasBuscar[strcspn(palbrasBuscar, "\n")] = '\0';

  char *token = strtok(palabrasBuscar, " ");
  bool encontrado = false;

  fistTreeMap(mapaXtitulo);
  while(nextTreeMap(mapaXtitulo) != NULL){
    Libro * libro = mapaXtitulo->current->pairTree->value;
    bool todasEncontradas = true;
    char* tokenCopy = palabrasBuscar;
    while(token != NULL){
      if(strstr(librro->titulo, token) == NULL){
       todasEncontradas = false;
       break;
      }
      token = strtok(NULL, " ");
    }
    if(todasEncontradas){
      printf("Libro encontrado: %s\n", libro->titulo);
      encontrado = true;
    }
    token = strtok(tokenCopy, " ");
  }
  if(!encontrado){
  printf("No se ha encontrado ningun libro con ese titulo.\n");
  }
}
void palabrasConMayorFrecuencia(TreeMap * mapaXid){
  int idLibro;
  printf("Ingrese el ID del libro\n");
  scanf("%d", &idLibro);
  getchar();//podrias ser while(getchar() != '\n'); y en todo getchar po si acaso 


  Libro * libro = searchTreeMap(mapXid, &idLibro);
  if(libro == NULL){
    printf("No se ha encontrado el Libro.\n");
    return;
  }

  MapaPalabras *mapaPalabras = &(libro->mapaPalabras);
  for(int i= 0; i< mapapalabras->numPalabras; i++){
    mapaPalabras->palabras[i].frecuencia /= (double)mapaPalabras->numPalabras;
  }
  for(int i = 0 ; i < mapaPalabras->numPalabras - 1 ; i++){
    for (int j = 0 ; j < mapaPalabras->numPalabras - i - 1; j++){
      if(mapaPalabras->palabras[j].frecuencia < mapaPalabras->palabras[j+1].frecuencia){
        Palabra aux = mapaPalabras->palabras[j];
        mapaPalabras->palabras[j] = mapaPalabras->[j+1];
        mapaPalabras->palabras[j+1] = aux;
      }
    }
  }
  Printf("Las palabras con mayor frecuencia son: \n");
  for(int i = 0; i < 10 && i < mapaPalabras->numPalabras; i++){
    printf("%s (frecuencia: %d")\n", mapaPalabras->palabras[i].palabra, mapaPalabras->palabras[i].frecuencia);
  }
}

void palabraRelevante(TreeMap *mapaXtitulo, TreeMap *mapaXid){
  char titulo[1000];
  printf("Ingrese el titulo del libro: \n");
  fgets(titulo, sizeof(titulo), stdin);
  tituloLibro[strcspn(tituloLibro, "\n")] = '\0';
  for(int i = 0; tituloLibro[i]; i++){
    tituloLibro[i] = tolowe(tituloLibro[i]);
  }

  firstTreeMap(mapaXtitulo);
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

    }
  }
  printf("No se encontro el libro.\n");
}
*/
/*
Voy a escribir mis sugerencias de struct por si sirven de algo 
estructura para la informacion de un libro otra opcion 


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


typedef struct {
  int id; //es el nombre del archivo + .txt
  char titulo[MAX];  // Título del libro
  int numPalabras;
  int numCaracteres;
} Libro;

//una lista de libros (hay que tner encuenta los 2 typedef) 
typedef struct NodoLibro{
Libro libro;
struct NodoLibro* siguiente;
} NodoLibro;

typedef struct{
  NodoLibro* cabeza;  //(o heap lo que prefieran);
}ListaLibros;

//un mapa para los titulos para buscar los libros por titulo mas facil 

typedef struct{
  char palabra[1000];
  ListaLibros libros;
}MapaTitulos;


*/
/*void listBloqueo(List * bloqueo){

  pushBack(bloqueo, "a");
  pushBack(bloqueo, "ante");
  pushBack(bloqueo, "bajo");
  pushBack(bloqueo, "contra");  
  pushBack(bloqueo, "en");
  pushBack(bloqueo, "con");
  pushBack(bloqueo,"los");
  pushBack(bloqueo,"las");
  pushBack(bloqueo,"de");

  pushBack(bloqueo,"del");
  pushBack(bloqueo,"la");
  pushBack(bloqueo,"y");
  pushBack(bloqueo,"o");
  pushBack(bloqueo,"lo");

  pushBack(bloqueo,"segun");
  pushBack(bloqueo, "ya");
  pushBack(bloqueo, "es");
  pushBack(bloqueo, "se");
  pushBack(bloqueo, "que");

  pushBack(bloqueo, "al");
  pushBack(bloqueo, "para");
  pushBack(bloqueo, "sin");
  pushBack(bloqueo, "ni");
  pushBack(bloqueo, "sobre");

  pushBack(bloqueo, "pero");
  pushBack(bloqueo, "como");
  pushBack(bloqueo, "pues");
  pushBack(bloqueo, "sino");
  pushBack(bloqueo, "si");

  pushBack(bloqueo, "no");
  pushBack(bloqueo, "te");
  pushBack(bloqueo, "me");
  pushBack(bloqueo, "mi");
  pushBack(bloqueo, "nos");

  pushBack(bloqueo, "muy");
  pushBack(bloqueo, "le");
  pushBack(bloqueo, "eso");
  pushBack(bloqueo, "esto");
  pushBack(bloqueo, "este");

  pushBack(bloqueo, "esa");
  pushBack(bloqueo, "ese");
  pushBack(bloqueo, "sea");
  pushBack(bloqueo, "por");
  pushBack(bloqueo, "porque");
  pushBack(bloqueo, "tras");

  pushBack(bloqueo, "sus");
  pushBack(bloqueo, "su");
  pushBack(bloqueo, "tal");
  pushBack(bloqueo, "siquiera");
  pushBack(bloqueo, "hacia");
  pushBack(bloqueo, "solo");
  pushBack(bloqueo, "hasta");
  pushBack(bloqueo, "mediante");

  pushBack(bloqueo, "tambien");
  pushBack(bloqueo, "entre");
  pushBack(bloqueo, "talvez");
  pushBack(bloqueo, "durante");
  pushBack(bloqueo, "tanto");
  pushBack(bloqueo, "tan");
  pushBack(bloqueo, "desde");
  pushBack(bloqueo, "entonces");

  pushBack(bloqueo, "salvo");
  pushBack(bloqueo, "excepto");
  pushBack(bloqueo, "cuando");
  pushBack(bloqueo, "cuales");
  pushBack(bloqueo, "cuantas");
  pushBack(bloqueo, "cualquier");
  pushBack(bloqueo, "cada");


}

*/


while(fgets(linea, sizeof(linea), archivo)){// Mientras se lea una línea del archivo
  // Verificar si estamos leyendo el texto, para eso usaremos tokens para encontrar ***
  char *parte = strtok(linea, " "); // Dividir la línea en partes
  while (parte != NULL){
    if(strstr(parte, "***") != NULL){// Verificar si una de las partes contiene "***"
      parte = strtok(NULL, " "); // Obtener la siguiente parte
      if(strstr(parte, "START"))
        leyendoTexto = !leyendoTexto; // Cambiar el estado de lectura
      else break;
        // Si estamos leyendo el texto y encontramos el final, terminar la lectura
        if (!leyendoTexto) break;
      }
    if(leyendoTexto){
    // Aquí puedes procesar el texto que sigue al título
      printf("%s", linea); // Por ejemplo, imprimir el texto
    }
    parte = strtok(NULL, " "); // Obtener la siguiente parte
  }
}