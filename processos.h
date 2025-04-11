#ifndef PROCESSOS_H
#define PROCESSOS_H

typedef struct {
  char id[50];
  char numero[50];
  char data[50];
  char classe[256];
  char assunto[256];
  int eleicao;
} Processos;

void limparString(char *str);

void Cabecalho();

Processos* CarregaProcessos(const char *nomeArquivo, int *tamanho);

//Ordenar, em ordem crescente, o conjunto de dados a partir do atributo “id”;
void OrdenarPorId(Processos *processos, int tamanho);

//Ordenar, em ordem decrescente, o conjunto de dados a partir do atributo “data_ajuizamento”;
void OrdenarPorData(Processos *processos, int tamanho);

//Contar quantos processos estão vinculados a um determinado “id_classe”;
int ContarProcessosPorClasse(Processos processos[], int tamanho, const char *classeBuscada);

//Identificar quantos “id_assuntos” constam nos processos presentes na base de dados; 
void ContarAssuntos(Processos processos[], int tamanho);

//Listar todos os processos que estão vinculados a mais de um assunto; e
void ListarAssuntos(Processos processos[], int tamanho);

//Indicar a quantos dias um processo está em tramitação na justiça.
int QntDias(Processos processos);
int ehBissexto(int ano);
int diasDesdeZero(int dia, int mes, int ano);

#endif