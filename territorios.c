#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

void cadastrarTerritorios(struct Territorio* mapa, int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("\nCadastro do território %d:\n", i + 1);
        printf("Nome: ");
        scanf("%s", mapa[i].nome);
        printf("Cor do exército: ");
        scanf("%s", mapa[i].cor);
        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

void exibirTerritorios(struct Territorio* mapa, int qtd) {
    printf("\n=== LISTA DE TERRITÓRIOS ===\n");
    for (int i = 0; i < qtd; i++) {
        printf("%d. Nome: %s | Cor: %s | Tropas: %d\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\nVocê não pode atacar um território da mesma cor!\n");
        return;
    }

    if (atacante->tropas <= 1) {
        printf("\nO território atacante não tem tropas suficientes para atacar!\n");
        return;
    }

    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\nAtaque: %s (dado %d) x %s (dado %d)\n", atacante->nome, dadoAtacante, defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("O atacante venceu!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        atacante->tropas = atacante->tropas / 2;
    } else {
        printf("O defensor resistiu ao ataque!\n");
        atacante->tropas -= 1;
    }
}

void liberarMemoria(struct Territorio* mapa) {
    free(mapa);
}

int main() {
    srand(time(NULL));

    int qtd;
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &qtd);

    struct Territorio* mapa = (struct Territorio*) calloc(qtd, sizeof(struct Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    cadastrarTerritorios(mapa, qtd);

    int opcao;
    do {
        exibirTerritorios(mapa, qtd);
        printf("\n1 - Atacar\n0 - Sair\nEscolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            int iAtacante, iDefensor;
            printf("Escolha o número do território atacante: ");
            scanf("%d", &iAtacante);
            printf("Escolha o número do território defensor: ");
            scanf("%d", &iDefensor);

            if (iAtacante < 1 || iAtacante > qtd || iDefensor < 1 || iDefensor > qtd) {
                printf("Opção inválida!\n");
            } else if (iAtacante == iDefensor) {
                printf("Um território não pode atacar a si mesmo!\n");
            } else {
                atacar(&mapa[iAtacante - 1], &mapa[iDefensor - 1]);
            }
        }
    } while (opcao != 0);

    liberarMemoria(mapa);
    printf("\nMemória liberada. Encerrando o programa.\n");

    return 0;
}
