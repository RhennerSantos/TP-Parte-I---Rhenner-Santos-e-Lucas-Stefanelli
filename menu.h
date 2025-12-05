#ifndef MENU_H
#define MENU_H

#include <stdbool.h>
#include "bd.h"

//mostra o menu
void exibir_menu(const int qtd_partidas, BDTime *bd_times, BDPartida *bd_partidas);

//consulta os times
void consultar_time(BDTime *bd_times);

//consulta partidas 
bool consultar_partidas(const int qtd_partidas, BDTime *bd_times, BDPartida *bd_partidas);

//mostrar classificação
void mostrar_classificação(BDTime *bd_times, BDPartida *bd_partidas);

//limpa a tela
void limpa_tela();

//transforma a string em minúsculo
void lowercase(char *outro_time, char *nome_time, int tamanho_nome);

//função para encontrar 2 times pelo id
char** busca_time(int id1, int id2, BDTime *bd_times);

//função para modificar dados de uma partida
void atualizar_partida(const int qtd_partidas, BDTime *bd_times, BDPartida *bd_partidas);

//função para inserir uma nova partida
void inserir_partida(const int qtd_partidas, BDTime *bd_times, BDPartida *bd_partidas);

//função para remover o nó da lista encadeada
void remover_partida(const int qtd_partidas, BDTime *bd_times, BDPartida *bd_partidas);

#endif
