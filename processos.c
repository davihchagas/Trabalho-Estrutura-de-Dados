#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processos.h"

void Cabecalho() {
  printf("\nid;numero;data_ajuizamento;id_classe;id_assunto;ano_eleicao\n");
}

void limparString(char *str) {
  int i, j = 0;
  char limpa[256];  

  for (i = 0; str[i] != '\0'; i++) {
      if (str[i] != '{' && str[i] != '}'&& str[i] != '"') {
          limpa[j++] = str[i];
      }
  }

  limpa[j] = '\0';
  strcpy(str, limpa);
}

int ContarProcessosPorClasse(Processos processos[], int tamanho, const char *classeBuscada) {
  int total = 0;

  for (int i = 0; i < tamanho; i++) {
      char copiaClasse[256];
      strcpy(copiaClasse, processos[i].classe);
      limparString(copiaClasse);

      char *token = strtok(copiaClasse, ",");
      while (token != NULL) {
          if (strcmp(token, classeBuscada) == 0) {
              total++;
              break;
          }
          token = strtok(NULL, ",");
      }
  }

  return total;
}

void ContarAssuntos(Processos processos[], int tamanho) {
  char unicos[100][20];
  int totalUnicos = 0;

  for (int i = 0; i < tamanho; i++) {
      char assuntoCopia[256];
      strcpy(assuntoCopia, processos[i].assunto);
      limparString(assuntoCopia);

      char *token = strtok(assuntoCopia, ",");
      while (token != NULL) {
          int encontrado = 0;

          for (int j = 0; j < totalUnicos; j++) {
              if (strcmp(token, unicos[j]) == 0) {
                  encontrado = 1;
                  break;
              }
          }

          if (!encontrado) {
              strcpy(unicos[totalUnicos], token);
              totalUnicos++;
          }

          token = strtok(NULL, ",");
      }
  }

  printf("\nTotal de id_assuntos distintos: %d\n", totalUnicos);
}


void ListarAssuntos(Processos processos[], int tamanho) {
  for (int i = 0; i < tamanho; i++) {
    char dataCopia[256];
    strcpy(dataCopia, processos[i].assunto);

    int countVirgulas = 0;
    for (int j = 0; dataCopia[j] != '\0'; j++) {
      if (dataCopia[j] == ',') {
        countVirgulas++;
      }
    }

    if (countVirgulas > 1) { 
      printf("\n%s,%s,%s%s},%s},%d", processos[i].id, processos[i].numero, processos[i].data, processos[i].assunto, processos[i].classe, processos[i].eleicao);
    }
  }
}

int ehBissexto(int ano) {
  return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

int diasDesdeZero(int dia, int mes, int ano) {
  int diasPorMes[] = {31,28,31,30,31,30,31,31,30,31,30,31};
  int totalDias = 0;

  for (int i = 0; i < ano; i++) {
      totalDias += ehBissexto(i) ? 366 : 365;
  }

  if (ehBissexto(ano)) {
      diasPorMes[1] = 29;
  }

  for (int i = 0; i < mes - 1; i++) {
      totalDias += diasPorMes[i];
  }

  totalDias += dia;

  return totalDias;
}

int QntDias(Processos processos) {
  int i = 1, ano, mes, dia;
  char dataCopia[50];
  strcpy(dataCopia, processos.data);

  char *resultado = strtok(dataCopia, "-");
  ano = atoi(resultado);

  resultado = strtok(NULL, "-");
  mes = atoi(resultado);

  resultado = strtok(NULL, " ");
  dia = atoi(resultado);

  int diaAtual =11;
  int mesAtual = 4;
  int anoAtual = 2025;

  int diasProcesso = diasDesdeZero(dia, mes, ano);
  int diasHoje = diasDesdeZero(diaAtual, mesAtual, anoAtual);

  return (diasHoje - diasProcesso);
}