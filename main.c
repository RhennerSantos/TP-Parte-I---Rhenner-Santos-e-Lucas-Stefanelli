#include "bd.h" 
#include "menu.h"
#include <stdio.h>


int main()
{
    //Obtém os arquivos csv
    char *arq_times = "times.csv";
    char *arq_partidas = "partidas_completo.csv";

    //Retorna um número para inserir no vetor estático e para facilitar a iteração do vetor
    const int linhas_times = conta_linhas(arq_times);
    const int linhas_partidas = conta_linhas(arq_partidas);
    
    //Cria e preenche o banco de dados de Times e Partidas
    Times *bd_times = criar_bdT(linhas_times, arq_times);
    Partidas *bd_partidas = criar_bdP(linhas_partidas, arq_partidas);
    
    //Exibi o menu
    exibir_menu();

    return 0;
}

