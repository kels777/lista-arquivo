#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int calcularIdade(int dia, int mes, int ano) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    int anoAtual = tm.tm_year + 1900;
    int mesAtual = tm.tm_mon + 1;
    int diaAtual = tm.tm_mday;

    int idade = anoAtual - ano;

    if (mes > mesAtual || (mes == mesAtual && dia > diaAtual)) {
        idade--;
    }

    return idade;
}

int main() {
    FILE *ler, *arqIdades;

    ler = fopen("c:\\Users\\kaioe\\OneDrive\\Documentos\\projetos\\arquivos\\lista de pessoas.txt", "r");
    arqIdades = fopen("c:\\Users\\kaioe\\OneDrive\\Documentos\\projetos\\arquivos\\lista de idades.txt", "w");

    if (!ler || !arqIdades) {
        puts("Erro ao abrir arquivos!");
        return 1;
    }

    char nome[100];
    int dia, mes, ano;
    while (fscanf(ler, "%s %d %d %d", nome, &dia, &mes, &ano) == 4) {
        int idade = calcularIdade(dia, mes, ano);
        fprintf(arqIdades, "Nome: %s Idade: %d\n", nome, idade);
    }

    puts("Data calculada e salva!!");

    fclose(ler);
    fclose(arqIdades);
    return 0;
}