#ifndef BD_H
#define BD_H

#include "partida.c"
#include "time.c"

//Cria a lista encadeada e nó para o BDTimes
typedef struct No_T{
    Times times;
    struct No_T *next;
}No_T;

typedef struct {
    No_T *first;
}BDTime;

//Cria a lista encadeada e nó para o BDPartida
typedef struct No_P{
    Partidas partidas;
    struct No_P *next;
}No_P;

typedef struct {
    No_P *first;
}BDPartida;


int conta_linhas(char *p);

//Funções que criam espaço para o banco de dados
BDTime *criar_bdT(char *p);
BDPartida *criar_bdP(const int x, char *p);

//Insere os dados no banco
void *inserir_dados();

//Calcula e insere dado no banco de dados
void calcula_estatistica(const int qtd_partidas, BDTime *bd_times, BDPartida *bd_partidas);

//Ordenação
void ordena_times(BDTime *bd_times);

//Funções p/ liberar memória
void liberar_bd_times(BDTime *bd_times);
void liberar_bd_partidas(BDPartida *bd_partidas);

#endif