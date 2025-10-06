#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20

typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

int comparacoes = 0;

void mostrarComponentes(Componente comp[], int n) {
    printf("\nComponentes:\n");
    for (int i = 0; i < n; i++) {
        printf("%d. Nome: %s | Tipo: %s | Prioridade: %d\n",
               i + 1, comp[i].nome, comp[i].tipo, comp[i].prioridade);
    }
}

void bubbleSortNome(Componente comp[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (strcmp(comp[j].nome, comp[j + 1].nome) > 0) {
                Componente temp = comp[j];
                comp[j] = comp[j + 1];
                comp[j + 1] = temp;
            }
        }
    }
}

void insertionSortTipo(Componente comp[], int n) {
    comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente key = comp[i];
        int j = i - 1;
        while (j >= 0) {
            comparacoes++;
            if (strcmp(comp[j].tipo, key.tipo) > 0) {
                comp[j + 1] = comp[j];
                j--;
            } else break;
        }
        comp[j + 1] = key;
    }
}

void selectionSortPrioridade(Componente comp[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (comp[j].prioridade < comp[min_idx].prioridade)
                min_idx = j;
        }
        if (min_idx != i) {
            Componente temp = comp[i];
            comp[i] = comp[min_idx];
            comp[min_idx] = temp;
        }
    }
}

int buscaBinariaPorNome(Componente comp[], int n, char chave[]) {
    int inicio = 0, fim = n - 1;
    comparacoes = 0;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoes++;
        int cmp = strcmp(comp[meio].nome, chave);
        if (cmp == 0) return meio;
        else if (cmp < 0) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

int main() {
    Componente comp[MAX_COMPONENTES];
    int total = 0, opcao;
    char chave[30];

    printf("Cadastro de componentes (max %d)\n", MAX_COMPONENTES);
    do {
        if (total >= MAX_COMPONENTES) break;
        printf("\nComponente %d\n", total + 1);
        printf("Nome: ");
        fgets(comp[total].nome, 30, stdin);
        comp[total].nome[strcspn(comp[total].nome, "\n")] = '\0';
        printf("Tipo: ");
        fgets(comp[total].tipo, 20, stdin);
        comp[total].tipo[strcspn(comp[total].tipo, "\n")] = '\0';
        printf("Prioridade (1-10): ");
        scanf("%d", &comp[total].prioridade);
        while(getchar() != '\n');
        total++;
        if(total < MAX_COMPONENTES) {
            printf("Deseja cadastrar outro? (1=Sim,0=Nao): ");
            scanf("%d", &opcao);
            while(getchar() != '\n');
        } else opcao = 0;
    } while(opcao == 1);

    do {
        printf("\n--- Menu de Ordenacao e Busca ---\n");
        printf("1. Bubble Sort por Nome\n2. Insertion Sort por Tipo\n3. Selection Sort por Prioridade\n4. Busca Binaria por Nome\n0. Sair\nEscolha: ");
        scanf("%d", &opcao);
        while(getchar() != '\n');
        clock_t start, end;
        double tempo;
        int indice;
        switch(opcao) {
            case 1:
                start = clock();
                bubbleSortNome(comp, total);
                end = clock();
                tempo = ((double)(end - start))/CLOCKS_PER_SEC;
                mostrarComponentes(comp, total);
                printf("Comparacoes: %d | Tempo: %.6f s\n", comparacoes, tempo);
                break;
            case 2:
                start = clock();
                insertionSortTipo(comp, total);
                end = clock();
                tempo = ((double)(end - start))/CLOCKS_PER_SEC;
                mostrarComponentes(comp, total);
                printf("Comparacoes: %d | Tempo: %.6f s\n", comparacoes, tempo);
                break;
            case 3:
                start = clock();
                selectionSortPrioridade(comp, total);
                end = clock();
                tempo = ((double)(end - start))/CLOCKS_PER_SEC;
                mostrarComponentes(comp, total);
                printf("Comparacoes: %d | Tempo: %.6f s\n", comparacoes, tempo);
                break;
            case 4:
                printf("Digite o nome do componente-chave: ");
                fgets(chave, 30, stdin);
                chave[strcspn(chave, "\n")] = '\0';
                start = clock();
                indice = buscaBinariaPorNome(comp, total, chave);
                end = clock();
                tempo = ((double)(end - start))/CLOCKS_PER_SEC;
                if(indice != -1)
                    printf("Componente encontrado: %s | Tipo: %s | Prioridade: %d\n", comp[indice].nome, comp[indice].tipo, comp[indice].prioridade);
                else
                    printf("Componente nao encontrado.\n");
                printf("Comparacoes: %d | Tempo: %.6f s\n", comparacoes, tempo);
                break;
            case 0: break;
            default: printf("Opcao invalida!\n");
        }
    } while(opcao != 0);

    printf("Saindo do sistema.\n");
    return 0;
}
