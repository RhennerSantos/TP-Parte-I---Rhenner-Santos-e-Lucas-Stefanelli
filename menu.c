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
    if (nome == NULL) return NULL;
    
    nome[0] = NULL;
    nome[1] = NULL;
    
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

void remover_partida(const int qtd_partidas, BDTime *bd_times, BDPartida *bd_partidas)
{
    No_P *p = bd_partidas->first;
    No_P *prev = NULL;
    int ID;
    char conf[40];
    
    if(consultar_partidas(qtd_partidas, bd_times, bd_partidas)) return;
    
    printf("Digite o ID da partida que você deseja remover: ");
    scanf("%d", &ID);
    printf("\n");
    
    printf("\nTem certeza que deseja remover a partida? [S/N] \n");
    scanf("%s", conf);    
    conf[0] = tolower(conf[0]);
    
    if (conf[0] == 's')
    {
        while(p != NULL)
        {
            if (p->partidas.ID == ID)
            {
                if(prev == NULL)
                {
                    bd_partidas->first = p->next;
                }
                else
                {
                    prev->next = p->next;
                }
                free(p);
                printf("Partida removida com sucesso!\n");
                calcula_estatistica(qtd_partidas, bd_times, bd_partidas);
                return;
            }
            prev = p;
            p = p->next;
        }
        printf("Partida com ID %d não encontrada.\n", ID);
    }    
    else if(conf[0] == 'n')
    {
        printf("A remoção foi cancelada\n");
        return;  
    }
}

void inserir_partida(const int qtd_partidas, BDTime *bd_times, BDPartida *bd_partidas)
{
    int time1, time2, placar1, placar2;
    char conf[40];
    
    printf("Para inserir o novo registro digite os seguintes valores.\n");
    printf("ID do time1: ");
    scanf("%d", &time1);
    printf("ID do time2: ");
    scanf("%d", &time2);
    printf("Placar do time1: ");
    scanf("%d", &placar1);
    printf("Placar do time2: ");
    scanf("%d", &placar2);
        
    printf("\nConfirmar inserção de valores [S/N] \n");
    scanf("%s", conf);    
    conf[0] = tolower(conf[0]);
    
    if (conf[0] == 's')
    {
        No_P *p = malloc(sizeof(No_P));
        if (p == NULL) {
            printf("Erro ao alocar memória.\n");
            return;
        }
        
        int max_id = 0;
        for (No_P *temp = bd_partidas->first; temp != NULL; temp = temp->next) {
            if (temp->partidas.ID > max_id) {
                max_id = temp->partidas.ID;
            }
        }
        
        p->partidas.ID = max_id + 1;
        p->partidas.time1ID = time1;
        p->partidas.time2ID = time2;
        p->partidas.gols1 = placar1; 
        p->partidas.gols2 = placar2; 
        
        p->next = bd_partidas->first;                                
        bd_partidas->first = p;
        calcula_estatistica(qtd_partidas + 1, bd_times, bd_partidas);
        printf("Partida inserida com sucesso! ID: %d\n", p->partidas.ID);
        return;
    }
    else if(conf[0] == 'n')
    {
        printf("A inserção dos valores foi cancelada\n");
    }
}

void atualizar_partida(const int qtd_partidas, BDTime *bd_times, BDPartida *bd_partidas)
{
    int id, placar1, placar2;
    char conf[40];
    
    if(consultar_partidas(qtd_partidas, bd_times, bd_partidas)) return;
    
    printf("Digite o ID da partida que você deseja alterar: ");
    scanf("%d", &id);
    printf("\n");
    printf("Digite um novo valor para o placar 1 e placar 2 respectivamente:\n");
    printf("Placar 1: ");
    scanf("%d", &placar1);
    printf("Placar 2: ");
    scanf("%d", &placar2);
    
    for (No_P *p = bd_partidas->first; p != NULL; p = p->next)
    {
        if (p->partidas.ID == id){
            char **nome = busca_time(p->partidas.time1ID, p->partidas.time2ID, bd_times);
            
            if (nome == NULL) {
                printf("Erro ao buscar nomes dos times.\n");
                return;
            }
            
            printf("\n[Novo placar] \n");
            printf("%-5s %-18s %-25s\n", "ID", "Time 1", "Time 2");
            printf("%-5d %-12s %d %s %d %-15s\n",
                p->partidas.ID,
                nome[0] ? nome[0] : "N/A",
                placar1,
                "X",
                placar2,
                nome[1] ? nome[1] : "N/A"
            );
            
            printf("\nConfirmar atualização de valores [S/N] \n");
            scanf("%s", conf);
            conf[0] = tolower(conf[0]);
            
            free(nome);
            
            if (conf[0] == 's'){
                p->partidas.gols1 = placar1;
                p->partidas.gols2 = placar2;
                calcula_estatistica(qtd_partidas, bd_times, bd_partidas);
                printf("Atualização feita com sucesso\n");
                return;
            }
            else if(conf[0] == 'n'){
                printf("Atualização cancelada\n");
                return;
            }
        }
    }
    printf("Partida com ID %d não encontrada.\n", id);
}

