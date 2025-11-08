#ifndef MENU_H
#define MENU_H

#include "bd.h"

//mostra o menu
void exibir_menu(const int qtd_partidas, Times *bd_times, Partidas *bd_partidas);

//consulta os times
void consultar_time(Times *bd_times);

// Consultar partidas (time mandante, time visitante, etc)
void consultar_partidas(const int qtd_partidas, Times *bd_times, Partidas *bd_partidas);

//mostrar classificação
void mostrar_classificação(Times *bd_times, Partidas *bd_partidas);

//limpa a tela
void limpa_tela();

//transforma a string em minúsculo
void lowercase(char *outro_time, char *nome_time, int tamanho_nome);

#endif
