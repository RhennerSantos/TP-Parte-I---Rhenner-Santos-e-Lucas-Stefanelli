#include "bd.h" 
#include "menu.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    //Obtém os arquivos csv
    char *arq_times = "times.txt";
    char *arq_partidas = "partidas.txt";
    
    //Retorna um número para inserir no vetor estático e para facilitar a iteração do vetor
    const int linhas_partidas = conta_linhas(arq_partidas);
    
    //Cria e preenche o banco de dados de Times e Partidas
    BDTime *bd_times = criar_bdT(arq_times);
    BDPartida *bd_partidas = criar_bdP(linhas_partidas, arq_partidas);
    
    // //Calcula e armazena dados do TAD times que é contido no BDtimes
    calcula_estatistica(linhas_partidas, bd_times, bd_partidas);
    
    //Mostra a tela no terminal
    exibir_menu(linhas_partidas, bd_times, bd_partidas);
    
    //Libera os ponteiros do banco de dados
    free(bd_times);
    free(bd_partidas);
    return 0;
}







