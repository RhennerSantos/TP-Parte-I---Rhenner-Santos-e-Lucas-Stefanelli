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
    return count;
}

Times *criar_bdT(const int qtd_times, char* arq)
{
    //Aloca memória estaticamente para o banco de dados
    Times t[qtd_times -1];
    //aloca dinamicamente memória pro ponteiro
    Times *ptr_time = malloc(qtd_times * sizeof(Times));
    for (int i = 0; i < qtd_times; i++){
        ptr_time[i] = t[i]; 
    }
    
    //abre arquivo para começar a preencher o banco de dados
    FILE *csv = fopen(arq, "r");
    
    //pula a primeira linha do csv
    char linha[256];
    fgets(linha, sizeof(linha), csv);
 
    //preenche o banco de dados
    for (int i = 0; i < qtd_times; i++){
    fscanf(csv, "%d, %s", &ptr_time[i].ID, ptr_time[i].nome);
    }
    
    //SÓ PARA TESTAR SE AS INFORMAÇÕES ESTÃO PRESENTES NO BANCO
    printf("%d", ptr_time[8].ID);
    printf("%s", ptr_time[8].nome);

    fclose(csv);
    return ptr_time;
}

Partidas *criar_bdP(const int qtd_partidas, char* arq)
{
    //Aloca memória estaticamente para o banco de dados
    Partidas p[qtd_partidas-1];
    //Aloca memória dinamicamente pro ponteiro
    Partidas *ptr_partida = malloc(qtd_partidas * sizeof(Partidas));
    for (int i = 0; i < qtd_partidas; i++){
        ptr_partida[i] = p[i]; 
    }
    
    //abre arquivo para começar a preencher o banco de dados
    FILE *csv = fopen(arq, "r");

    //pula a primeira linha do csv
    char linha[256];
    fgets(linha, sizeof(linha), csv);
    
    //Preenche o banco de dados
    for (int i = 0; i < qtd_partidas; i++){
    fscanf(csv, "%d, %d, %d, %d, %d", &ptr_partida[i].ID, &ptr_partida[i].time1ID, &ptr_partida[i].time2ID, 
    &ptr_partida[i].gols1, &ptr_partida[i].gols2); 
    }

    //SÓ PARA TESTAR SE AS INFORMAÇÕES ESTÃO PRESENTES NO BANCO
    printf("\n \n");
    printf("%d", ptr_partida[0].ID);
    printf("%d", ptr_partida[0].time1ID);
    printf("%d", ptr_partida[0].time2ID);
    printf("%d", ptr_partida[0].gols1);
    printf("%d", ptr_partida[0].gols2);
    printf("\n \n");

    fclose(csv);
    return ptr_partida;
}

