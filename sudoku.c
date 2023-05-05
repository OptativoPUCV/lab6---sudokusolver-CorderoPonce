#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
  
  for (int i = 0 ; i < 9 ; i++){
    for (int j = 0 ; j < 9 ; j++){
      int num = n->sudo[i][j];
      
      if (num != 0){
        
        for (int y = 0 ; y < 9 ; y++){
        if (num == n->sudo[i][y] && y != j) return 0;
        }

        for (int x = 0 ; x < 9 ; x++){
          if (num == n->sudo[x][j] && x != i) return 0;
        }

        int posI = (i/3)*3;
        int posJ = (j/3)*3;
      
        for (int x = posI ; x < posI+3 ; x++){
          for (int y = posJ ; y < posJ+3 ; y++){
            if (num == n->sudo[x][y] && x != i && y != j) return 0;
          }
        }
      }
    }     
  }
  return 1;
}

List* get_adj_nodes(Node* n){
  List* list=createList();
  int num = 1;

  for (int i = 0 ; i < 9 ; i++){
    for (int j = 0 ; j < 9 ; j++){
      
      if(!n->sudo[i][j]){
        while(num < 10){
          Node *new = copy(n);
          new->sudo[i][j] = num;
          if (is_valid(new)) pushBack(list, new);

          num++;
          if(num == 10) return list;
        }
      }
    }
  }
  return list;
}

int is_final(Node* n){

  for (int i = 0 ; i < 9 ; i++){
    for (int j = 0 ; j < 9 ; j++){
      if (n->sudo[i][j] == 0) return 0;
    }
  }
  return 1;
}

Node* DFS(Node* initial, int* cont){
  
  Stack *stack = createStack();
  push(stack, initial);

  while(top(stack) != NULL){
    Node *topNode = top(stack);

    pop(stack);
    if ((is_final(topNode) == 0)) return topNode;

    List *list = createList();
    list = get_adj_nodes(topNode);

    pushBack(stack, list);

    free(topNode);
    cont++;
  }

  
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/