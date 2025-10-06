#include <stdio.h>
#include <string.h>

struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

int main() {
    struct Territorio territorios[5];
    int i;

    printf("=== CADASTRO DE TERRITÓRIOS ===\n\n");

    for (i = 0; i < 5; i++) {
        printf("Cadastro do território %d:\n", i + 1);
        fflush(stdin);

        printf("Digite o nome do território: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';

        printf("Digite a cor do exército: ");
        fgets(territorios[i].cor, sizeof(territorios[i].cor), stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
        getchar();
        printf("\n");
    }

    printf("=== LISTA DE TERRITÓRIOS CADASTRADOS ===\n\n");

    for (i = 0; i < 5; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exército: %s\n", territorios[i].cor);
        printf("Quantidade de Tropas: %d\n", territorios[i].tropas);
        printf("----------------------------------------\n");
    }

    return 0;
}
