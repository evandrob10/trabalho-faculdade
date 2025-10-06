#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_NOME 30
#define MAX_COR 10
#define MAX_MISSAO_LEN 200

typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
} Territorio;

int lerInteiro(const char *prompt, int min, int max) {
    char buf[128];
    long val;
    char *end;
    while (1) {
        printf("%s", prompt);
        if (!fgets(buf, sizeof(buf), stdin)) {
            clearerr(stdin);
            continue;
        }
        val = strtol(buf, &end, 10);
        if (end == buf) {
            printf("Entrada inválida. Digite um número.\n");
            continue;
        }
        while (*end != '\0' && isspace((unsigned char)*end)) end++;
        if (*end != '\0' && *end != '\n') {
            printf("Entrada inválida. Digite apenas o número.\n");
            continue;
        }
        if (val < min || val > max) {
            printf("Valor fora do intervalo (%d - %d). Tente novamente.\n", min, max);
            continue;
        }
        return (int)val;
    }
}

void cadastrarTerritorios(Territorio *mapa, int qtd) {
    char buffer[256];
    for (int i = 0; i < qtd; i++) {
        printf("\nCadastro do território %d\n", i + 1);
        printf("Nome: ");
        if (!fgets(buffer, sizeof(buffer), stdin)) buffer[0]='\0';
        buffer[strcspn(buffer, "\n")] = '\0';
        strncpy(mapa[i].nome, buffer, MAX_NOME);
        mapa[i].nome[MAX_NOME-1] = '\0';
        printf("Cor do exército: ");
        if (!fgets(buffer, sizeof(buffer), stdin)) buffer[0]='\0';
        buffer[strcspn(buffer, "\n")] = '\0';
        strncpy(mapa[i].cor, buffer, MAX_COR);
        mapa[i].cor[MAX_COR-1] = '\0';
        mapa[i].tropas = lerInteiro("Quantidade de tropas: ", 0, 1000000);
    }
}

