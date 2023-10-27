#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    PairTree* pairTree;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal_tree(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pairTree = (PairTree *)malloc(sizeof(PairTree));
    new->pairTree->key = key;
    new->pairTree->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {

  TreeMap *map = (TreeMap *)malloc(sizeof(TreeMap));

  map->root = NULL;
  map->current = NULL;
  map->lower_than = lower_than;

    //new->lower_than = lower_than;
  return map;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
  if( tree == NULL) return;
  PairTree* existe = searchTreeMap(tree,key);

  if(existe != NULL){
    return;
  }

  tree->current = tree->root;
  TreeNode* buscar = tree->current;
  int izqODer = 0;
  while(buscar != NULL){
    int result = tree->lower_than(tree->current->pairTree->key,key);
    if(result == 1){
      if(tree->current->right == NULL) {
        buscar = NULL;
      }else{
        tree->current = tree->current->right;
        izqODer = 1;
      }
    } else if (result == 0){
      if(tree->current->left == NULL){
        buscar = NULL;
      } else{
        tree->current = tree->current->left;
        izqODer = 0;
      }
    }
  }

  TreeNode * new = createTreeNode(key,value);
  new->parent = tree->current;
  if(izqODer == 1){
    tree->current->right = new;
  }else{
    tree->current->left = new;
  }
  tree->current = new;
}  

TreeNode * minimum(TreeNode * x){

  while(x->left != NULL){
    x = x->left;
  }
  return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {

  if(node->left == NULL && node->right == NULL){
    if(node->parent == NULL){
      tree->root = NULL;
    } else {
      if(node == node->parent->left){
        node->parent->left = NULL;
      } else{
        node->parent->left = NULL;
      }
    }
    free(node->pairTree);
    free(node);
  } else if( node->left != NULL && node->right == NULL){
      if(node -> parent == NULL){
        tree->root = node->left;
        node->left->parent = NULL;
      } else{
        if(node == node->parent->left){
          node->parent->left = node->left;
        } else{
          node->parent->right = node->left;
        }
        node->left->parent = node->parent;
      }
    free(node->pairTree);
    free(node);
    } else {
        TreeNode* NoMinimo = minimum(node->right);

        PairTree* aux = node->pairTree;
        node->pairTree = NoMinimo->pairTree;
        NoMinimo->pairTree = aux;
        removeNode(tree, NoMinimo);
      }

} 

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




PairTree * searchTreeMap(TreeMap * tree, void* key) {
  if(tree == NULL) return NULL;
  int comprobar = is_equal_tree(tree,tree->root->pairTree->key,key);
  if(comprobar == 1){
    tree->current = tree->root;
    return tree->root->pairTree;
  } else{
    tree->current = tree->root;
  }

  while(comprobar < 1){
    int result = tree->lower_than(tree->current->pairTree->key, key);
    if(result == 1){
      if(tree->current->right == NULL) return NULL;
      tree->current = tree->current->right;
    } else if(result == 0){
      if(tree->current->left == NULL) return NULL;
      tree->current = tree->current->left;
    }
    comprobar = is_equal_tree(tree,tree->current->pairTree->key,key);

  }
  return tree->current->pairTree;
}


PairTree * upperBound(TreeMap * tree, void* key) {

  TreeNode* ub_node = NULL;
  TreeNode* current = tree->root;

  while(current != NULL){
    if(tree->lower_than(current->pairTree->key,key)){
      current = current->right;
    } else {
      ub_node = current;
      current = current->left;
    }
  }
  if(ub_node == NULL) return NULL;
  tree->current = ub_node;
  return ub_node->pairTree;
}

PairTree * firstTreeMap(TreeMap * tree) {

  while(tree->root->left != NULL){
    tree->root = tree->root->left;
  }

  tree->current = tree->root;
  return tree->root->pairTree;
}

PairTree * nextTreeMap(TreeMap * tree) {

  TreeNode* sucesor =NULL;
  TreeNode* padre = tree->root;

  while(padre != NULL){
    if(tree->lower_than(tree->current->pairTree->key, padre->pairTree->key)){
      sucesor = padre;
      padre = padre->left;
    } else {
      padre = padre->right;
    }
  }
  if(sucesor == NULL) return NULL;
  tree->current = sucesor;
  return sucesor->pairTree;
}
