#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20

// =========================
// STRUCT
// =========================

typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// =========================
// VARIÁVEIS GLOBAIS
// =========================

Componente componentes[MAX_COMPONENTES];
int totalComponentes = 0;

long comparacoesBubble = 0;
long comparacoesInsertion = 0;
long comparacoesSelection = 0;

// =========================
// FUNÇÕES AUXILIARES
// =========================

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void removerQuebraLinha(char str[]) {
    str[strcspn(str, "\n")] = '\0';
}

// =========================
// CADASTRO
// =========================

void cadastrarComponente() {

    if (totalComponentes >= MAX_COMPONENTES) {
        printf("\nLimite de componentes atingido!\n");
        return;
    }

    printf("\nNome do componente: ");
    fgets(componentes[totalComponentes].nome, sizeof(componentes[totalComponentes].nome), stdin);
    removerQuebraLinha(componentes[totalComponentes].nome);

    printf("Tipo do componente: ");
    fgets(componentes[totalComponentes].tipo, sizeof(componentes[totalComponentes].tipo), stdin);
    removerQuebraLinha(componentes[totalComponentes].tipo);

    printf("Prioridade (1 a 10): ");
    scanf("%d", &componentes[totalComponentes].prioridade);
    limparBuffer();

    totalComponentes++;

    printf("\nComponente cadastrado com sucesso!\n");
}

// =========================
// EXIBIÇÃO
// =========================

void mostrarComponentes(Componente vetor[], int tamanho) {

    if (tamanho == 0) {
        printf("\nNenhum componente cadastrado.\n");
        return;
    }

    printf("\n========== COMPONENTES ==========\n");

    for (int i = 0; i < tamanho; i++) {

        printf("\nComponente %d\n", i + 1);
        printf("Nome: %s\n", vetor[i].nome);
        printf("Tipo: %s\n", vetor[i].tipo);
        printf("Prioridade: %d\n", vetor[i].prioridade);
    }

    printf("\n=================================\n");
}

// =========================
// BUBBLE SORT - NOME
// =========================

void bubbleSortNome(Componente vetor[], int tamanho) {

    comparacoesBubble = 0;

    for (int i = 0; i < tamanho - 1; i++) {

        for (int j = 0; j < tamanho - i - 1; j++) {

            comparacoesBubble++;

            if (strcmp(vetor[j].nome, vetor[j + 1].nome) > 0) {

                Componente aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
}

// =========================
// INSERTION SORT - TIPO
// =========================

void insertionSortTipo(Componente vetor[], int tamanho) {

    comparacoesInsertion = 0;

    for (int i = 1; i < tamanho; i++) {

        Componente chave = vetor[i];
        int j = i - 1;

        while (j >= 0) {

            comparacoesInsertion++;

            if (strcmp(vetor[j].tipo, chave.tipo) > 0) {
                vetor[j + 1] = vetor[j];
                j--;
            } else {
                break;
            }
        }

        vetor[j + 1] = chave;
    }
}

// =========================
// SELECTION SORT - PRIORIDADE
// =========================

void selectionSortPrioridade(Componente vetor[], int tamanho) {

    comparacoesSelection = 0;

    for (int i = 0; i < tamanho - 1; i++) {

        int menor = i;

        for (int j = i + 1; j < tamanho; j++) {

            comparacoesSelection++;

            if (vetor[j].prioridade < vetor[menor].prioridade) {
                menor = j;
            }
        }

        if (menor != i) {

            Componente aux = vetor[i];
            vetor[i] = vetor[menor];
            vetor[menor] = aux;
        }
    }
}

// =========================
// BUSCA BINÁRIA
// =========================

int buscaBinariaPorNome(Componente vetor[], int tamanho, char nome[]) {

    int inicio = 0;
    int fim = tamanho - 1;

    while (inicio <= fim) {

        int meio = (inicio + fim) / 2;

        int resultado = strcmp(vetor[meio].nome, nome);

        if (resultado == 0) {
            return meio;
        }

        if (resultado < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    return -1;
}

// =========================
// MEDIÇÃO DE TEMPO
// =========================

void executarBubbleSort() {

    clock_t inicio = clock();

    bubbleSortNome(componentes, totalComponentes);

    clock_t fim = clock();

    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\n=== BUBBLE SORT (NOME) ===\n");
    printf("Comparacoes: %ld\n", comparacoesBubble);
    printf("Tempo: %.8f segundos\n", tempo);

    mostrarComponentes(componentes, totalComponentes);
}

void executarInsertionSort() {

    clock_t inicio = clock();

    insertionSortTipo(componentes, totalComponentes);

    clock_t fim = clock();

    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\n=== INSERTION SORT (TIPO) ===\n");
    printf("Comparacoes: %ld\n", comparacoesInsertion);
    printf("Tempo: %.8f segundos\n", tempo);

    mostrarComponentes(componentes, totalComponentes);
}

void executarSelectionSort() {

    clock_t inicio = clock();

    selectionSortPrioridade(componentes, totalComponentes);

    clock_t fim = clock();

    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\n=== SELECTION SORT (PRIORIDADE) ===\n");
    printf("Comparacoes: %ld\n", comparacoesSelection);
    printf("Tempo: %.8f segundos\n", tempo);

    mostrarComponentes(componentes, totalComponentes);
}

// =========================
// BUSCA DE COMPONENTE-CHAVE
// =========================

void buscarComponenteChave() {

    if (totalComponentes == 0) {
        printf("\nNenhum componente cadastrado.\n");
        return;
    }

    char nomeBusca[30];

    printf("\nDigite o nome do componente-chave: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    removerQuebraLinha(nomeBusca);

    int posicao =
        buscaBinariaPorNome(
            componentes,
            totalComponentes,
            nomeBusca
        );

    if (posicao != -1) {

        printf("\n===== COMPONENTE ENCONTRADO =====\n");
        printf("Nome: %s\n", componentes[posicao].nome);
        printf("Tipo: %s\n", componentes[posicao].tipo);
        printf("Prioridade: %d\n", componentes[posicao].prioridade);

        printf("\n>>> TORRE LIBERADA PARA MONTAGEM! <<<\n");

    } else {

        printf("\nComponente-chave nao encontrado.\n");
    }
}

// =========================
// MAIN
// =========================

int main() {

    int opcao;

    do {

        printf("\n====================================");
        printf("\n TORRE DE FUGA - DESAFIO MESTRE");
        printf("\n====================================");
        printf("\n1 - Cadastrar componente");
        printf("\n2 - Mostrar componentes");
        printf("\n3 - Ordenar por nome (Bubble Sort)");
        printf("\n4 - Ordenar por tipo (Insertion Sort)");
        printf("\n5 - Ordenar por prioridade (Selection Sort)");
        printf("\n6 - Buscar componente-chave");
        printf("\n0 - Sair");
        printf("\n\nEscolha uma opcao: ");

        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {

            case 1:
                cadastrarComponente();
                break;

            case 2:
                mostrarComponentes(componentes, totalComponentes);
                break;

            case 3:
                executarBubbleSort();
                break;

            case 4:
                executarInsertionSort();
                break;

            case 5:
                executarSelectionSort();
                break;

            case 6:
                buscarComponenteChave();
                break;

            case 0:
                printf("\nEncerrando sistema...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}