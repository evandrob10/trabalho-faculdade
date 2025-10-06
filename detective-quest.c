#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

Sala* criarSala(const char* nome, const char* pista) {
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    if (!novaSala) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    strcpy(novaSala->nome, nome);
    if (pista != NULL)
        strcpy(novaSala->pista, pista);
    else
        strcpy(novaSala->pista, "");
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    return novaSala;
}

BSTPista* inserirPista(BSTPista* raiz, const char* pista) {
    if (raiz == NULL) {
        BSTPista* novo = (BSTPista*)malloc(sizeof(BSTPista));
        strcpy(novo->pista, pista);
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    }
    if (strcmp(pista, raiz->pista) < 0)
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    else if (strcmp(pista, raiz->pista) > 0)
        raiz->direita = inserirPista(raiz->direita, pista);
    return raiz;
}

void exibirPistas(BSTPista* raiz) {
    if (raiz == NULL)
        return;
    exibirPistas(raiz->esquerda);
    printf("- %s\n", raiz->pista);
    exibirPistas(raiz->direita);
}

void explorarSalasComPistas(Sala* salaAtual, BSTPista** arvorePistas) {
    char escolha;
    while (salaAtual != NULL) {
        printf("\nVocê está na %s.\n", salaAtual->nome);
        if (strlen(salaAtual->pista) > 0) {
            printf("Você encontrou uma pista: %s\n", salaAtual->pista);
            *arvorePistas = inserirPista(*arvorePistas, salaAtual->pista);
        }
        printf("Para onde deseja ir? (e = esquerda, d = direita, s = sair): ");
        scanf(" %c", &escolha);

        if (escolha == 'e' || escolha == 'E') {
            if (salaAtual->esquerda != NULL)
                salaAtual = salaAtual->esquerda;
            else
                printf("Não há sala à esquerda!\n");
        } else if (escolha == 'd' || escolha == 'D') {
            if (salaAtual->direita != NULL)
                salaAtual = salaAtual->direita;
            else
                printf("Não há sala à direita!\n");
        } else if (escolha == 's' || escolha == 'S') {
            printf("Exploração encerrada.\n");
            return;
        } else {
            printf("Opção inválida! Tente novamente.\n");
        }
    }
}

int main() {
    Sala* hallEntrada = criarSala("Hall de Entrada", "Carta misteriosa");
    Sala* salaEstar = criarSala("Sala de Estar", "Chave antiga");
    Sala* cozinha = criarSala("Cozinha", "Pegada suja");
    Sala* biblioteca = criarSala("Biblioteca", "Livro com anotações");
    Sala* jardim = criarSala("Jardim", NULL);
    Sala* sotao = criarSala("Sótão", "Diário secreto");

    hallEntrada->esquerda = salaEstar;
    hallEntrada->direita = cozinha;
    salaEstar->esquerda = biblioteca;
    salaEstar->direita = jardim;
    cozinha->direita = sotao;

    BSTPista* arvorePistas = NULL;

    printf("Bem-vindo ao Detective Quest!\nExplore a mansão e colete pistas.\n");
    explorarSalasComPistas(hallEntrada, &arvorePistas);

    printf("\nPistas coletadas em ordem alfabética:\n");
    exibirPistas(arvorePistas);

    free(sotao);
    free(jardim);
    free(biblioteca);
    free(cozinha);
    free(salaEstar);
    free(hallEntrada);

    void liberarBST(BSTPista* raiz) {
        if (!raiz) return;
        liberarBST(raiz->esquerda);
        liberarBST(raiz->direita);
        free(raiz);
    }
    liberarBST(arvorePistas);

    return 0;
}