void exibirMapa(const Territorio *mapa, int qtd) {
    printf("\n=== MAPA DE TERRITÓRIOS ===\n");
    for (int i = 0; i < qtd; i++) {
        printf("%2d. %s | Cor: %s | Tropas: %d\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("===========================\n");
}

void atribuirMissao(char *destino, char *missoes[], int totalMissoes) {
    int idx = rand() % totalMissoes;
    strcpy(destino, missoes[idx]);
}

void exibirMissao(const char *missao) {
    printf("Sua missão: %s\n", missao);
}

int contarTerritoriosCor(const Territorio *mapa, int tamanho, const char *cor) {
    int c = 0;
    for (int i = 0; i < tamanho; i++) {
        if (strcasecmp(mapa[i].cor, cor) == 0) c++;
    }
    return c;
}

int somarTropasCor(const Territorio *mapa, int tamanho, const char *cor) {
    int soma = 0;
    for (int i = 0; i < tamanho; i++) {
        if (strcasecmp(mapa[i].cor, cor) == 0) soma += mapa[i].tropas;
    }
    return soma;
}

int somarTropasJogador(const Territorio *mapa, int tamanho, const char *corJogador) {
    return somarTropasCor(mapa, tamanho, corJogador);
}

int verificarMissao(const char *missao, const Territorio *mapa, int tamanho, const char *corDoJogador) {
    if (strstr(missao, "Conquistar 3") != NULL) {
        int cont = contarTerritoriosCor(mapa, tamanho, corDoJogador);
        if (cont >= 3) return 1;
        return 0;
    }
    if (strstr(missao, "Eliminar todas as tropas da cor ") != NULL) {
        const char *padrao = "Eliminar todas as tropas da cor ";
        const char *p = strstr(missao, padrao);
        if (p) {
            p += strlen(padrao);
            char corAlvo[MAX_COR];
            strncpy(corAlvo, p, MAX_COR-1);
            corAlvo[MAX_COR-1] = '\0';
            corAlvo[strcspn(corAlvo, "\n")] = '\0';
            int tropasAlvo = somarTropasCor(mapa, tamanho, corAlvo);
            if (tropasAlvo == 0) return 1;
            return 0;
        }
    }
    if (strstr(missao, "Atingir 20") != NULL) {
        int tot = somarTropasJogador(mapa, tamanho, corDoJogador);
        if (tot >= 20) return 1;
        return 0;
    }
    if (strstr(missao, "Controlar maioria") != NULL) {
        int cont = contarTerritoriosCor(mapa, tamanho, corDoJogador);
        if (cont > tamanho / 2) return 1;
        return 0;
    }
    return 0;
}

void atacar(Territorio *atacante, Territorio *defensor) {
    if (strcasecmp(atacante->cor, defensor->cor) == 0) {
        printf("Erro: não é possível atacar um território da mesma cor.\n");
        return;
    }
    if (atacante->tropas <= 1) {
        printf("Erro: atacante não tem tropas suficientes (mínimo 2 para tentar atacar).\n");
        return;
    }
    int dadoA = (rand() % 6) + 1;
    int dadoD = (rand() % 6) + 1;
    printf("\nRolagem: %s (%d) x %s (%d)\n", atacante->nome, dadoA, defensor->nome, dadoD);
    if (dadoA > dadoD) {
        printf("Atacante venceu!\n");
        int transferencia = atacante->tropas / 2;
        if (transferencia < 1) transferencia = 1;
        atacante->tropas -= transferencia;
        defensor->tropas = transferencia;
        strncpy(defensor->cor, atacante->cor, MAX_COR-1);
        defensor->cor[MAX_COR-1] = '\0';
    } else {
        printf("Defensor resistiu!\n");
        atacante->tropas -= 1;
        if (atacante->tropas < 0) atacante->tropas = 0;
    }
}

void liberarMemoria(Territorio *mapa, char **missoesJogadores, int numJogadores) {
    if (mapa) free(mapa);
    if (missoesJogadores) {
        for (int i = 0; i < numJogadores; i++) {
            if (missoesJogadores[i]) free(missoesJogadores[i]);
        }
        free(missoesJogadores);
    }
}

int main() {
    srand((unsigned)time(NULL));
    char *missoesDisponiveis[] = {
        "Conquistar 3 territorios",
        "Eliminar todas as tropas da cor Vermelho",
        "Atingir 20 tropas",
        "Controlar maioria dos territorios",
        "Eliminar todas as tropas da cor Verde"
    };
    int totalMissoes = sizeof(missoesDisponiveis) / sizeof(missoesDisponiveis[0]);
    printf("=== WAR ESTRUTURADO: MISSÕES E ATAQUES ===\n\n");
    int numJogadores = 2;
    char coresJogadores[2][MAX_COR];
    char buffer[128];
    for (int j = 0; j < numJogadores; j++) {
        printf("Jogador %d, digite a cor que identificará seus territorios (ex: Azul, Vermelho): ", j + 1);
        if (!fgets(buffer, sizeof(buffer), stdin)) buffer[0]='\0';
        buffer[strcspn(buffer, "\n")] = '\0';
        strncpy(coresJogadores[j], buffer, MAX_COR-1);
        coresJogadores[j][MAX_COR-1] = '\0';
    }
    int qtdTerritorios = lerInteiro("\nQuantos territorios deseja cadastrar? ", 1, 1000);
    Territorio *mapa = (Territorio *) calloc(qtdTerritorios, sizeof(Territorio));
    if (!mapa) {
        printf("Erro: falha na alocacao de memoria.\n");
        return 1;
    }
    cadastrarTerritorios(mapa, qtdTerritorios);
    char **missoesJogadores = (char **) malloc(sizeof(char *) * numJogadores);
    if (!missoesJogadores) {
        printf("Erro ao alocar memória para missões.\n");
        free(mapa);
        return 1;
    }
    for (int j = 0; j < numJogadores; j++) {
        missoesJogadores[j] = (char *) malloc(MAX_MISSAO_LEN);
        if (!missoesJogadores[j]) {
            printf("Erro ao alocar memória para missão do jogador %d.\n", j + 1);
            for (int k = 0; k < j; k++) free(missoesJogadores[k]);
            free(missoesJogadores);
            free(mapa);
            return 1;
        }
        atribuirMissao(missoesJogadores[j], missoesDisponiveis, totalMissoes);
    }
    printf("\n--- MISSÕES SORTEADAS ---\n");
    for (int j = 0; j < numJogadores; j++) {
        printf("Jogador %d (cor %s): ", j + 1, coresJogadores[j]);
        exibirMissao(missoesJogadores[j]);
    }
    printf("-------------------------\n");
    int turno = 0;
    int vencedor = -1;
    do {
        int jogadorAtual = turno % numJogadores;
        printf("\n\nTurno do Jogador %d (cor %s)\n", jogadorAtual + 1, coresJogadores[jogadorAtual]);
        exibirMapa(mapa, qtdTerritorios);
        printf("Opções:\n1 - Atacar\n0 - Passar / Sair do jogo\n");
        int opc = lerInteiro("Escolha: ", 0, 1);
        if (opc == 1) {
            int idxAt, idxDf;
            while (1) {
                idxAt = lerInteiro("Número do território atacante: ", 1, qtdTerritorios) - 1;
                if (strcasecmp(mapa[idxAt].cor, coresJogadores[jogadorAtual]) != 0) {
                    printf("Esse território não pertence a você. Escolha um território da cor %s.\n", coresJogadores[jogadorAtual]);
                    continue;
                }
                if (mapa[idxAt].tropas <= 1) {
                    printf("Território selecionado não tem tropas suficientes para atacar (min 2). Escolha outro.\n");
                    continue;
                }
                break;
            }
            idxDf = lerInteiro("Número do território defensor: ", 1, qtdTerritorios) - 1;
            if (idxAt == idxDf) {
                printf("Um território não pode atacar a si mesmo.\n");
            } else {
                if (strcasecmp(mapa[idxAt].cor, mapa[idxDf].cor) == 0) {
                    printf("Você não pode atacar um território da mesma cor.\n");
                } else {
                    atacar(&mapa[idxAt], &mapa[idxDf]);
                }
            }
        } else {
            printf("Jogador %d passou o turno.\n", jogadorAtual + 1);
        }
        if (verificarMissao(missoesJogadores[jogadorAtual], mapa, qtdTerritorios, coresJogadores[jogadorAtual])) {
            vencedor = jogadorAtual;
            break;
        }
        turno++;
    } while (1);
    if (vencedor >= 0) {
        printf("\n\n=== MISSÃO CUMPRIDA ===\n");
        printf("Parabéns! Jogador %d (cor %s) cumpriu a missão:\n%s\n", vencedor + 1, coresJogadores[vencedor], missoesJogadores[vencedor]);
    } else {
        printf("Fim do jogo sem vencedor por missão.\n");
    }
    liberarMemoria(mapa, missoesJogadores, numJogadores);
    printf("\nMemória liberada. Encerrando.\n");
    return 0;
}
