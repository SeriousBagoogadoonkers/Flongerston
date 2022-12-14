#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void flush_in() {
  int ch;
  while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
  }
}

void txt(int n) { printf("flabergasted %d\n", n); }

void Inicio(float *gas_preco, int *fila_lim) {
  system("clear");
  printf("Pograma");
  printf("\n\n\n\tAutor: Felipe Zonta Silva\n"
         "Descrição: O programa visa ser um sistema utilizado em um posto de "
         "gasolina, recebendo dados do contexto e os processando para o "
         "funcionamento dos negócios"
         "\n\n%sAtenção!%s ao digitar o preço da gasolina utilize ponto não "
         "virgula.",
         C_RED, C_RESET);
  // preço da gasolina
  printf("\n\n\n\t-Digite o preço da gasolina:");
  scanf("%f", &*gas_preco);
  while (*gas_preco <= 0) { // Verificação
    system("clear");
    printf("%sERRO!%s\no valor da gasolina tem que ser maior que zero\n", C_RED,
           C_RESET);
    printf("\n\n\t-Digite o preço da gasolina:");
    scanf("%f", &*gas_preco);
  }
  // fila
  printf("\t-Digite a quantidade de carros que o estabelecimento suporta:");
  scanf("%d", &*fila_lim);
  while (*fila_lim <= 0) { // verificação
    system("clear");
    printf("%sERRO!%s\na quantidade de carros na fila tem que ser maior que "
           "zero\n",
           C_RED, C_RESET);
    printf(
        "\n\n\t-Digite a quantidade de carros que o estabelecimento suporta:");
    scanf("%d", &*fila_lim);
  }
  system("clear");
  //______________________________________________________________________________________________________________________________________________________________________
}

void attFila(int *fila_atual, struct TCarro *carro) {
  for (int i = 0; i < *fila_atual; i++) {
    carro[i] = carro[i + 1];
  }
}

void Menu(int *opcao, int tipo) {
  switch (tipo) {

  case 0: // menu principal
    printf("\n\n\t[MENU]\n\n\t(1)_adicionar um carro na "
           "fila\n\t(2)_abastecimento\n\t(3)_fila de espera"
           "\n\t(4)_relatório\n\t(5)_estatisticas "
           "gerais\n\t(6)_encerrar\n\n\n");
    break;

  case 1: // menu dos relatórios
    printf("\n\n\t[Relatórios]\n\n"
           "\t(1)_gasolina vendida \n\t(2)_valor "
           "arrecadado com as vendas \n\t(3)_carros "
           "atendidos\n\t(4)_gasolina no tanque "
           "\n\t(5)_relatório para impressão \n\t(6)_menu anterior\n\n\n");
    break;

  case 2: // opções de abastecimento
    printf("\n\n\t[Abastecer]\n\n"
           "\t(1)_quantidade específica \n\t(2)_"
           "encher tanque \n\t");
    break;
  }
  scanf("%d", &*opcao);
  system("clear");
}
