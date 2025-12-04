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

char** busca_time(int id1, int id2, BDTime *bd_times)
{
    char **nome = malloc(2 * sizeof(char*));
    for (No_T *t = bd_times->first; t != NULL; t = t->next){
        if (t->times.ID == id1){
            nome[0] = t->times.nome;
        }
        if (t->times.ID == id2){
            nome[1] = t->times.nome;
        }
    }
    return nome;
}

void consultar_partidas(const int qtd_partidas, BDTime *bd_times, BDPartida *bd_partidas){
    char escolha;
    int i, j = 0, tamanho_nome;
    char *nome_time = malloc(sizeof(char)*40);
    char *outro_time = malloc(sizeof(char)*40);
    char **nome = malloc(2 * sizeof(char*));
    int ids[10];

    limpa_tela();

    printf("Escolha o modo de consulta:\n\n1. Por time mandante\n2. Por time visitante\n3. Por time mandante ou visitante\n4. Retornar ao menu principal\n\n");
    scanf(" %c", &escolha);

    if (escolha != '4'){

        printf("Digite o nome ou prefixo do time: ");
        scanf("%s", nome_time);

        tamanho_nome = strlen(nome_time);

        for (No_T *t = bd_times->first; t != NULL; t = t->next){

            strncpy(outro_time, t->times.nome, tamanho_nome);
            //torna o search case insensitive
            lowercase(outro_time, nome_time, tamanho_nome);
            if (strncmp(outro_time, nome_time, tamanho_nome) == 0){
                ids[j] = t->times.ID;
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
            for (No_P *p = bd_partidas->first; p != NULL; p = p->next){
                if (inArray(ids, p->partidas.time1ID, j) && escolha == '1'){
                    nome = busca_time(p->partidas.time1ID, p->partidas.time2ID, bd_times);
                    printf("%-5d %-12s %d %s %d %-15s\n",
                        p->partidas.ID,
                        nome[0],
                        p->partidas.gols1,
                        "X",
                        p->partidas.gols2,
                        nome[1]
                    );
                    }else if (inArray(ids, p->partidas.time2ID, j) && escolha == '2'){
                        nome = busca_time(p->partidas.time1ID, p->partidas.time2ID, bd_times);
                        printf("%-5d %-12s %d %s %d %-15s\n",
                        p->partidas.ID,
                        nome[0],
                        p->partidas.gols1,
                        "X",
                        p->partidas.gols2,
                        nome[1]
                    );
                    }else if ((inArray(ids, p->partidas.time1ID, j) || inArray(ids, p->partidas.time2ID, j)) && escolha == '3'){
                        nome = busca_time(p->partidas.time1ID, p->partidas.time2ID, bd_times);
                        printf("%-5d %-12s %d %s %d %-15s\n", p->partidas.ID,
                            nome[0],
                            p->partidas.gols1,
                            "X",
                            p->partidas.gols2,
                            nome[1]
                        );
                    }
                    
                }
        
    }
        free(nome_time);
        free(outro_time);
        printf("\n");
    }
}

void consultar_time(BDTime *bd_times){
    char *nome_time = malloc(sizeof(char)*40);
    char *outro_time = malloc(sizeof(char)*40);
    bool cabecalho = false;

    limpa_tela();

    printf("\nDigite o nome ou prefixo do time:\n");
    scanf("%s", nome_time);

    int tamanho_nome = strlen(nome_time);

    for (No_T *t = bd_times->first; t != NULL; t = t->next){
        strncpy(outro_time, t->times.nome, tamanho_nome);
        //torna o search case insensitive
        lowercase(outro_time, nome_time, tamanho_nome);
        if (strncmp(outro_time, nome_time, tamanho_nome) == 0){
            if (!cabecalho){
                printf("%-4s %-25s %4s %4s %4s %4s %4s %4s %4s\n", "ID", "Time", "V", "E", "D", "GM", "GS", "S", "PG");
                cabecalho = true;
            }

            printf("%-4d %-25s %4d %4d %4d %4d %4d %4d %4d\n",
                t->times.ID,
                t->times.nome,
                t->times.status.wins,
                t->times.status.draw,
                t->times.status.lose,
                t->times.status.w_score,
                t->times.status.l_score,
                t->times.status.saldo,
                t->times.status.pts_ganho);
            
        }
    }

    if (!cabecalho){
        printf("Time não encontrado.");
    }
    free(nome_time);
    free(outro_time);
    printf("\n\n");
}

void mostrar_classificação(BDTime *bd_times, BDPartida *bd_partidas)
{
    limpa_tela();
    
    printf("%-4s %-25s %4s %4s %4s %4s %4s %4s %4s\n", "ID", "Time", "V", "E", "D", "GM", "GS", "S", "PG");
    for (No_T *t = bd_times->first; t != NULL; t = t->next)
    {   
        printf("%-4d %-25s %4d %4d %4d %4d %4d %4d %4d\n",
            t->times.ID,
            t->times.nome,
            t->times.status.wins,
            t->times.status.draw,
            t->times.status.lose,
            t->times.status.w_score,
            t->times.status.l_score,
            t->times.status.saldo,
            t->times.status.pts_ganho);
    }
    printf("\n\n\n");
}

void exibir_menu(const int qtd_partidas, BDTime *bd_times, BDPartida *bd_partidas)
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



