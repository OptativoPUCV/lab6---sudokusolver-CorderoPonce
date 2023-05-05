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
      
      for (int y = 0 ; y < 9 ; y++){
        if (num == n->sudo[i][y] && y != j) return 0;
      }

      for (int x = 0 ; x < 9 ; x++){
        if (num == n->sudo[x][j] && x != i) return 0;
      }
  
      int k = (i/3)*3 + (j/3); // índice de la submatriz 3x3
            for (int p = 0; p < 9; p++) {
                int sub_i = 3*(k/3) + (p/3);
                int sub_j = 3*(k%3) + (p%3);
                if (num == n->sudo[sub_i][sub_j] && (sub_i != i && sub_j != j)) return 0;
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