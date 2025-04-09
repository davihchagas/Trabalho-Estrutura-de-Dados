#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processos.h"

int main() {
  FILE *arquivo;
  Processos processos[15];
  arquivo = fopen("processos.csv", "r");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return 1;
    }

    char linha[2048];
    char *sp;
    int i = 0;

    fgets(linha, sizeof(linha), arquivo);

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
      sp = strtok(linha, ",");
      strcpy(processos[i].id, sp);

      sp = strtok(NULL, ",");
      strcpy(processos[i].numero, sp);

      sp = strtok(NULL, ",");
      strcpy(processos[i].data, sp);

      sp = strtok(NULL, "}");
      strcpy(processos[i].classe, sp);

      sp = strtok(NULL, "}");
      strcpy(processos[i].assunto, sp);

      sp = strtok(NULL, ",");
      processos[i].eleicao =  atoi(sp);

      i++;
    }

    //Função 3
    int qtdClasse = ContarProcessosPorClasse(processos, i, "11531");
    printf("\nTotal de processos vinculados ao id_classe 11531: %d\n", qtdClasse);

    //Função 4
    ContarAssuntos(processos, i);
    
    //Função 5
    Cabecalho();
    ListarAssuntos(processos, i);

    //Função 6
    int qtdDias = QntDias(processos[1]);
    printf("\n\nO processo de ID %s esta em tramitacao ha %d dias\n",processos[1].id, qtdDias);

    fclose(arquivo);

    system("pause");

  return 0;
}