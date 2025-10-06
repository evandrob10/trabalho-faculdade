#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

Item mochila[MAX_ITENS];
int totalItens = 0;

void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("Mochila cheia!\n");
        return;
    }
    Item novo;
    printf("Nome do item: ");
    scanf(" %[^\n]", novo.nome);
    printf("Tipo do item: ");
    scanf(" %[^\n]", novo.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    mochila[totalItens] = novo;
    totalItens++;
    printf("Item adicionado com sucesso!\n");
}

void removerItem() {
    if (totalItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }
    char nome[30];
    printf("Nome do item a remover: ");
    scanf(" %[^\n]", nome);
    int encontrado = 0;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (int j = i; j < totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            totalItens--;
            printf("Item removido!\n");
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) printf("Item nao encontrado!\n");
}

void listarItens() {
    if (totalItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }
    printf("\n--- Itens na mochila ---\n");
    for (int i = 0; i < totalItens; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n", i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

void buscarItem() {
    if (totalItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }
    char nome[30];
    printf("Digite o nome do item para buscar: ");
    scanf(" %[^\n]", nome);
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("Item encontrado!\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return;
        }
    }
    printf("Item nao encontrado!\n");
}

int main() {
    int opcao;
    do {
        printf("\n--- Sistema de Inventario ---\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1: inserirItem(); listarItens(); break;
            case 2: removerItem(); listarItens(); break;
            case 3: listarItens(); break;
            case 4: buscarItem(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
    return 0;
}
