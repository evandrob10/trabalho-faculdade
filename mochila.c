#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

Item vetor[MAX_ITENS];
int totalVetor = 0;
int comparacoesSeq = 0;
int comparacoesBin = 0;

void inserirItemVetor() {
    if (totalVetor >= MAX_ITENS) {
        printf("Vetor cheio!\n");
        return;
    }
    Item novo;
    printf("Nome: ");
    scanf(" %[^\n]", novo.nome);
    printf("Tipo: ");
    scanf(" %[^\n]", novo.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    vetor[totalVetor++] = novo;
}

void removerItemVetor() {
    if (totalVetor == 0) {
        printf("Vetor vazio!\n");
        return;
    }
    char nome[30];
    printf("Nome do item a remover: ");
    scanf(" %[^\n]", nome);
    int encontrado = 0;
    for (int i = 0; i < totalVetor; i++) {
        if (strcmp(vetor[i].nome, nome) == 0) {
            for (int j = i; j < totalVetor - 1; j++)
                vetor[j] = vetor[j + 1];
            totalVetor--;
            printf("Item removido!\n");
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) printf("Item nao encontrado!\n");
}

void listarItensVetor() {
    if (totalVetor == 0) {
        printf("Vetor vazio!\n");
        return;
    }
    for (int i = 0; i < totalVetor; i++)
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, vetor[i].nome, vetor[i].tipo, vetor[i].quantidade);
}

void ordenarVetor() {
    for (int i = 0; i < totalVetor - 1; i++) {
        for (int j = 0; j < totalVetor - i - 1; j++) {
            if (strcmp(vetor[j].nome, vetor[j + 1].nome) > 0) {
                Item temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
}

void buscarSequencialVetor() {
    if (totalVetor == 0) {
        printf("Vetor vazio!\n");
        return;
    }
    char nome[30];
    printf("Nome do item a buscar (sequencial): ");
    scanf(" %[^\n]", nome);
    comparacoesSeq = 0;
    for (int i = 0; i < totalVetor; i++) {
        comparacoesSeq++;
        if (strcmp(vetor[i].nome, nome) == 0) {
            printf("Item encontrado!\nNome: %s | Tipo: %s | Quantidade: %d\n",
                   vetor[i].nome, vetor[i].tipo, vetor[i].quantidade);
            printf("Comparacoes realizadas: %d\n", comparacoesSeq);
            return;
        }
    }
    printf("Item nao encontrado! Comparacoes: %d\n", comparacoesSeq);
}

void buscarBinariaVetor() {
    if (totalVetor == 0) {
        printf("Vetor vazio!\n");
        return;
    }
    char nome[30];
    printf("Nome do item a buscar (binaria): ");
    scanf(" %[^\n]", nome);
    int inicio = 0, fim = totalVetor - 1;
    comparacoesBin = 0;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoesBin++;
        int cmp = strcmp(vetor[meio].nome, nome);
        if (cmp == 0) {
            printf("Item encontrado!\nNome: %s | Tipo: %s | Quantidade: %d\n",
                   vetor[meio].nome, vetor[meio].tipo, vetor[meio].quantidade);
            printf("Comparacoes realizadas: %d\n", comparacoesBin);
            return;
        } else if (cmp < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }
    printf("Item nao encontrado! Comparacoes: %d\n", comparacoesBin);
}

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

No* lista = NULL;

void inserirItemLista() {
    No* novo = (No*)malloc(sizeof(No));
    printf("Nome: ");
    scanf(" %[^\n]", novo->dados.nome);
    printf("Tipo: ");
    scanf(" %[^\n]", novo->dados.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);
    novo->proximo = lista;
    lista = novo;
}

void removerItemLista() {
    if (!lista) {
        printf("Lista vazia!\n");
        return;
    }
    char nome[30];
    printf("Nome do item a remover: ");
    scanf(" %[^\n]", nome);
    No *atual = lista, *anterior = NULL;
    while (atual) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior) anterior->proximo = atual->proximo;
            else lista = atual->proximo;
            free(atual);
            printf("Item removido!\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Item nao encontrado!\n");
}

void listarItensLista() {
    if (!lista) {
        printf("Lista vazia!\n");
        return;
    }
    No* atual = lista;
    int i = 1;
    while (atual) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i++, atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
}

void buscarSequencialLista() {
    if (!lista) {
        printf("Lista vazia!\n");
        return;
    }
    char nome[30];
    printf("Nome do item a buscar (sequencial lista): ");
    scanf(" %[^\n]", nome);
    comparacoesSeq = 0;
    No* atual = lista;
    while (atual) {
        comparacoesSeq++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            printf("Item encontrado!\nNome: %s | Tipo: %s | Quantidade: %d\n",
                   atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
            printf("Comparacoes realizadas: %d\n", comparacoesSeq);
            return;
        }
        atual = atual->proximo;
    }
    printf("Item nao encontrado! Comparacoes: %d\n", comparacoesSeq);
}

int main() {
    int escolha, opcao;
    do {
        printf("\n--- Sistema de Mochila ---\n");
        printf("Escolha a estrutura:\n1. Vetor\n2. Lista encadeada\n0. Sair\nEscolha: ");
        scanf("%d", &escolha);
        if (escolha == 0) break;

        if (escolha == 1) {
            do {
                printf("\n--- Vetor ---\n");
                printf("1. Inserir item\n2. Remover item\n3. Listar itens\n4. Ordenar itens\n5. Busca sequencial\n6. Busca binaria\n0. Voltar\nOpcao: ");
                scanf("%d", &opcao);
                switch(opcao) {
                    case 1: inserirItemVetor(); break;
                    case 2: removerItemVetor(); break;
                    case 3: listarItensVetor(); break;
                    case 4: ordenarVetor(); printf("Vetor ordenado!\n"); break;
                    case 5: buscarSequencialVetor(); break;
                    case 6: ordenarVetor(); buscarBinariaVetor(); break;
                    case 0: break;
                    default: printf("Opcao invalida!\n");
                }
            } while(opcao != 0);
        } else if (escolha == 2) {
            do {
                printf("\n--- Lista Encadeada ---\n");
                printf("1. Inserir item\n2. Remover item\n3. Listar itens\n4. Busca sequencial\n0. Voltar\nOpcao: ");
                scanf("%d", &opcao);
                switch(opcao) {
                    case 1: inserirItemLista(); break;
                    case 2: removerItemLista(); break;
                    case 3: listarItensLista(); break;
                    case 4: buscarSequencialLista(); break;
                    case 0: break;
                    default: printf("Opcao invalida!\n");
                }
            } while(opcao != 0);
        } else {
            printf("Escolha invalida!\n");
        }
    } while (1);

    No* atual = lista;
    while (atual) {
        No* temp = atual;
        atual = atual->proximo;
        free(temp);
    }

    printf("Saindo do sistema.\n");
    return 0;
}
