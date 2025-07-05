#include <stdio.h>
#include <stdlib.h>

typedef struct dados
{
    char nome[100];
    char esporte[100];
    int idade;
    float altura;
} dados;

int main(){
    dados atleta [5];
    FILE *atletas;
    atletas = fopen("c:\\Users\\kaioe\\OneDrive\\Documentos\\projetos\\arquivos\\lista de atletas.txt","w");


    for(int i = 0;i < 5;i++){
        puts("Digite o nome do atleta:");
        setbuf(stdin,NULL);
        fgets(atleta[i].nome,sizeof(atleta[i].nome),stdin);
        
        puts("Digite sua idade:");
        scanf("%d",&atleta[i].idade);

        puts("Digite a altura do atleta:");
        scanf("%f",&atleta[i].altura);

        puts("Digite o esporte do atleta:");
        setbuf(stdin,NULL);
        fgets(atleta[i].esporte,sizeof(atleta[i].esporte),stdin);
    }

    for(int i = 0;i < 5;i++){
        fprintf(atletas,"Atleta numero %d:\n",i+1);
        fprintf(atletas,"Nome: %s\n",atleta[i].nome);
        fprintf(atletas,"Idade: %d\n",atleta[i].idade);
        fprintf(atletas,"Altura: %.2f\n",atleta[i].altura);
        fprintf(atletas,"Esporte: %s\n",atleta[i].esporte);
    }
    puts("Arquivo salvo!!");

    fclose(atletas);
    return 0;
}