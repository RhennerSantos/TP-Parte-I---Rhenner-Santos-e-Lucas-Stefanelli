#include "bd.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void liberar_bd_times(BDTime *bd_times)
{
    if (bd_times == NULL)
        return;
    
    No_T *atual = bd_times->first;
    No_T *proximo;
    
    while (atual != NULL)
    {
        proximo = atual->next;
        free(atual);
        atual = proximo;
    }
    
    free(bd_times);
}

void liberar_bd_partidas(BDPartida *bd_partidas)
{
    if (bd_partidas == NULL)
        return;
    
    No_P *atual = bd_partidas->first;
    No_P *proximo;
    
    while (atual != NULL)
    {
        proximo = atual->next;
        free(atual);
        atual = proximo;
    }
    
    free(bd_partidas);
}

int conta_linhas(char *arq)
{
    FILE *csv = fopen(arq, "r");
    int count = 0;
    char chr = 'a';
    
    //conta as linhas verificando o final \n delas
    while ((chr = getc(csv)) != EOF)
    {
        if (chr == '\n')
        {
            count++;
        }
    }

    fclose(csv); 
    return count -1;
}

// Função de comparação: Retorna 1 se time1 > time2, -1 se time1 < time2, 0 se iguais
int compara_times(Times *t1, Times *t2)
{
    // Pontos ganhos
    if (t1->status.pts_ganho > t2->status.pts_ganho)
        return 1;
    if (t1->status.pts_ganho < t2->status.pts_ganho)
        return -1;
    
    // Saldo de gols
    if (t1->status.saldo > t2->status.saldo)
        return 1;
    if (t1->status.saldo < t2->status.saldo)
        return -1;
    
    // Gols marcados
    if (t1->status.w_score > t2->status.w_score)
        return 1;
    if (t1->status.w_score < t2->status.w_score)
        return -1;
    
    // Vitórias
    if (t1->status.wins > t2->status.wins)
        return 1;
    if (t1->status.wins < t2->status.wins)
        return -1;
    
    // Times empatados em todos os critérios
    return 0;
}

// Função auxiliar para encontrar o último node
No_T* get_ultimo(No_T *head)
{
    while (head != NULL && head->next != NULL)
        head = head->next;
    return head;
}

// Função de partição do Quicksort
No_T* particiona(No_T *head, No_T *end, No_T **newHead, No_T **newEnd)
{
    No_T *pivot = end;
    No_T *prev = NULL, *cur = head, *tail = pivot;
    
    while (cur != pivot)
    {
        if (compara_times(&cur->times, &pivot->times) > 0)
        {
            if (*newHead == NULL)
                *newHead = cur;
            
            prev = cur;
            cur = cur->next;
        }
        else
        {
            if (prev)
                prev->next = cur->next;
            
            No_T *tmp = cur->next;
            cur->next = NULL;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }
    
    if (*newHead == NULL)
        *newHead = pivot;
    
    *newEnd = tail;
    
    return pivot;
}

// Quicksort
No_T* quicksort_recursivo(No_T *head, No_T *end)
{
    if (!head || head == end)
        return head;
    
    No_T *newHead = NULL, *newEnd = NULL;
    
    No_T *pivot = particiona(head, end, &newHead, &newEnd);
    
    if (newHead != pivot)
    {
        No_T *tmp = newHead;
        while (tmp->next != pivot)
            tmp = tmp->next;
        tmp->next = NULL;
        
        newHead = quicksort_recursivo(newHead, tmp);
        
        tmp = get_ultimo(newHead);
        tmp->next = pivot;
    }
    
    pivot->next = quicksort_recursivo(pivot->next, newEnd);
    
    return newHead;
}

// Ordenação
void ordena_times(BDTime *bd_times)
{
    if (bd_times == NULL || bd_times->first == NULL)
        return;
    
    bd_times->first = quicksort_recursivo(bd_times->first, get_ultimo(bd_times->first));
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
