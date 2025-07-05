#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *lista;
    lista = fopen("c:\\Users\\kaioe\\OneDrive\\Documentos\\projetos\\arquivos\\lista de produtos.txt","r");

    char nome[100];
    int quantidade;
    float preco;
    float valorTotal = 0;

    while (fscanf(lista, "%s %d %f", nome, &quantidade, &preco) == 3) {
        valorTotal += quantidade * preco;
    }

    printf("O valor total da compra é R$ %.2f\n", valorTotal);

    fclose(lista);
    return 0;
}