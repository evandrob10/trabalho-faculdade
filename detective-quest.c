#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 10

typedef struct Sala {
    char nome[50];
    char pista[100];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

typedef struct BSTPista {
    char pista[100];
    struct BSTPista* esquerda;
    struct BSTPista* direita;
} BSTPista;

typedef struct HashItem {
    char pista[100];
    char suspeito[50];
    struct HashItem* proximo;
} HashItem;

// Funções básicas de sala
Sala* criarSala(const char* nome, const char* pista) {
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    strcpy(novaSala->nome, nome);
    strcpy(novaSala->pista, pista);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    return novaSala;
}

// Funções básicas da BST
BSTPista* inserirPista(BSTPista* raiz, const char* pista) {
    if (!raiz) {
        BSTPista* novo = (BSTPista*)malloc(sizeof(BSTPista));
        strcpy(novo->pista, pista);
        novo->esquerda = novo->direita = NULL;
        return novo;
    }
    if (strcmp(pista, raiz->pista) < 0)
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    else if (strcmp(pista, raiz->pista) > 0)
        raiz->direita = inserirPista(raiz->direita, pista);
    return raiz;
}

void exibirPistas(BSTPista* raiz) {
    if (!raiz) return;
    exibirPistas(raiz->esquerda);
    printf("- %s\n", raiz->pista);
    exibirPistas(raiz->direita);
}

// Funções de hash
unsigned int hash(const char* str) {
    unsigned int h = 0;
    for (int i = 0; str[i]; i++) h = (h * 31 + str[i]) % HASH_SIZE;
    return h;
}

void inserirNaHash(HashItem* tabela[], const char* pista, const char* suspeito) {
    unsigned int idx = hash(pista);
    HashItem* novo = (HashItem*)malloc(sizeof(HashItem));
    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);
    novo->proximo = tabela[idx];
    tabela[idx] = novo;
}

char* encontrarSuspeito(HashItem* tabela[], const char* pista) {
    unsigned int idx = hash(pista);
    HashItem* item = tabela[idx];
    while (item) {
        if (strcmp(item->pista, pista) == 0)
            return item->suspeito;
        item = item->proximo;
    }
    return NULL;
}

// Exploração interativa
void explorarSalas(Sala* salaAtual, BSTPista** arvorePistas, HashItem* tabela[]) {
    char escolha;
    while (salaAtual) {
        printf("\nVocê está na %s.\n", salaAtual->nome);
        if (strlen(salaAtual->pista) > 0) {
            printf("Você encontrou uma pista: %s\n", salaAtual->pista);
            *arvorePistas = inserirPista(*arvorePistas, salaAtual->pista);
        }
        printf("Para onde deseja ir? (e = esquerda, d = direita, s = sair): ");
        scanf(" %c", &escolha);

        if (escolha == 'e' || escolha == 'E') {
            if (salaAtual->esquerda) salaAtual = salaAtual->esquerda;
            else printf("Não há sala à esquerda!\n");
        } else if (escolha == 'd' || escolha == 'D') {
            if (salaAtual->direita) salaAtual = salaAtual->direita;
            else printf("Não há sala à direita!\n");
        } else if (escolha == 's' || escolha == 'S') {
            printf("Exploração encerrada.\n");
            return;
        } else {
            printf("Opção inválida!\n");
        }
    }
}

// Função de julgamento final
void verificarSuspeitoFinal(BSTPista* arvorePistas, HashItem* tabela[], const char* acusado) {
    int contador = 0;
    void contar(BSTPista* raiz) {
        if (!raiz) return;
        contar(raiz->esquerda);
        char* suspeito = encontrarSuspeito(tabela, raiz->pista);
        if (suspeito && strcmp(suspeito, acusado) == 0)
            contador++;
        contar(raiz->direita);
    }
    contar(arvorePistas);

    printf("\n%s foi acusado.\n", acusado);
    if (contador >= 2)
        printf("Acusação válida! Há pistas suficientes.\n");
    else
        printf("Acusação inválida! Pistas insuficientes.\n");
}

int main() {
    Sala* hall = criarSala("Hall de Entrada", "Carta misteriosa");
    Sala* estar = criarSala("Sala de Estar", "Chave antiga");
    Sala* cozinha = criarSala("Cozinha", "Pegada suja");
    Sala* biblioteca = criarSala("Biblioteca", "Livro com anotações");
    Sala* jardim = criarSala("Jardim", "");
    Sala* sotao = criarSala("Sótão", "Diário secreto");

    hall->esquerda = estar;
    hall->direita = cozinha;
    estar->esquerda = biblioteca;
    estar->direita = jardim;
    cozinha->direita = sotao;

    BSTPista* arvorePistas = NULL;
    HashItem* tabela[HASH_SIZE] = {NULL};

    inserirNaHash(tabela, "Carta misteriosa", "Sr. Silva");
    inserirNaHash(tabela, "Chave antiga", "Sra. Oliveira");
    inserirNaHash(tabela, "Pegada suja", "Sr. Silva");
    inserirNaHash(tabela, "Livro com anotações", "Sra. Oliveira");
    inserirNaHash(tabela, "Diário secreto", "Sr. Souza");

    printf("Bem-vindo ao Detective Quest!\nExplore a mansão e colete pistas.\n");
    explorarSalas(hall, &arvorePistas, tabela);

    printf("\nPistas coletadas em ordem alfabética:\n");
    exibirPistas(arvorePistas);

    char acusado[50];
    printf("\nQuem você acusa como culpado? ");
    scanf(" %[^\n]", acusado);

    verificarSuspeitoFinal(arvorePistas, tabela, acusado);

    free(sotao); free(jardim); free(biblioteca); free(cozinha); free(estar); free(hall);

    for (int i = 0; i < HASH_SIZE; i++) {
        HashItem* item = tabela[i];
        while (item) {
            HashItem* tmp = item;
            item = item->proximo;
            free(tmp);
        }
    }

    void liberarBST(BSTPista* raiz) {
        if (!raiz) return;
        liberarBST(raiz->esquerda);
        liberarBST(raiz->direita);
        free(raiz);
    }
    liberarBST(arvorePistas);

    return 0;
}