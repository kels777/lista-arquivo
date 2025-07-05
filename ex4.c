#include <stdio.h>
#include <stdlib.h>

void construirMatriz(int ***mat,int vertical,int horizontal){
    *mat = malloc(vertical*sizeof(int*));
    if(mat == NULL){
        puts("Falha na alocação na memória!!");
        exit(1);
    }

    for(int i = 0;i < vertical;i++){
        (*mat)[i] = malloc(horizontal*sizeof(int*));
        if((*mat)[i]==NULL){
            puts("Falha na alocação na memoria!!");
        }
    }
}

void limparMatriz(int ***mat,int vertical){
    for(int i =0;i < vertical;i++){
        free((*mat)[i]);
    }

    free(*mat);
}

void imprimirMatriz(int **mat,int vertical,int horizontal){
    for(int i = 0;i < vertical;i++){
        for(int j = 0;j < horizontal;j++){
            printf("[%d] ",mat[i][j]);
        }
        printf("\n");
    }
}

int main(){
    FILE *mat;
    mat = fopen("c:\\Users\\kaioe\\OneDrive\\Documentos\\projetos\\arquivos\\matriz.txt","r");
    if(mat == NULL){
        puts("Falha ao abrir o arquivo!!");
        exit(1);
    }

    int vert, hori;
    fscanf(mat,"%d %d",&vert,&hori);

    int **matriz;
    construirMatriz(&matriz,vert,hori);

    for(int i = 0;i < vert;i++){
        for(int j = 0;j < hori;j++){
            fscanf(mat,"%d",&matriz[i][j]);
        }
    }

    imprimirMatriz(matriz,vert,hori);

    fclose(mat);
    limparMatriz(&matriz,vert);
    return 0;
}

