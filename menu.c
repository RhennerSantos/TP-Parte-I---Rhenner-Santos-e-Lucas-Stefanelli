#include "menu.h" 
#include "bd.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

void limpa_tela(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

bool inArray(int *arr, int alvo, int tamanho_arr){
    for (int i = 0; i < tamanho_arr; i++){
        if (arr[i] == alvo){
            return true;
        }
    }
    return false;
}

void lowercase(char *outro_time, char *nome_time, int tamanho_nome)
{
    for (int i = 0; i < tamanho_nome; i++)
    {
        outro_time[i] = tolower(outro_time[i]);
        nome_time[i] = tolower(nome_time[i]);
    }
}

void consultar_partidas(const int qtd_partidas, Times *bd_times, Partidas *bd_partidas){
    char escolha;
    int i, j = 0, tamanho_nome;
    char *nome_time = malloc(sizeof(char)*40);
    char *outro_time = malloc(sizeof(char)*40);
    int ids[10];

    limpa_tela();

    printf("Escolha o modo de consulta:\n\n1. Por time mandante\n2. Por time visitante\n3. Por time mandante ou visitante\n4. Retornar ao menu principal\n\n");
    scanf(" %c", &escolha);

    if (escolha != '4'){

        printf("Digite o nome ou prefixo do time: ");
        scanf("%s", nome_time);

        tamanho_nome = strlen(nome_time);

        for (int i = 0; i < 10; i++){

            strncpy(outro_time, bd_times[i].nome, tamanho_nome);
            //torna o search case insensitive
            lowercase(outro_time, nome_time, tamanho_nome);

            if (strncmp(outro_time, nome_time, tamanho_nome) == 0){
                ids[j] = bd_times[i].ID;
                j++;
            }
        }
        if (j == 0){
            printf("Time não encontrado.\n");
        }else{
        printf("%-5s %-18s %-25s\n",
        "ID",
        "Time 1",
        "Time 2");
            for (i = 0; i < qtd_partidas - 1; i++){
                if (inArray(ids, bd_partidas[i].time1ID, j) && escolha == '1'){
                    printf("%-5d %-12s %d %s %d %-15s\n",
                        bd_partidas[i].ID,
                        bd_times[bd_partidas[i].time1ID].nome,
                        bd_partidas[i].gols1,
                        "X",
                        bd_partidas[i].gols2,
                        bd_times[bd_partidas[i].time2ID].nome
                    );
                    }else if (inArray(ids, bd_partidas[i].time2ID, j) && escolha == '2'){
                        printf("%-5d %-12s %d %s %d %-15s\n",
                        bd_partidas[i].ID,
                        bd_times[bd_partidas[i].time1ID].nome,
                        bd_partidas[i].gols1,
                        "X",
                        bd_partidas[i].gols2,
                        bd_times[bd_partidas[i].time2ID].nome
                    );
                    }else if ((inArray(ids, bd_partidas[i].time1ID, j) || inArray(ids, bd_partidas[i].time2ID, j)) && escolha == '3'){
                        printf("%-5d %-12s %d %s %d %-15s\n", bd_partidas[i].ID,
                            bd_times[bd_partidas[i].time1ID].nome,
                            bd_partidas[i].gols1,
                            "X",
                            bd_partidas[i].gols2,
                            bd_times[bd_partidas[i].time2ID].nome
                        );
                    }
                    
                }
        
    }
        free(nome_time);
        free(outro_time);
        printf("\n");
    }
}

void consultar_time(Times *bd_times){
    char *nome_time = malloc(sizeof(char)*40);
    char *outro_time = malloc(sizeof(char)*40);
    bool cabecalho = false;

    limpa_tela();

    printf("\nDigite o nome ou prefixo do time:\n");
    scanf("%s", nome_time);

    int tamanho_nome = strlen(nome_time);

    for (int i = 0; i < 10; i++){
        strncpy(outro_time, bd_times[i].nome, tamanho_nome);
        //torna o search case insensitive
        lowercase(outro_time, nome_time, tamanho_nome);
        if (strncmp(outro_time, nome_time, tamanho_nome) == 0){
            if (!cabecalho){
                printf("%-4s %-25s %4s %4s %4s %4s %4s %4s %4s\n", "ID", "Time", "V", "E", "D", "GM", "GS", "S", "PG");
                cabecalho = true;
            }

            printf("%-4d %-25s %4d %4d %4d %4d %4d %4d %4d\n",
                bd_times[i].ID,
                bd_times[i].nome,
                bd_times[i].status.wins,
                bd_times[i].status.draw,
                bd_times[i].status.lose,
                bd_times[i].status.w_score,
                bd_times[i].status.l_score,
                bd_times[i].status.saldo,
                bd_times[i].status.pts_ganho);
            
        }
    }

    if (!cabecalho){
        printf("Time não encontrado.");
    }
    free(nome_time);
    free(outro_time);
    printf("\n\n");
}

void mostrar_classificação(Times *bd_times, Partidas *bd_partidas)
{
    limpa_tela();
    
    printf("%-4s %-25s %4s %4s %4s %4s %4s %4s %4s\n", "ID", "Time", "V", "E", "D", "GM", "GS", "S", "PG");
    for (int i = 0; i < 10; i++)
    {   
        printf("%-4d %-25s %4d %4d %4d %4d %4d %4d %4d\n",
            bd_times[i].ID,
            bd_times[i].nome,
            bd_times[i].status.wins,
            bd_times[i].status.draw,
            bd_times[i].status.lose,
            bd_times[i].status.w_score,
            bd_times[i].status.l_score,
            bd_times[i].status.saldo,
            bd_times[i].status.pts_ganho);
    }
    printf("\n\n\n");
}

void exibir_menu(const int qtd_partidas, Times *bd_times, Partidas *bd_partidas)
{
    char escolha;
    while(escolha != 'Q' && escolha != 'q'){
        printf("Bem-vindo ao sistema de gerenciamento de partidas!\n");
        printf("Digite um numero para prosseguir: \n");
        printf("1 - Consultar time\n"
            "2 - Consultar partidas\n"
            "6 - Imprimir tabela de classificacao\n"
            "Q - Sair\n");
        scanf(" %c", &escolha);
    
        switch(escolha){
            case '1': 
                if(qtd_partidas != 1)
                {
                    consultar_time(bd_times);
                    break;    
                }
                else
                {
                    limpa_tela();
                    printf("Infelizmente, os times não constam nenhum score no sistema\n");
                    break;
                }
            case '2':
                if(qtd_partidas != 1)
                {
                    consultar_partidas(qtd_partidas, bd_times, bd_partidas);
                    break;    
                }
                else
                {
                    limpa_tela();
                    printf("Infelizmente, os times não constam nenhum score no sistema\n");
                    break;
                }
                break;
            case '6':
                if(qtd_partidas != 1)
                {
                    mostrar_classificação(bd_times, bd_partidas);
                    break;    
                }
                else
                {
                    limpa_tela();
                    printf("Infelizmente, os times não constam nenhum score no sistema\n");
                    break;
                }
                break;
            case 'Q':
                printf("Você escolheu sair do sistema\n");
                break;
            case 'q':
                printf("Você escolheu sair do sistema\n");
                break;
            default:
                printf("Não existe essa opção\n");
        }
    }
}



