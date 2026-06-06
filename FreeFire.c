#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 100

// =========================
// STRUCTS
// =========================

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// =========================
// VARIÁVEIS GLOBAIS
// =========================

Item mochila[MAX_ITENS];
int totalItens = 0;

No* inicio = NULL;

// =========================
// FUNÇÕES DO VETOR
// =========================

void inserirItemVetor() {

    if (totalItens >= MAX_ITENS) {
        printf("\nMochila cheia!\n");
        return;
    }

    printf("\nNome: ");
    scanf(" %[^\n]", mochila[totalItens].nome);

    printf("Tipo: ");
    scanf(" %[^\n]", mochila[totalItens].tipo);

    printf("Quantidade: ");
    scanf("%d", &mochila[totalItens].quantidade);

    totalItens++;

    printf("\nItem inserido no vetor com sucesso!\n");
}

void listarItensVetor() {

    printf("\n===== MOCHILA (VETOR) =====\n");

    if (totalItens == 0) {
        printf("Nenhum item cadastrado.\n");
        return;
    }

    for (int i = 0; i < totalItens; i++) {

        printf("\nItem %d\n", i + 1);
        printf("Nome: %s\n", mochila[i].nome);
        printf("Tipo: %s\n", mochila[i].tipo);
        printf("Quantidade: %d\n", mochila[i].quantidade);
    }
}

void removerItemVetor() {

    char nome[30];
    int posicao = -1;

    printf("\nNome do item para remover: ");
    scanf(" %[^\n]", nome);

    for (int i = 0; i < totalItens; i++) {

        if (strcmp(mochila[i].nome, nome) == 0) {
            posicao = i;
            break;
        }
    }

    if (posicao == -1) {
        printf("\nItem não encontrado.\n");
        return;
    }

    for (int i = posicao; i < totalItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    totalItens--;

    printf("\nItem removido com sucesso!\n");
}

int buscarSequencialVetor(char nome[], int* comparacoes) {

    *comparacoes = 0;

    for (int i = 0; i < totalItens; i++) {

        (*comparacoes)++;

        if (strcmp(mochila[i].nome, nome) == 0) {
            return i;
        }
    }

    return -1;
}

void ordenarVetor() {

    Item aux;

    for (int i = 0; i < totalItens - 1; i++) {

        for (int j = 0; j < totalItens - i - 1; j++) {

            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {

                aux = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = aux;
            }
        }
    }

    printf("\nVetor ordenado com sucesso!\n");
}

int buscarBinariaVetor(char nome[], int* comparacoes) {

    int inicioBusca = 0;
    int fimBusca = totalItens - 1;

    *comparacoes = 0;

    while (inicioBusca <= fimBusca) {

        int meio = (inicioBusca + fimBusca) / 2;

        (*comparacoes)++;

        int resultado = strcmp(mochila[meio].nome, nome);

        if (resultado == 0) {
            return meio;
        }

        if (resultado < 0) {
            inicioBusca = meio + 1;
        } else {
            fimBusca = meio - 1;
        }
    }

    return -1;
}

// =========================
// FUNÇÕES DA LISTA
// =========================

void inserirItemLista() {

    No* novo = (No*) malloc(sizeof(No));

    if (novo == NULL) {
        printf("Erro de memória.\n");
        return;
    }

    printf("\nNome: ");
    scanf(" %[^\n]", novo->dados.nome);

    printf("Tipo: ");
    scanf(" %[^\n]", novo->dados.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);

    novo->proximo = inicio;
    inicio = novo;

    printf("\nItem inserido na lista!\n");
}

void listarItensLista() {

    No* atual = inicio;
    int contador = 1;

    printf("\n===== MOCHILA (LISTA ENCADEADA) =====\n");

    if (atual == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    while (atual != NULL) {

        printf("\nItem %d\n", contador++);
        printf("Nome: %s\n", atual->dados.nome);
        printf("Tipo: %s\n", atual->dados.tipo);
        printf("Quantidade: %d\n", atual->dados.quantidade);

        atual = atual->proximo;
    }
}

No* buscarSequencialLista(char nome[], int* comparacoes) {

    No* atual = inicio;

    *comparacoes = 0;

    while (atual != NULL) {

        (*comparacoes)++;

        if (strcmp(atual->dados.nome, nome) == 0) {
            return atual;
        }

        atual = atual->proximo;
    }

    return NULL;
}

void removerItemLista() {

    char nome[30];

    printf("\nNome do item para remover: ");
    scanf(" %[^\n]", nome);

    No* atual = inicio;
    No* anterior = NULL;

    while (atual != NULL &&
           strcmp(atual->dados.nome, nome) != 0) {

        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("\nItem não encontrado.\n");
        return;
    }

    if (anterior == NULL) {
        inicio = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);

    printf("\nItem removido da lista com sucesso!\n");
}

// =========================
// MAIN
// =========================

int main() {

    int opcao;
    int comparacoes;
    char nomeBusca[30];

    do {

        printf("\n==============================");
        printf("\n INVENTARIO FREE FIRE");
        printf("\n==============================");
        printf("\n1  - Inserir item no vetor");
        printf("\n2  - Remover item do vetor");
        printf("\n3  - Listar vetor");
        printf("\n4  - Busca sequencial vetor");

        printf("\n5  - Inserir item na lista");
        printf("\n6  - Remover item da lista");
        printf("\n7  - Listar lista");
        printf("\n8  - Busca sequencial lista");

        printf("\n9  - Ordenar vetor");
        printf("\n10 - Busca binaria vetor");

        printf("\n0  - Sair");

        printf("\n\nOpcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1:
                inserirItemVetor();
                break;

            case 2:
                removerItemVetor();
                break;

            case 3:
                listarItensVetor();
                break;

            case 4: {

                printf("\nNome do item: ");
                scanf(" %[^\n]", nomeBusca);

                int posicao =
                    buscarSequencialVetor(nomeBusca,
                                          &comparacoes);

                if (posicao != -1) {

                    printf("\nItem encontrado!");
                    printf("\nComparacoes: %d",
                           comparacoes);

                } else {

                    printf("\nItem nao encontrado.");
                    printf("\nComparacoes: %d",
                           comparacoes);
                }

                break;
            }

            case 5:
                inserirItemLista();
                break;

            case 6:
                removerItemLista();
                break;

            case 7:
                listarItensLista();
                break;

            case 8: {

                printf("\nNome do item: ");
                scanf(" %[^\n]", nomeBusca);

                No* encontrado =
                    buscarSequencialLista(nomeBusca,
                                          &comparacoes);

                if (encontrado != NULL) {

                    printf("\nItem encontrado!");
                    printf("\nComparacoes: %d",
                           comparacoes);

                } else {

                    printf("\nItem nao encontrado.");
                    printf("\nComparacoes: %d",
                           comparacoes);
                }

                break;
            }

            case 9:
                ordenarVetor();
                break;

            case 10: {

                printf("\nNome do item: ");
                scanf(" %[^\n]", nomeBusca);

                int posicao =
                    buscarBinariaVetor(nomeBusca,
                                       &comparacoes);

                if (posicao != -1) {

                    printf("\nItem encontrado!");
                    printf("\nComparacoes: %d",
                           comparacoes);

                } else {

                    printf("\nItem nao encontrado.");
                    printf("\nComparacoes: %d",
                           comparacoes);
                }

                break;
            }

            case 0:
                printf("\nEncerrando sistema...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}