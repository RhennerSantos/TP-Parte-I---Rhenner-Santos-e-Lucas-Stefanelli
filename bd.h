#ifndef BD_H
#define BD_H

// registro struct de partidas
typedef struct{
    int ID;
    int time1ID;
    int time2ID;
    int gols1;
    int gols2;
}Partidas;

// registro struct de times
typedef struct{
    int ID;
    char nome[400];
    //status; - > inserir quando for fazer o TAD times
}Times;

int conta_linhas();

// Funções que criam espaço para o banco de dados
Times *criar_bdT();
Partidas *criar_bdP();

void *inserir_dados();

#endif
