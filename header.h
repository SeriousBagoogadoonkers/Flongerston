#include <stdio.h>
#include <stdlib.h>

#define C_RESET "\x1b[0m"
#define C_RED "\x1b[31m"
#define C_GREEN "\x1b[32m"

struct TCarro { // adicionar modelo e dar um fgets para todos os tipo char
  char nome[32];
  char marca[32];
  float tank_max;
  float tank_atual;
};

void txt(int n);

void flush_in();

void Inicio(float *gas_preco, int *fila_lim); 

void attFila(int *fila_atual, struct TCarro *carro);

void Menu(int *opcao, int tipo);
