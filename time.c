#ifndef TIME_H
#define TIME_H

typedef struct {
    int ID;
    int wins;
    int lose;
    int draw;
    int w_score;
    int l_score;
    int saldo;
    int pts_ganho;
} Status;

typedef struct {
    int ID;
    char nome[400];
    Status status;
} Times;

#endif