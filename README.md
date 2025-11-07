# TP-Parte I Rhenner Santos e Lucas Stefanelli

Este é um sistema produzido para a disciplina de Estruturas de Dados, ministrada pelo docente Thiago Paixão. O objetivo desse programa é organizar os dados de um campeonato de futebol, permitindo que seja possível consultar informações do banco de dados. Para isso, um menu será mostrado no terminal com algumas opções, para que o usuário possa interagir com o sistema.

## Como executar

### 1. Pré-requesitos
- Possuir um compilador em C e uma interface para executar o código.
- Inserir o diretório correto para os arquivos CSV.

### 2. Execução
```
Digite "make" no console
```
  
### 3. Interação com a interface
```
Bem-vindo ao sistema de gerenciamento de partidas!
Digite um numero para prosseguir:
1 - Consultar time.
2 - Consultar partidas.
6 - Imprimir tabela de classificação.
Q - Sair.
```

1. Exibe os nomes dos times que forem pesquisados 
2. Exibe as partidas do time que for pesquisado 
6. Imprime uma tabela com a pontução de todos os times
Q. Termina a execução do sistema.
 
## Estrutura do projeto

### 1. Arquivos
 |Arquivos        | Sobre                                             |        
 |----------      |-------------------------------------------------  |
 |Makefile        |executa e compila os arquivos automaticamente      |
 |main.c          |arquivo principal do programa                      |
 |bd.c + bd.h     |possui o TAD BDTimes, TAD BDPartidas e o TAD Times |
 |menu.c + menu.h |possui o TAD Partidas e outras funções do menu.    |
 |partidas.csv    |conjunto de dados das partidas                     |
 |times.csv       |conjunto de dados do grupo de times                |
 |README.md       |Documentação do sistema                            |
 
### 2. TADs
```C
//TAD BD_partida
typedef struct{
    int ID;
    int time1ID;
    int time2ID;
    int gols1;
    int gols2;
}Partidas;
```
```C
//TAD_time
typedef struct{
    int ID;
    int wins;
    int draw;
    int lose;
    int w_score;
    int l_score;
    int saldo;
    int pts_ganho;
}Status;
```
```C
//TAD BD_Time
typedef struct{
    int ID;
    char nome[400];
    Status status;
}Times;
```

É interessante observar que o struct TAD_Time fica dentro do BD_Times, em vez de ser um terceiro struct separado. Essa decisão foi feita para facilitar o acesso às informações do banco de dados.
 
### 3 Funções do main()
```
conta_linhas(arq_partidas)  : Retorna a quantidade de linhas do arquivo partidas, útil para iterar o csv de partidas.
criar_bdT() :                 Cria espaço e carrega arquivos csv dentro do banco de dados de times.
criar_bdP() :                 Faz o mesmo, só que para o banco de dados de partidas.
calcula_estatistica() :       Calcula as estatitiscas dos times e coloca no TAD_Time.
exibir_menu() :               Exibi o menu e possui as funções de consulta dos dados.
```




 

 
 



