#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processos.h"

void Cabecalho() {
  printf("\n\nid;numero;data_ajuizamento;id_classe;id_assunto;ano_eleicao\n");
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

Processos* CarregaProcessos(const char *arquivo, int *tamanho) {
  FILE *fp = fopen(arquivo, "r");
  if (!fp) {
      printf("Erro ao abrir o arquivo %s.\n", arquivo);
      return NULL;
  }

  int capacidade = 100;
  *tamanho = 0;
  Processos *dados = malloc(capacidade * sizeof(Processos));
  if (!dados) {
      printf("Erro de alocação de memória.\n");
      fclose(fp);
      return NULL;
  }

  char linha[2048];
  fgets(linha, sizeof(linha), fp);

  while (fgets(linha, sizeof(linha), fp)) {
      if (*tamanho >= capacidade) {
          capacidade *= 2;
          Processos *temp = realloc(dados, capacidade * sizeof(Processos));
          if (!temp) {
              printf("Erro ao realocar memória.\n");
              free(dados);
              fclose(fp);
              return NULL;
          }
          dados = temp;
      }

      char *sp = strtok(linha, ",");
      if (sp) strcpy(dados[*tamanho].id, sp);

      sp = strtok(NULL, ",");
      if (sp) strcpy(dados[*tamanho].numero, sp);

      sp = strtok(NULL, ",");
      if (sp) strcpy(dados[*tamanho].data, sp);

      sp = strtok(NULL, "}");
      if (sp) strcpy(dados[*tamanho].classe, sp);

      sp = strtok(NULL, "}");
      if (sp) strcpy(dados[*tamanho].assunto, sp);

      sp = strtok(NULL, ",");
      if (sp) dados[*tamanho].eleicao = atoi(sp);

      (*tamanho)++;
  }



  fclose(fp);
  return dados;
}

Processos* OrdenarPorId(Processos *processos, int tamanho) {
  Processos *ordenado = malloc(tamanho * sizeof(Processos));
  if (!ordenado) {
      printf("Erro ao alocar memória.\n");
      return NULL;
  }

  memcpy(ordenado, processos, tamanho * sizeof(Processos));

  for (int i = 0; i < tamanho - 1; i++) {
      for (int j = i + 1; j < tamanho; j++) {
          if (strcmp(ordenado[i].id, ordenado[j].id) > 0) {
              Processos temp = ordenado[i];
              ordenado[i] = ordenado[j];
              ordenado[j] = temp;
          }
      }
  }

  FILE *fp = fopen("ordenado_por_id.csv", "w");
  if (!fp) {
      printf("Erro ao criar arquivo ordenado_por_id.csv\n");
      free(ordenado);
      return NULL;
  }

  fprintf(fp, "id;numero;data_ajuizamento;id_classe;id_assunto;ano_eleicao\n");
  for (int i = 0; i < tamanho; i++) {
      fprintf(fp, "%s,%s,%s,%s}%s},%d\n",
              ordenado[i].id, ordenado[i].numero, ordenado[i].data,
              ordenado[i].classe, ordenado[i].assunto, ordenado[i].eleicao);
  }

  fclose(fp);
  return ordenado;
}

Processos* OrdenarPorData(Processos *processos, int tamanho) {
  Processos *ordenado = malloc(tamanho * sizeof(Processos));
  if (!ordenado) {
      printf("Erro ao alocar memória.\n");
      return NULL;
  }

  memcpy(ordenado, processos, tamanho * sizeof(Processos));

  for (int i = 0; i < tamanho - 1; i++) {
      for (int j = i + 1; j < tamanho; j++) {
          if (strcmp(ordenado[i].data, ordenado[j].data) < 0) {
              Processos temp = ordenado[i];
              ordenado[i] = ordenado[j];
              ordenado[j] = temp;
          }
      }
  }

  FILE *fp = fopen("ordenado_por_data.csv", "w");
  if (!fp) {
      printf("Erro ao criar arquivo ordenado_por_data.csv\n");
      free(ordenado);
      return NULL;
  }

  fprintf(fp, "id;numero;data_ajuizamento;id_classe;id_assunto;ano_eleicao\n");
  for (int i = 0; i < tamanho; i++) {
      fprintf(fp, "%s,%s,%s,%s}%s},%d\n",
              ordenado[i].id, ordenado[i].numero, ordenado[i].data,
              ordenado[i].classe, ordenado[i].assunto, ordenado[i].eleicao);
  }

  fclose(fp);
  return ordenado;
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

  printf("\nTotal de id_assuntos distintos: %d", totalUnicos);
}


void ListarAssuntos(Processos processos[], int tamanho) {
  int contagem = 0;
  printf("\n\nid;id_assunto");
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
      contagem++;
      printf("\n%d- %s%s}\"", contagem,processos[i].id, processos[i].assunto);
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