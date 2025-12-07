# TP-Parte II Rhenner Santos e Lucas Stefanelli

Este é um sistema produzido para a disciplina de Estruturas de Dados, ministrada pelo docente Thiago Meireles Paixão. O objetivo desse programa é organizar os dados de um campeonato de futebol, permitindo que seja possível consultar essas informações. Para isso, um menu será mostrado no terminal com algumas opções, para que o usuário possa interagir com o sistema.

## Como executar

### 1. Pré-requesitos
- Possuir um compilador em C e uma interface para executar o código.
- Inserir o diretório correto para os arquivos CSV.

### 2. Execução
```
Digite "make" no console.
```
  
### 3. Interação com a interface
```
Bem-vindo ao sistema de gerenciamento de partidas!
Digite um numero para prosseguir:
1 - Consultar time.
2 - Consultar partidas.
3 - Atualizar partida.
4 - Remover partida.
5 - Inserir partida.
6 - Imprimir tabela de classificação.
Q - Sair.
```

- 1 Exibe a pontuação do time que for pesquisado. 
- 2 Mostra as partidas do time que foi digitado.
- 3 Permite que o score de uma partida seja alterado.
- 4 Permite a exclusão de um partida.
- 5 Insere uma partida nova.
- 6 Imprime uma tabela com a pontução de todos os times.
- Q Termina a execução do sistema.
 
## Estrutura do projeto

### 1. Arquivos
 |Arquivos            | Sobre                                             |        
 |----------          |-------------------------------------------------  |
 |Makefile            |executa e compila os arquivos automaticamente      |
 |main.c              |arquivo principal do programa                      |
 |bd.c + bd.h         |possui as listas encadeadas do BD times/partidas   |
 |                    |e funções de organização do banco de dados         |
 |time.c + partidas.c |tem o struct do BDTimes e BDpartidas               |                                                   
 |menu.c + menu.h     |possui todas as funções do menu                    |
 |partidas.csv        |conjunto de dados das partidas                     |
 |times.csv           |conjunto de dados do grupo de times                |
 |README.md           |documentação do sistema                            |
 
### 2. Banco de dados

Tanto o BDTimes quando o BDPartidas estão representados como listas encadeadas. Para isso, foram utilizados 2 structs da seguinte maneira:

```
typedef struct No{
    Times/Partidas; // liga o nó ao struct que tem os dados do csv
    struct No *next; // ponteiro que aponta para o próximo nó
}No;

typedef struct{
    No *first; // ponteiro que aponta para o primeiro no
}BD;
```

É importante Salientar que o BDTimes é simplesmente encadeado, por conta da iteração da lista ser simples. Já o BDPartidas utiliza um ponteiro *prev em alguns casos, já que ele utiliza funções mais complexas como a de ordenação.

```C
typedef struct{
    int ID;
    int time1ID;
    int time2ID;
    int gols1;
    int gols2;
}Partidas;
```
```C
typedef struct{
    int ID;
    char nome[400];
    Status status;
}Times;
```
```C
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


Há 3 structs, mas o apenas dois banco de dados. É interessante observar que o struct Status faz parte do struct Times, mas estes estão separados para facilitar a organização dos dados.
 
### 3 Funções do main()

```
conta_linhas() :              Retorna a quantidade de linhas do arquivo partidas.
criar_bdT() :                 Cria espaço estaticamente e carrega arquivos CSV dentro do banco de dados de times.
criar_bdP() :                 Faz o mesmo, só que para o banco de dados de partidas.
calcula_estatistica() :       Calcula as estatítiscas dos times e coloca no TAD_Time.
exibir_menu() :               Exibi o menu e entrega as funções para a consulta dos dados.
liberar_bd_times():           Dá free nos nodes e no ponteiro para o BD_Times.
liberar_bd_partidas():        Dá free nos nodes e no ponteiro para o BD_Partidas.
```

##  Decisões de implementação

- bool consultar_partidas(): a função de consulta retonar um valor verdadeiro e falso, útil para caso o nome seja pesquisado errado e a interface não possa prosseguir para remoção ou atualização de dados.
- Conta_linhas(): Função para contar as quantidade variável de linhas do partidas.csv. Útil para quando for necessário iterar o BD_Partidas.
- Calcula_estatistica(): Essa função é utilizado antes do menu iniciar, mas também é chamada quando os dados são alterados.
- lowercase(): Essa é uma função que torna possível fazer uma pesquisa case insensitive.
- inArray(): Checa se os IDs escolhidos são os do time desejado, utlizado no consultar_partidas.
- quicksort_recursivo(): Para ordenar os times, foi utilizado um quicksort e alguns outras funções auxiliares como a get_ultimo() que pega o último nó da lista.
- strncmp(): Faz o search tanto pelo nome completo quanto pelo prefixo;





 

 
 



