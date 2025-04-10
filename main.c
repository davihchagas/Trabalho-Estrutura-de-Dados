#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processos.h"

int main() {
    FILE *arquivo;
    int capacidade = 1000;
    int tamanho = 0;
    char linha[2048];
    char *sp;

    Processos *processos = malloc(capacidade * sizeof(Processos));
    if (!processos) {
        printf("Erro de alocação de memória.\n");
        return 1;
    }

    arquivo = fopen("processos.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        free(processos);
        return 1;
    }

    fgets(linha, sizeof(linha), arquivo);

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (tamanho >= capacidade) {
            capacidade *= 2;
            Processos *temp = realloc(processos, capacidade * sizeof(Processos));
            if (!temp) {
                printf("Erro ao realocar memória.\n");
                free(processos);
                fclose(arquivo);
                return 1;
            }
            processos = temp;
        }

        sp = strtok(linha, ",");
        if (sp) strcpy(processos[tamanho].id, sp);

        sp = strtok(NULL, ",");
        if (sp) strcpy(processos[tamanho].numero, sp);

        sp = strtok(NULL, ",");
        if (sp) strcpy(processos[tamanho].data, sp);

        sp = strtok(NULL, "}");
        if (sp) strcpy(processos[tamanho].classe, sp);

        sp = strtok(NULL, "}");
        if (sp) strcpy(processos[tamanho].assunto, sp);

        sp = strtok(NULL, ",");

        sp = strtok(NULL, ",");
        processos[tamanho].eleicao = atoi(sp);

        tamanho++;
    }

    fclose(arquivo);

    // Função 3
    int qtdClasse = ContarProcessosPorClasse(processos, tamanho, "11531");
    printf("\nTotal de processos vinculados ao id_classe 11531: %d\n", qtdClasse);

    // Função 4
    ContarAssuntos(processos, tamanho);

    // Função 5
    Cabecalho();
    ListarAssuntos(processos, tamanho);

    // Função 6
    int qtdDias = QntDias(processos[1]);
    printf("\n\nO processo de ID %s esta em tramitacao ha %d dias\n", processos[1].id, qtdDias);

    free(processos);
    return 0;
}
