#ifndef BD_H
#define BD_H

//BD_partida
typedef struct{
    int ID;
    int time1ID;
    int time2ID;
    int gols1;
    int gols2;
}Partidas;

//TAD_time
typedef struct{
    int ID;
    int wins;
    int draw;
    int lose;
    int w_score;
    int l_score;
    int saldo;
    int pts_ganho;
}Status;

//BD_time
typedef struct{
    int ID;
    char nome[400];
    Status status;
}Times;

int conta_linhas(char *p);

//Funções que criam espaço para o banco de dados
Times *criar_bdT(char *p);
Partidas *criar_bdP(const int x, char *p);

//Insere os dados no banco
void *inserir_dados();

//Calcula e insere dado no banco de dados
void calcula_estatistica(const int qtd_partidas, Times *bd_times, Partidas *bd_partidas);

#endif
