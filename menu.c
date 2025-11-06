#include "menu.h" 
#include "bd.h" 
#include <stdio.h>
#include <stdlib.h>

void limpa_tela()
{
    system("clear");
}



void mostrar_classificação(const int qtd_times, Times *bd_times, Partidas *bd_partidas)
{
    limpa_tela();
    //TEM QUE ALINHAR ISSO AINDA
    printf("ID\tTime\t\t\tV\tE\tD\tGM\tGS\tS\tPG\n");
    for (int i = 0; i < qtd_times-1; i++)
    {
        printf("%d", bd_times[i].ID);
        printf("\t%s", bd_times[i].nome);
        printf("\t\t\t%d", bd_times[i].status.wins);
        printf("\t%d", bd_times[i].status.lose);
        printf("\t%d", bd_times[i].status.draw);
        printf("\t%d", bd_times[i].status.w_score);
        printf("\t%d", bd_times[i].status.l_score);
        printf("\t%d", bd_times[i].status.saldo);
        printf("\t%d\n", bd_times[i].status.pts_ganho);
    }
    printf("\n\n\n");
}

void exibir_menu(const int qtd_times, const int qtd_partidas, Times *bd_times, Partidas *bd_partidas)
{
    char escolha;
    while(escolha != 'Q' && escolha != 'q')
    {
    printf("Bem-vindo ao sistema de gerenciamento de partidas!\n");
    printf("Digie um número para prosseguir: \n");
    printf("1 - Consultar time\n"
           "2 - Consultar partidas\n"
           "6 - Imprimir tabela de classificação\n"
           "Q - Sair\n");
    scanf("%c", &escolha);
    
    switch(escolha)
    {
        //verificar depois se a lista está vazia pela qtd_times e qtd_partidas
        //se estiver, mostre um aviso em vez de executar a função
        case '1': //consultar_time();
        case '2': //consultar_partidas();
        case '6': mostrar_classificação(qtd_times, bd_times, bd_partidas); break;
        case 'Q': printf("Você escolheu sair do sistema"); break;
        case 'q': printf("Você escolheu sair do sistema"); break;
        default: printf("Não existe essa opção\n");
    }
    }
}
