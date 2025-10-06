#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_FILA 5
#define TIPOS_PECAS 4

typedef struct {
    char tipo;
    int id;
} Peca;

typedef struct {
    Peca fila[TAMANHO_FILA];
    int frente;
    int tras;
    int qtd;
} Fila;

Peca gerarPeca(int id) {
    char tipos[TIPOS_PECAS] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.tipo = tipos[rand() % TIPOS_PECAS];
    nova.id = id;
    return nova;
}

void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = 0;
    f->qtd = 0;
    for(int i = 0; i < TAMANHO_FILA; i++) {
        f->fila[i] = gerarPeca(i);
        f->tras = (f->tras + 1) % TAMANHO_FILA;
        f->qtd++;
    }
}

void exibirFila(Fila *f) {
    printf("\nFila de peças:\n");
    for(int i = 0; i < f->qtd; i++) {
        int indice = (f->frente + i) % TAMANHO_FILA;
        printf("[%c %d] ", f->fila[indice].tipo, f->fila[indice].id);
    }
    printf("\n");
}

void jogarPeca(Fila *f) {
    if(f->qtd == 0) {
        printf("A fila está vazia. Nenhuma peça para jogar.\n");
        return;
    }
    Peca removida = f->fila[f->frente];
    printf("Peça jogada: [%c %d]\n", removida.tipo, removida.id);
    f->frente = (f->frente + 1) % TAMANHO_FILA;
    f->qtd--;
}

void inserirPeca(Fila *f, int proximoId) {
    if(f->qtd == TAMANHO_FILA) {
        printf("A fila está cheia. Não é possível inserir nova peça.\n");
        return;
    }
    f->fila[f->tras] = gerarPeca(proximoId);
    printf("Nova peça inserida: [%c %d]\n", f->fila[f->tras].tipo, f->fila[f->tras].id);
    f->tras = (f->tras + 1) % TAMANHO_FILA;
    f->qtd++;
}

int main() {
    srand(time(NULL));
    Fila fila;
    inicializarFila(&fila);
    int proximoId = TAMANHO_FILA;
    int opcao;

    do {
        exibirFila(&fila);
        printf("\nOpções de ação:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                jogarPeca(&fila);
                break;
            case 2:
                inserirPeca(&fila, proximoId++);
                break;
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while(opcao != 0);

    return 0;
}
