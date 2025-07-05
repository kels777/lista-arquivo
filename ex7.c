#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *atletas;
    atletas = fopen("c:\\Users\\kaioe\\OneDrive\\Documentos\\projetos\\arquivos\\lista de atletas.txt","r");
    if(atletas == NULL){
        puts("Falha ao abrir o arquivo!!");
        exit(1);
    }

    char linha [100];
    for(int i = 0; i < 5;i++){
        for(int j = 0;j < 5;j++){
            fgets(linha,sizeof(linha),atletas);
            printf("%s",linha);
        }
        printf("\n");
    }

    fclose(atletas);
    return 0;
}