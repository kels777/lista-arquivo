#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[100];
    char telefone[20];
    int dia, mes;
} Contato;

void salvarContatos(Contato *agenda, int n, const char *arquivo) {
    FILE *f = fopen(arquivo, "wb");
    if (f) {
        fwrite(&n, sizeof(int), 1, f);
        fwrite(agenda, sizeof(Contato), n, f);
        fclose(f);
    }
}

int carregarContatos(Contato *agenda, const char *arquivo, int max) {
    FILE *f = fopen(arquivo, "rb");
    int n = 0;
    if (f) {
        fread(&n, sizeof(int), 1, f);
        if (n > max) n = max;
        fread(agenda, sizeof(Contato), n, f);
        fclose(f);
    }
    return n;
}

void inserirContato(Contato *agenda, int *n, int max) {
    if (*n >= max) {
        printf("Agenda cheia!\n");
        return;
    }
    printf("Nome: ");
    setbuf(stdin, NULL);
    fgets(agenda[*n].nome, sizeof(agenda[*n].nome), stdin);
    agenda[*n].nome[strcspn(agenda[*n].nome, "\n")] = 0;
    printf("Telefone: ");
    fgets(agenda[*n].telefone, sizeof(agenda[*n].telefone), stdin);
    agenda[*n].telefone[strcspn(agenda[*n].telefone, "\n")] = 0;
    printf("Dia do aniversario: ");
    scanf("%d", &agenda[*n].dia);
    printf("Mes do aniversario: ");
    scanf("%d", &agenda[*n].mes);
    (*n)++;
}

void removerContato(Contato *agenda, int *n) {
    char nome[100];
    printf("Nome do contato a remover: ");
    setbuf(stdin, NULL);
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;
    int achou = 0;
    for (int i = 0; i < *n; i++) {
        if (strcmp(agenda[i].nome, nome) == 0) {
            for (int j = i; j < *n - 1; j++)
                agenda[j] = agenda[j + 1];
            (*n)--;
            achou = 1;
            printf("Contato removido!\n");
            break;
        }
    }
    if (!achou) printf("Contato nao encontrado!\n");
}

void pesquisarContato(Contato *agenda, int n) {
    char nome[100];
    printf("Nome do contato a pesquisar: ");
    setbuf(stdin, NULL);
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(agenda[i].nome, nome) == 0) {
            printf("Nome: %s\nTelefone: %s\nAniversario: %02d/%02d\n", agenda[i].nome, agenda[i].telefone, agenda[i].dia, agenda[i].mes);
            return;
        }
    }
    printf("Contato nao encontrado!\n");
}

void listarContatos(Contato *agenda, int n) {
    printf("Lista de contatos:\n");
    for (int i = 0; i < n; i++) {
        printf("%s - %s - %02d/%02d\n", agenda[i].nome, agenda[i].telefone, agenda[i].dia, agenda[i].mes);
    }
}

void listarPorLetra(Contato *agenda, int n) {
    char letra;
    printf("Letra inicial: ");
    setbuf(stdin, NULL);
    scanf(" %c", &letra);
    printf("Contatos que começam com '%c':\n", letra);
    for (int i = 0; i < n; i++) {
        if (agenda[i].nome[0] == letra)
            printf("%s - %s - %02d/%02d\n", agenda[i].nome, agenda[i].telefone, agenda[i].dia, agenda[i].mes);
    }
}

void listarAniversariantes(Contato *agenda, int n) {
    int mes;
    printf("Digite o mes: ");
    scanf("%d", &mes);
    printf("Aniversariantes do mes %d:\n", mes);
    for (int i = 0; i < n; i++) {
        if (agenda[i].mes == mes)
            printf("%s - %s - %02d/%02d\n", agenda[i].nome, agenda[i].telefone, agenda[i].dia, agenda[i].mes);
    }
}

int main() {
    Contato agenda[100];
    int max = 100;
    const char arquivo[] = "agenda.bin";
    int n = carregarContatos(agenda, arquivo, max);
    char op;
    do {
        printf("\nMenu:\n");
        printf("a) Inserir contato\n");
        printf("b) Remover contato\n");
        printf("c) Pesquisar contato pelo nome\n");
        printf("d) Listar todos os contatos\n");
        printf("e) Listar contatos por letra inicial\n");
        printf("f) Listar aniversariantes do mes\n");
        printf("g) Sair\n");
        printf("Opcao: ");
        setbuf(stdin, NULL);
        scanf(" %c", &op);

        switch(op) {
            case 'a': inserirContato(agenda, &n, max); break;
            case 'b': removerContato(agenda, &n); break;
            case 'c': pesquisarContato(agenda, n); break;
            case 'd': listarContatos(agenda, n); break;
            case 'e': listarPorLetra(agenda, n); break;
            case 'f': listarAniversariantes(agenda, n); break;
            case 'g': salvarContatos(agenda, n, arquivo); printf("Agenda salva. Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while(op != 'g');