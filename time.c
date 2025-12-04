#include "time.h"

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

//BD_time
typedef struct{
    int ID;
    char nome[400];
    Status status;
}Times;



