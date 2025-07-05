#include <stdio.h>
#include <stdlib.h>

void salvarMatrizArquivo(int **mat,int vetical,int horizontal){
    FILE *matriz;
    matriz = fopen("matriz.txt","w");
    if(!matriz){
        puts("Falha ao abrir o arquivo!!");
        exit(1);
    }

    for(int i = 0;i < vetical;i++){
        for(int j = 0;j <horizontal;j++){
            fprintf(matriz,"[%d]  ",mat[i][j]);
        }
        fprintf(matriz,"\n");
    }

    puts("Arquivo salvo!!!");
    fclose(matriz);
}

void limparMemoria(int ***mat, int vert){
    for(int i = 0;i < vert;i++){
        free((*mat)[i]);
    }

    free(*mat);
}


int main(){
   int **mat;
   int x,y;

   puts("Dejesa uma matriz de quais dimencoes:");
   scanf("%d %d",&x,&y);

   if(x < 1 || y < 1){
    puts("Dimenções nao aceitas!!");
    exit(1);
   }

   mat = malloc(x * sizeof(int));
   if(*mat == NULL){
    puts("Falha na alocacao de memoria!!");
    exit(1);
   }
   for(int i = 0;i < x;i++){
       mat[i] = malloc(y * sizeof(int));
    }
    puts("Digite a matriz:");
    for(int i = 0;i < x;i++){
        for(int j = 0;j < y;j++){
            scanf("%d",&mat[i][j]);
        }
    }

    salvarMatrizArquivo(mat,x,y);
    limparMemoria(&mat,x);

    return 0;
}