#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// Struct que representa um item da mochila
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Variáveis globais
Item mochila[MAX_ITENS];
int totalItens = 0;

// Função para listar todos os itens
void listarItens() {
    printf("\n===== ITENS NA MOCHILA =====\n");

    if (totalItens == 0) {
        printf("A mochila esta vazia.\n");
        return;
    }

    for (int i = 0; i < totalItens; i++) {
        printf("\nItem %d\n", i + 1);
        printf("Nome: %s\n", mochila[i].nome);
        printf("Tipo: %s\n", mochila[i].tipo);
        printf("Quantidade: %d\n", mochila[i].quantidade);
    }

    printf("============================\n");
}

// Função para cadastrar um item
void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("\nMochila cheia! Limite de %d itens atingido.\n", MAX_ITENS);
        return;
    }

    printf("\nNome do item: ");
    scanf(" %[^\n]", mochila[totalItens].nome);

    printf("Tipo do item: ");
    scanf(" %[^\n]", mochila[totalItens].tipo);

    printf("Quantidade: ");
    scanf("%d", &mochila[totalItens].quantidade);

    totalItens++;

    printf("\nItem cadastrado com sucesso!\n");
    listarItens();
}

// Função de busca sequencial
void buscarItem() {
    char nomeBusca[30];
    int encontrado = 0;

    printf("\nDigite o nome do item que deseja buscar: ");
    scanf(" %[^\n]", nomeBusca);

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\n===== ITEM ENCONTRADO =====\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\nItem nao encontrado.\n");
    }
}

// Função para remover um item
void removerItem() {
    char nomeRemover[30];
    int posicao = -1;

    printf("\nDigite o nome do item que deseja remover: ");
    scanf(" %[^\n]", nomeRemover);

    // Busca o item
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            posicao = i;
            break;
        }
    }

    if (posicao == -1) {
        printf("\nItem nao encontrado.\n");
        return;
    }

    // Desloca os elementos para preencher o espaço
    for (int i = posicao; i < totalItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    totalItens--;

    printf("\nItem removido com sucesso!\n");
    listarItens();
}

int main() {
    int opcao;

    do {
        printf("\n===== INVENTARIO FREE FIRE =====\n");
        printf("1 - Cadastrar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem();
                break;

            case 2:
                removerItem();
                break;

            case 3:
                listarItens();
                break;

            case 4:
                buscarItem();
                break;

            case 0:
                printf("\nEncerrando o sistema...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}