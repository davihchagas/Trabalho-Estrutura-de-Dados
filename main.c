#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processos.h"

int main() {
    int tamanho = 0;
    Processos *processos = CarregaProcessos("processos.csv", &tamanho);
    if (!processos) return 1;

    //Função 1
    OrdenarPorId(processos, tamanho);

    //Função 2
    OrdenarPorData(processos, tamanho);

    // Função 3
    int qtdClasse = ContarProcessosPorClasse(processos, tamanho, "12193");
    printf("\nTotal de processos vinculados ao id_classe 12193: %d\n", qtdClasse);

    // Função 4
    ContarAssuntos(processos, tamanho);

    // Função 5
    ListarAssuntos(processos, tamanho);

    // Função 6
    int qtdDias = QntDias(processos[1]);
    printf("\n\nO processo de ID %s esta em tramitacao ha %d dias\n", processos[1].id, qtdDias);

    free(processos);
    return 0;
}