bool consultar_partidas(const int qtd_partidas, BDTime *bd_times, BDPartida *bd_partidas){
    char escolha;
    int j = 0, tamanho_nome;
    char nome_time[100];
    char outro_time[100];
    int ids[10];

    limpa_tela();

    printf("Escolha o modo de consulta:\n\n1. Por time mandante\n2. Por time visitante\n3. Por time mandante ou visitante\n4. Retornar ao menu principal\n\n");
    scanf(" %c", &escolha);

    if (escolha != '4'){
        printf("Digite o nome ou prefixo do time: ");
        scanf("%s", nome_time);
        printf("\n");

        tamanho_nome = strlen(nome_time);

        for (No_T *t = bd_times->first; t != NULL; t = t->next){
            strncpy(outro_time, t->times.nome, tamanho_nome);
            outro_time[tamanho_nome] = '\0';
            
            lowercase(outro_time, nome_time, tamanho_nome);
            
            if (strncmp(outro_time, nome_time, tamanho_nome) == 0){
                ids[j] = t->times.ID;
                j++;
                if (j >= 10) break;
            }
        }
        
        if (j == 0){
            printf("Time não encontrado.\n");
            return true;
        }
        
        printf("%-5s %-18s %-25s\n", "ID", "Time 1", "Time 2");
        
        for (No_P *p = bd_partidas->first; p != NULL; p = p->next){
            bool exibir = false;
            
            if (escolha == '1' && inArray(ids, p->partidas.time1ID, j)) {
                exibir = true;
            }
            else if (escolha == '2' && inArray(ids, p->partidas.time2ID, j)) {
                exibir = true;
            }
            else if (escolha == '3' && (inArray(ids, p->partidas.time1ID, j) || inArray(ids, p->partidas.time2ID, j))) {
                exibir = true;
            }
            
            if (exibir) {
                char **nome = busca_time(p->partidas.time1ID, p->partidas.time2ID, bd_times);
                if (nome != NULL) {
                    printf("%-5d %-12s %d %s %d %-15s\n",
                        p->partidas.ID,
                        nome[0] ? nome[0] : "N/A",
                        p->partidas.gols1,
                        "X",
                        p->partidas.gols2,
                        nome[1] ? nome[1] : "N/A"
                    );
                    free(nome);
                }
            }
        }
        
        printf("\n");
        return false;
    }
    return false;
}

void consultar_time(BDTime *bd_times){
    char nome_time[100];
    char outro_time[100];
    bool cabecalho = false;

    limpa_tela();

    printf("\nDigite o nome ou prefixo do time:\n");
    scanf("%s", nome_time);

    int tamanho_nome = strlen(nome_time);

    for (No_T *t = bd_times->first; t != NULL; t = t->next){
        strncpy(outro_time, t->times.nome, tamanho_nome);
        outro_time[tamanho_nome] = '\0';
        
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
    printf("\n\n");
}

void mostrar_classificação(BDTime *bd_times, BDPartida *bd_partidas)
{
    limpa_tela();
    ordena_times(bd_times);
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
    char escolha = '0';
    while(escolha != 'Q' && escolha != 'q'){
        printf("Bem-vindo ao sistema de gerenciamento de partidas!\n");
        printf("Digite um numero para prosseguir: \n");
        printf("1 - Consultar time\n"
            "2 - Consultar partidas\n"
            "3 - Atualizar partida\n"
            "4 - Remover partida\n"
            "5 - Inserir partida\n"
            "6 - Imprimir tabela de classificacão\n"
            "Q - Sair\n");
        scanf(" %c", &escolha);
    
        switch(escolha){
            case '1': 
                consultar_time(bd_times);
                break;
            case '2':
                consultar_partidas(qtd_partidas, bd_times, bd_partidas);
                break;
            case '3':
                atualizar_partida(qtd_partidas, bd_times, bd_partidas);
                break;
            case '4':
                remover_partida(qtd_partidas, bd_times, bd_partidas);
                break;
            case '5':
                inserir_partida(qtd_partidas, bd_times, bd_partidas);
                break;
            case '6':
                mostrar_classificação(bd_times, bd_partidas);
                break;
            case 'Q':
            case 'q':
                printf("Você escolheu sair do sistema\n");
                break;
            default:
                printf("Não existe essa opção\n");
        }
    }
}