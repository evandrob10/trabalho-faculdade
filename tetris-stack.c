#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_FILA 5
#define TAMANHO_PILHA 3
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

typedef struct {
    Peca pilha[TAMANHO_PILHA];
    int topo;
} Pilha;

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

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

void exibirEstado(Fila *f, Pilha *p) {
    printf("\nFila de peças:\n");
    for(int i = 0; i < f->qtd; i++) {
        int indice = (f->frente + i) % TAMANHO_FILA;
        printf("[%c %d] ", f->fila[indice].tipo, f->fila[indice].id);
    }
    printf("\nPilha de reserva (Topo -> Base):\n");
    if(p->topo == -1) printf("Vazia");
    else {
        for(int i = p->topo; i >= 0; i--) {
            printf("[%c %d] ", p->pilha[i].tipo, p->pilha[i].id);
        }
    }
    printf("\n");
}

void jogarPeca(Fila *f, int *proximoId) {
    if(f->qtd == 0) return;
    Peca jogada = f->fila[f->frente];
    printf("Peça jogada: [%c %d]\n", jogada.tipo, jogada.id);
    f->frente = (f->frente + 1) % TAMANHO_FILA;
    f->qtd--;
    f->fila[f->tras] = gerarPeca((*proximoId)++);
    f->tras = (f->tras + 1) % TAMANHO_FILA;
    f->qtd++;
}

void reservarPeca(Fila *f, Pilha *p, int *proximoId) {
    if(p->topo == TAMANHO_PILHA - 1) {
        printf("Pilha de reserva cheia!\n");
        return;
    }
    Peca reservada = f->fila[f->frente];
    p->topo++;
    p->pilha[p->topo] = reservada;
    printf("Peça reservada: [%c %d]\n", reservada.tipo, reservada.id);
    f->frente = (f->frente + 1) % TAMANHO_FILA;
    f->qtd--;
    f->fila[f->tras] = gerarPeca((*proximoId)++);
    f->tras = (f->tras + 1) % TAMANHO_FILA;
    f->qtd++;
}

void usarPecaReserva(Pilha *p) {
    if(p->topo == -1) {
        printf("Pilha de reserva vazia!\n");
        return;
    }
    Peca usada = p->pilha[p->topo];
    printf("Peça usada da reserva: [%c %d]\n", usada.tipo, usada.id);
    p->topo--;
}

void trocarPeças(Fila *f, Pilha *p) {
    if(f->qtd == 0 || p->topo == -1) {
        printf("Não é possível trocar: fila ou pilha vazia.\n");
        return;
    }
    Peca temp = f->fila[f->frente];
    f->fila[f->frente] = p->pilha[p->topo];
    p->pilha[p->topo] = temp;
    printf("Troca realizada entre frente da fila e topo da pilha.\n");
}

void trocaMultipla(Fila *f, Pilha *p) {
    if(f->qtd < 3 || p->topo < 2) {
        printf("Não há peças suficientes para troca múltipla.\n");
        return;
    }
    for(int i = 0; i < 3; i++) {
        int idxFila = (f->frente + i) % TAMANHO_FILA;
        Peca temp = f->fila[idxFila];
        f->fila[idxFila] = p->pilha[p->topo - i];
        p->pilha[p->topo - i] = temp;
    }
    printf("Troca múltipla realizada entre as 3 primeiras da fila e as 3 da pilha.\n");
}

int main() {
    srand(time(NULL));
    Fila fila;
    Pilha pilha;
    int proximoId = TAMANHO_FILA;
    int opcao;

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    do {
        exibirEstado(&fila, &pilha);
        printf("\nOpções disponíveis:\n");
        printf("1 - Jogar peça da frente da fila\n");
        printf("2 - Enviar peça da fila para a pilha de reserva\n");
        printf("3 - Usar peça da pilha de reserva\n");
        printf("4 - Trocar peça da frente da fila com topo da pilha\n");
        printf("5 - Trocar os 3 primeiros da fila com 3 da pilha\n");
        printf("0 - Sair\n");
        printf("Opção escolhida: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: jogarPeca(&fila, &proximoId); break;
            case 2: reservarPeca(&fila, &pilha, &proximoId); break;
            case 3: usarPecaReserva(&pilha); break;
            case 4: trocarPeças(&fila, &pilha); break;
            case 5: trocaMultipla(&fila, &pilha); break;
            case 0: printf("Saindo do programa...\n"); break;
            default: printf("Opção inválida! Tente novamente.\n");
        }
    } while(opcao != 0);

    return 0;
}
