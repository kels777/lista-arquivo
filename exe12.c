#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inverterString(char *str) {
    int i = 0, j = strlen(str) - 1;
    if (j >= 0 && str[j] == '\n') {
        str[j] = '\0';
        j--;
    }
    while (i < j) {
        char tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
        i++;
        j--;
    }
}

int main() {
    char entrada[100], saida[100];
    int max_linha = 31;   
    int max_linhas = 100; 

    printf("Nome do arquivo de entrada: ");
    fgets(entrada, sizeof(entrada), stdin);
    entrada[strcspn(entrada, "\n")] = 0;
    printf("Nome do arquivo de saída: ");
    fgets(saida, sizeof(saida), stdin);
    saida[strcspn(saida, "\n")] = 0;

    FILE *fin = fopen(entrada, "r");
    if (!fin) {
        printf("Erro ao abrir arquivo de entrada!\n");
        return 1;
    }

    char linhas[100][31];
    int n = 0;
    while (fgets(linhas[n], max_linha, fin) && n < max_linhas) {
        inverterString(linhas[n]);
        n++;
    }
    fclose(fin);

    FILE *fout = fopen(saida, "w");
    if (!fout) {
        printf("Erro ao abrir arquivo de saída!\n");
        return 1;
    }

    for (int i = n - 1; i >= 0; i--) {
        fprintf(fout, "%s\n", linhas[i]);
    }
    fclose(fout);

    printf("Arquivo invertido salvo com sucesso!\n");
    return 0;
}