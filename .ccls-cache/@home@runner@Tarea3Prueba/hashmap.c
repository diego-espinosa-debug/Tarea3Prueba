
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    PairHash ** buckets;
    long size; //cantidad de datos/PairHashs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

PairHash * createPair( char * key,  void * value) {
    PairHash * new = (PairHash *)malloc(sizeof(PairHash));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
  if(key1==NULL || key2==NULL) return 0;
  if(strcmp((char*)key1,(char*)key2) == 0) return 1;
  return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
  if(map == NULL || key == NULL){
    return;
  }
  int posicion = hash(key,map->capacity);

  while(map->buckets[posicion] != NULL && map->buckets[posicion]->key != NULL){
      posicion = (posicion +1) % map->capacity;


      if(map->buckets[posicion] != NULL && is_equal(map->buckets[posicion]->key,key)){
        return;
      }
  }

  map->buckets[posicion] = createPair(key, value);

  if(map->buckets[posicion] != NULL){
    map->size++;
    map->current = posicion;

  }
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)

  if(map == NULL) return;

  PairHash **antiguoBuc = map->buckets;
  int antiguaCap = map->capacity;

  map->capacity *=2;
  map->buckets = (PairHash **)calloc(map->capacity, sizeof(PairHash *));

  if(map->buckets == NULL) return;

  map->size = 0;

  for(int i = 0; i < antiguaCap; i++){
    if(antiguoBuc[i] && antiguoBuc[i]->key){
      insertMap(map, antiguoBuc[i]->key, antiguoBuc[i]->value);
    }
  }

  free(antiguoBuc);

}


HashMap * createMap(long capacity) {

  if(capacity <= 0){
    return NULL;
  }

  HashMap *map = (HashMap *)malloc(sizeof(HashMap));
  if(map == NULL){
    return NULL;
  }
  map->capacity = capacity;
  map->size = 0;
  map->current = -1;
  map->buckets = (PairHash **)calloc(capacity, sizeof(PairHash *));

  return map;
}

void eraseMap(HashMap * map,  char * key) {    
  if(map == NULL || key == NULL)
    return;

  int posicion = hash(key, map->capacity);

  while(map->buckets[posicion] != NULL){
    if (map->buckets[posicion]->key != NULL && is_equal(map->buckets[posicion]->key, key)) {
      PairHash * PairHash=map->buckets[posicion];
      PairHash->key = NULL;
      map->size--;
      return;
    }

    posicion = (posicion+1) % map->capacity;
  }

}

PairHash * searchMap(HashMap * map,  char * key) {   

  if(map == NULL || key == NULL) return NULL;

  int posicion = hash(key, map->capacity);

  while(map->buckets[posicion] != NULL){
    if(map->buckets[posicion]-> key != NULL && is_equal(map->buckets[posicion]->key, key)){
      map->current = posicion;
      return map->buckets[posicion];
    }
    posicion = (posicion+1)% map->capacity;
  }
  return NULL;
}

PairHash * firstMap(HashMap * map) {

  if(map == NULL) return NULL;

  for(int i = 0; i< map->capacity; i++){
    if(map->buckets[i] != NULL && map->buckets[i]->key != NULL){
      map->current = i;
      return map->buckets[i];
    }

  }
    return NULL;
}

PairHash * nextMap(HashMap * map) {
  if(map == NULL) return NULL;

  for(int i = map->current+1 ; i< map->capacity; i++){
    if(map->buckets[i] != NULL && map->buckets[i]->key != NULL){
       map->current = i;
      return map->buckets[i];
    }
  }

  return NULL;
}
