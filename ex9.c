#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALUNOS 100

typedef struct {
    char nome[100];
    float nota1, nota2, media;
} Aluno;

typedef struct {
    char nomeTurma[100];
    int qtdAlunos;
    Aluno alunos[MAX_ALUNOS];
} Turma;

void definirTurma(Turma *turma) {
    printf("Nome da turma: ");
    setbuf(stdin, NULL);
    fgets(turma->nomeTurma, sizeof(turma->nomeTurma), stdin);
    turma->nomeTurma[strcspn(turma->nomeTurma, "\n")] = 0;
    turma->qtdAlunos = 0;
}

void inserirAluno(Turma *turma) {
    if (turma->qtdAlunos >= MAX_ALUNOS) {
        printf("Limite de alunos atingido!\n");
        return;
    }
    Aluno *a = &turma->alunos[turma->qtdAlunos];
    printf("Nome do aluno: ");
    setbuf(stdin, NULL);
    fgets(a->nome, sizeof(a->nome), stdin);
    a->nome[strcspn(a->nome, "\n")] = 0;
    printf("Nota 1: ");
    scanf("%f", &a->nota1);
    printf("Nota 2: ");
    scanf("%f", &a->nota2);
    a->media = (a->nota1 + a->nota2) / 2.0;
    turma->qtdAlunos++;
}

void exibirAlunos(Turma *turma) {
    printf("Alunos e médias:\n");
    for (int i = 0; i < turma->qtdAlunos; i++) {
        printf("%s - Média: %.2f\n", turma->alunos[i].nome, turma->alunos[i].media);
    }
}

void exibirAprovados(Turma *turma) {
    printf("Alunos aprovados:\n");
    for (int i = 0; i < turma->qtdAlunos; i++) {
        if (turma->alunos[i].media >= 6.0)
            printf("%s - Média: %.2f\n", turma->alunos[i].nome, turma->alunos[i].media);
    }
}

void exibirReprovados(Turma *turma) {
    printf("Alunos reprovados:\n");
    for (int i = 0; i < turma->qtdAlunos; i++) {
        if (turma->alunos[i].media < 6.0)
            printf("%s - Média: %.2f\n", turma->alunos[i].nome, turma->alunos[i].media);
    }
}

void salvarEmDisco(Turma *turma) {
    FILE *f = fopen("turma.txt", "w");
    if (!f) {
        printf("Erro ao salvar arquivo!\n");
        return;
    }
    fprintf(f, "Turma: %s\n", turma->nomeTurma);
    fprintf(f, "Quantidade de alunos: %d\n", turma->qtdAlunos);
    for (int i = 0; i < turma->qtdAlunos; i++) {
        fprintf(f, "%s %.2f %.2f %.2f\n", turma->alunos[i].nome, turma->alunos[i].nota1, turma->alunos[i].nota2, turma->alunos[i].media);
    }
    fclose(f);
    printf("Dados salvos em turma.txt!\n");
}

int main() {
    Turma turma = { { " " }, 0, { { 0 } } };
    char opcao;
    do {
        printf("\nMenu:\n");
        printf("(a) Definir informações da turma\n");
        printf("(b) Inserir aluno e notas\n");
        printf("(c) Exibir alunos e médias\n");
        printf("(d) Exibir alunos aprovados\n");
        printf("(e) Exibir alunos reprovados\n");
        printf("(f) Salvar dados em Disco\n");
        printf("(g) Sair do programa\n");
        printf("Escolha: ");
        setbuf(stdin, NULL);
        scanf(" %c", &opcao);

        switch(opcao) {
            case 'a': definirTurma(&turma); break;
            case 'b': inserirAluno(&turma); break;
            case 'c': exibirAlunos(&turma); break;
            case 'd': exibirAprovados(&turma); break;
            case 'e': exibirReprovados(&turma); break;
            case 'f': salvarEmDisco(&turma); break;
            case 'g': printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while(opcao != 'g');
    return 0;
}