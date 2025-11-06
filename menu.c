#include "menu.h" 
#include "bd.h" 
#include <stdio.h>
#include <stdlib.h>


void exibir_menu()
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
        case '1': //consultar_time();
        case '2': //consultar_partidas();
        case '6': //mostrar_classificação();
        
        case 'Q': printf("Você escolheu sair do sistema"); break;
        case 'q': printf("Você escolheu sair do sistema"); break;
        default: printf("Não existe essa opção\n");
    }
    }
}