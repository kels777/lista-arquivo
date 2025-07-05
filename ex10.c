
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int codVendedor;
    char nome[100];
    float valorVenda;
    int mes;
} Registro;

void criarArquivo(const char *nomeArq) {
    FILE *f = fopen(nomeArq, "wb");
    if (f) {
        puts("Arquivo criado com sucesso!");
        fclose(f);
    } else {
        puts("Erro ao criar arquivo!");
    }
}

int existeRegistro(Registro *regs, int n, int cod, int mes) {
    for (int i = 0; i < n; i++)
        if (regs[i].codVendedor == cod && regs[i].mes == mes)
            return 1;
    return 0;
}

int carregarRegistros(Registro *regs, const char *nomeArq, int max) {
    FILE *f = fopen(nomeArq, "rb");
    if (!f) return 0;
    int n = 0;
    while (fread(&regs[n], sizeof(Registro), 1, f) == 1 && n < max)
        n++;
    fclose(f);
    return n;
}

void salvarRegistros(Registro *regs, int n, const char *nomeArq) {
    FILE *f = fopen(nomeArq, "wb");
    if (!f) {
        puts("Erro ao salvar arquivo!");
        return;
    }
    fwrite(regs, sizeof(Registro), n, f);
    fclose(f);
}

void incluirRegistro(const char *nomeArq, int max) {
    Registro regs[100];
    int n = carregarRegistros(regs, nomeArq, max);

    Registro novo;
    printf("Codigo vendedor: ");
    scanf("%d", &novo.codVendedor);
    printf("Nome vendedor: ");
    setbuf(stdin, NULL);
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = 0;
    printf("Valor da venda: ");
    scanf("%f", &novo.valorVenda);
    printf("Mes: ");
    scanf("%d", &novo.mes);

    if (existeRegistro(regs, n, novo.codVendedor, novo.mes)) {
        puts("Registro já existe!");
        return;
    }

    regs[n++] = novo;

    // Ordena por código e mês
    for (int i = 0; i < n-1; i++)
        for (int j = i+1; j < n; j++)
            if (regs[i].codVendedor > regs[j].codVendedor ||
                (regs[i].codVendedor == regs[j].codVendedor && regs[i].mes > regs[j].mes)) {
                Registro tmp = regs[i];
                regs[i] = regs[j];
                regs[j] = tmp;
            }

    salvarRegistros(regs, n, nomeArq);
    puts("Registro incluído!");
}

void excluirVendedor(const char *nomeArq, int max) {
    Registro regs[100];
    int n = carregarRegistros(regs, nomeArq, max);
    int cod;
    printf("Codigo do vendedor a excluir: ");
    scanf("%d", &cod);

    int m = 0;
    for (int i = 0; i < n; i++)
        if (regs[i].codVendedor != cod)
            regs[m++] = regs[i];

    if (m == n) {
        puts("Nenhum registro removido.");
    } else {
        salvarRegistros(regs, m, nomeArq);
        puts("Registros do vendedor removidos.");
    }
}

void alterarVenda(const char *nomeArq, int max) {
    Registro regs[100];
    int n = carregarRegistros(regs, nomeArq, max);
    int cod, mes;
    printf("Codigo vendedor: ");
    scanf("%d", &cod);
    printf("Mes: ");
    scanf("%d", &mes);

    int achou = 0;
    for (int i = 0; i < n; i++) {
        if (regs[i].codVendedor == cod && regs[i].mes == mes) {
            printf("Valor atual: %.2f\n", regs[i].valorVenda);
            printf("Novo valor: ");
            scanf("%f", &regs[i].valorVenda);
            achou = 1;
            break;
        }
    }
    if (achou) {
        salvarRegistros(regs, n, nomeArq);
        puts("Valor alterado!");
    } else {
        puts("Registro não encontrado!");
    }
}

void imprimirRegistros(const char *nomeArq, int max) {
    Registro regs[100];
    int n = carregarRegistros(regs, nomeArq, max);
    printf("Codigo\tNome\t\tValor\tMes\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%s\t%.2f\t%d\n", regs[i].codVendedor, regs[i].nome, regs[i].valorVenda, regs[i].mes);
}

void excluirArquivo(const char *nomeArq) {
    if (remove(nomeArq) == 0)
        puts("Arquivo excluído!");
    else
        puts("Erro ao excluir arquivo!");
}

int main() {
    const char nomeArq[] = "vendas.dat";
    const int max = 100;
    char op;
    do {
        printf("\nMenu:\n");
        printf("a) Criar o arquivo de dados\n");
        printf("b) Incluir um registro\n");
        printf("c) Excluir um vendedor\n");
        printf("d) Alterar valor de uma venda\n");
        printf("e) Imprimir registros\n");
        printf("f) Excluir o arquivo de dados\n");
        printf("g) Finalizar o programa\n");
        printf("Opcao: ");
        setbuf(stdin, NULL);
        scanf(" %c", &op);

        switch(op) {
            case 'a': criarArquivo(nomeArq); break;
            case 'b': incluirRegistro(nomeArq, max); break;
            case 'c': excluirVendedor(nomeArq, max); break;
            case 'd': alterarVenda(nomeArq, max); break;
            case 'e': imprimirRegistros(nomeArq, max); break;
            case 'f': excluirArquivo(nomeArq); break;
            case 'g': puts("Fim do programa."); break;
            default: puts("Opcao invalida!");
        }
    } while(op != 'g');
    return 0;
}