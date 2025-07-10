#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char nome[50];
    int idade;
    float altura;
} Atleta;

int main() {
    FILE *arquivo;
    Atleta atletas[5];

    arquivo = fopen("atletas.bin", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    fread(atletas, sizeof(Atleta), 5, arquivo);
    fclose(arquivo);

    int indiceMaisAlto = 0;
    int indiceMaisVelho = 0;

    for (int i = 1; i < 5; i++) {
        if (atletas[i].altura > atletas[indiceMaisAlto].altura) {
            indiceMaisAlto = i;
        }
        if (atletas[i].idade > atletas[indiceMaisVelho].idade) {
            indiceMaisVelho = i;
        }
    }

    printf("Atleta mais alto: %s\n", atletas[indiceMaisAlto].nome);
    printf("Atleta mais velho: %s\n", atletas[indiceMaisVelho].nome);

    return 0;
}
