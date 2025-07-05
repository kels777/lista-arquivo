#include <stdio.h>
#include <stdlib.h>

struct quantidade {
    int contador;
};

void repeticaoDeLetras(char palavra[]) {
    struct quantidade repeticao[100] = {0};
    char clone[100];
    int unico, x = 0;

    for (int i = 0; palavra[i] != '\0'; i++) {
        unico = 1;
        for (int j = 0; j < x; j++) {
            if (palavra[i] == clone[j]) {
                repeticao[j].contador++;
                unico = 0;
                break;
            }
        }
        if (unico) {
            clone[x] = palavra[i];
            repeticao[x].contador = 1;
            x++;
        }
    }

    printf("Palavra: %s\n", palavra);
    for (int i = 0; i < x; i++) {
        if (repeticao[i].contador > 1) {
            printf("A letra [%c] repetiu [%d] vezes.\n", clone[i], repeticao[i].contador);
        }
    }
    printf("\n");
}

int main() {
    FILE *livro = fopen("c:\\Users\\kaioe\\OneDrive\\Documentos\\projetos\\arquivos\\palavras.txt", "r");
    if (!livro) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    char pegarPalavra[100];
    while (fscanf(livro, "%s", pegarPalavra) != EOF) {
        repeticaoDeLetras(pegarPalavra);
    }

    fclose(livro);
    return 0;
}
