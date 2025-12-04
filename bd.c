#include "bd.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int conta_linhas(char *arq)
{
    FILE *csv = fopen(arq, "r");
    int count = 0;
    char chr = 'a';
    
    //conta as linhas verificando o final \n delas
    while (chr != EOF)
    {
        if (chr == '\n')
        {
            count = count + 1;
        }
        chr = getc(csv);
    }
    fclose(csv); 
    return count -1;
}

BDTime *criar_bdT(char* arq)
{

    //aloca dinamicamente memória para um ponteiro para lista encadeada
    BDTime *ptr_time = malloc(sizeof(BDTime));
    ptr_time->first = NULL;
    
    //Cria um struct para ser inserido na lista encadeada
    Times atual; 
    
    //abre arquivo para começar a preencher o banco de dados
    FILE *csv = fopen(arq, "r");
    
    //pula a primeira linha do csv
    char linha[256];
    fgets(linha, sizeof(linha), csv);

    //altera o struct "atual" e insere ele nos nós 
    for (int i = 0; i < 10; i++){
    fscanf(csv, "%d, %s", &atual.ID, atual.nome);

    No_T *no = malloc(sizeof(No_T));
    no->times = atual;
    no->next = ptr_time->first;
    ptr_time->first = no;
    }

    fclose(csv);
    return ptr_time;
}

BDPartida *criar_bdP(const int qtd_partidas, char* arq)
{
    //aloca dinamicamente memória para um ponteiro para lista encadeada
    BDPartida *ptr_partida = malloc(sizeof(BDPartida));
    ptr_partida->first = NULL;
    
    //Cria um struct para ser inserido na lista encadeada
    Partidas atual; 
    
    //abre arquivo para começar a preencher o banco de dados
    FILE *csv = fopen(arq, "r");

    //pula a primeira linha do csv
    char linha[256];
    fgets(linha, sizeof(linha), csv);
    
    //Preenche o banco de dados
    for (int i = 0; i < qtd_partidas; i++){
    fscanf(csv, "%d, %d, %d, %d, %d", &atual.ID, &atual.time1ID, &atual.time2ID, 
    &atual.gols1, &atual.gols2); 
    
    No_P *no = malloc(sizeof(No_P));
    no->partidas = atual;
    no->next = ptr_partida->first;
    ptr_partida->first = no;
    }

    fclose(csv);
    return ptr_partida;
}

//Calcula as pontuações para inserir no TAD_Time
void calcula_estatistica(const int qtd_partidas, BDTime *bd_times, BDPartida *bd_partidas)
{
    //variáveis acumuladoras
    int win = 0;
    int defeat = 0;
    int draw = 0;
    int w_gols = 0;
    int l_gols = 0;
    //começa a contar as vitórias, derrotas e empates
    for (No_T *t = bd_times->first; t != NULL; t = t->next)
    {
        for (No_P *p = bd_partidas->first; p != NULL; p = p->next)
        {
            if(t->times.ID == p->partidas.time1ID)
            {
                if(p->partidas.gols1 > p->partidas.gols2)
                {
                    win++;
                } 
                else if (p->partidas.gols1 == p->partidas.gols2)
                {
                    draw++;
                }
                else
                {
                    defeat++;
                }
                w_gols += p->partidas.gols1;
                l_gols += p->partidas.gols2;
                
            }
            if(t->times.ID == p->partidas.time2ID)
            {
                if(p->partidas.gols1 < p->partidas.gols2)
                {
                    win++;
                } 
                else if (p->partidas.gols1 == p->partidas.gols2)
                {
                    draw++;
                }
                else
                {
                    defeat++;
                }
                w_gols += p->partidas.gols2;
                l_gols += p->partidas.gols1;
            }
        }
        //insere estatisticas no struct status
        t->times.status.wins = win;
        t->times.status.lose = defeat;
        t->times.status.draw = draw;
        t->times.status.w_score = w_gols;
        t->times.status.l_score = l_gols;
        t->times.status.saldo = w_gols - l_gols;
        t->times.status.pts_ganho = 3*win + draw;
        //reinicia as variáveis para calcular pro próximo time
        win = 0;
        draw = 0;
        defeat = 0;
        w_gols = 0;
        l_gols = 0;
    }      
}
