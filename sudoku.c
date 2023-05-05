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
    int rows[9][9] = {0};      // números vistos en cada fila
    int cols[9][9] = {0};      // números vistos en cada columna
    int boxes[9][9] = {0};     // números vistos en cada submatriz de 3x3

    for (int i = 0 ; i < 9 ; i++){
        for (int j = 0 ; j < 9 ; j++){
            int num = n->sudo[i][j];
            if (num == 0) continue;   // ignorar celdas vacías

            // validar fila
            if (rows[i][num-1]) return 0;
            rows[i][num-1] = 1;

            // validar columna
            if (cols[j][num-1]) return 0;
            cols[j][num-1] = 1;

            // validar submatriz de 3x3
            int box_index = (i/3)*3 + (j/3);
            if (boxes[box_index][num-1]) return 0;
            boxes[box_index][num-1] = 1;
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