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
  bool checked[9][9] = {false};

  for (int i = 0 ; i < 9 ; i++){
    for (int j = 0 ; j < 9 ; j++){
      if (!checked[i][j]){
        checked[i][j] = true;
        int num = n->sudo[i][j];

        // Comprobar fila
        for (int y = 0 ; y < 9 ; y++){
          if (y != j && num == n->sudo[i][y]) {
            return 0;
          }
        }

        // Comprobar columna
        for (int x = 0 ; x < 9 ; x++){
          if (x != i && num == n->sudo[x][j]) {
            return 0;
          }
        }

        // Comprobar región 3x3
        int region_x = (i / 3) * 3;
        int region_y = (j / 3) * 3;
        for (int x = region_x ; x < region_x + 3 ; x++){
          for (int y = region_y ; y < region_y + 3 ; y++){
            if ((x != i || y != j) && num == n->sudo[x][y]) {
              return 0;
            }
            checked[x][y] = true;
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
          pushBack(list, new);

          num++;
          if(num == 10) return list;
        }
      }
    }
  }
  return list;
}

int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
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