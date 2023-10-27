#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() 
{
  List *lista = (List *) malloc(sizeof(List));
  if (lista != NULL)
  {
    lista -> head = NULL;
  }
  return lista;
}

void * firstList(List * list)
{
  if(list->head == NULL) return NULL;
  list -> current = list -> head;
  return list -> head -> data;
}

void * nextList(List * list) 
{
    if (list != NULL && list->current != NULL && list->current-> next != NULL) 
    {
      list->current = list->current->next;
      return list->current->data;
    } else {
      return NULL;
    }
}

void * lastList(List * list) {
  if(list != NULL && list->tail != NULL)
  {
    list -> current = list -> tail;
    return list->tail->data;
  }
  return NULL;
}

void * prevList(List * list) 
{
  if(list != NULL && list -> current != NULL && list -> current -> prev != NULL)
  {
    list -> current = list -> current -> prev;
    return list-> current->data;
  }else{
    return NULL;
  }

}

void pushFront(List * list, void * data) 
{
  Node * local = createNode(data);
  if(list->head == NULL){
    list->head = local;
    list->tail = local;
    list->current = local;
    return ;
  }else{
    local -> next = list -> head; 
    list -> head -> prev = local;
    list ->head = local;
  }

}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) 
{
  Node *aux = createNode(data);
    if (aux == NULL) {
        return; 
    }
  list->tail = aux;
  list->current->next = aux;
  aux->next = list->tail;
  aux->prev = list->current;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list)
{
  assert(list!=NULL || list->head != NULL);

  if(list == NULL || list -> current == NULL)
      return NULL;

  Node* aux = list->current; 

  if(aux->next != NULL)
      aux->next->prev = aux->prev;

  if(aux->prev != NULL)
      aux->prev->next = aux->next;
  void*dato = (void *)aux->data;

  if(list->current == list->tail)
      list->tail = list->current->prev;

  if(list->current == list->head)
      list->head = list->current->next;

  list->current= aux->prev;
  free(aux);

  return dato;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}