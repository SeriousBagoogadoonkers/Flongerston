#include "header.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {

  int fila_lim = 0, fila_atual = 0, carro_atendido = 0;
  int opcao = 0, tipo = 0;
  float gas_preco = 0, gas_vendido = 0, gas_abastecer, gas_tank = 200, banco;
  FILE *fp = fopen("registro.txt", "w");
  struct TCarro *carro;
  struct TCarro *atendido;

  Inicio(&gas_preco, &fila_lim);

  atendido = (struct TCarro *)malloc(1 * sizeof(struct TCarro));
  carro = (struct TCarro *)malloc(fila_lim * sizeof(struct TCarro));
  if (carro == NULL) {
    printf("memória insuficiente");
  }

  Menu(&opcao, tipo);
  while (opcao != 6) {
    banco = gas_vendido * gas_preco; // atualiza o banco a cada loop
    switch (opcao) {
    default:
      printf("%sERRO!%sopção inválida digite novamente", C_RED, C_RESET);
      break;

    case 1: // adicionar carro
    {
      if (fila_atual == fila_lim) {
        printf("%sERRO!%s a fila atingiu seu limite máximo", C_RED, C_RESET);
      } else {
        flush_in();

        printf("digite o nome do carro:");
        fgets(carro[fila_atual].nome, 31, stdin);
        carro[fila_atual].nome[strcspn(carro[fila_atual].nome, "\n")] = 0;

        printf("digite a marca do carro:");
        fgets(carro[fila_atual].marca, 31, stdin);
        carro[fila_atual].marca[strcspn(carro[fila_atual].marca, "\n")] = 0;

        printf("capacidade do tanque do carro:");
        scanf("%f", &carro[fila_atual].tank_max);

        printf("quantidade atual de combustível:");
        scanf("%f", &carro[fila_atual].tank_atual);

        system("clear");

        while (carro[fila_atual].tank_atual >=
               carro[fila_atual]
                   .tank_max) { // verifica se o carro pode ser abastecido
          printf("%sERRO!%s o carro não pode ser atendido, por favor "
                 "verifique os dados digitados.\n\n",
                 C_RED, C_RESET);

          printf("capacidade do tanque do carro:");
          scanf("%f", &carro[fila_atual].tank_max);

          printf("quantidade atual de combustível:");
          scanf("%f", &carro[fila_atual].tank_atual);
          system("clear");
        }
        fila_atual = fila_atual + 1;
        printf("%scarro adicionado%s [fila atual:%d]", C_GREEN, C_RESET,
               fila_atual);
      }
      break;
    }

    case 2: // abastecer carro
    {
      if (fila_atual > 0 || gas_tank <= 0) { // verifica se afila existe

        tipo = 2; // muda tipo do menu
        Menu(&opcao,tipo);
      
        switch (opcao) {
    
        case 1: {
          printf("o cliente pode abastecer %s%.2fL%s de gasolina", C_GREEN,
                 carro[0].tank_max - carro[0].tank_atual, C_RESET);

          printf("\nDigite a quantidade de gasolina a ser abastecida:");
          scanf("%f", &gas_abastecer);

          while (gas_abastecer > carro[0].tank_max - carro[0].tank_atual ||
                 gas_abastecer <= 0 || gas_abastecer > gas_tank) {
            if (gas_abastecer > carro[0].tank_max - carro[0].tank_atual) {
              printf("%sERRO!%s a quantidade que você deseja abastecer excede o "
                     "tanque do carro\n",
                     C_RED, C_RESET);
            } else if (gas_abastecer <= 0) {
              printf("%sERRO!%s o valor de abastecimento tem que ser positivo\n",
                     C_RED, C_RESET);
            } else if (gas_abastecer > gas_tank) {
              printf("%sERRO!%s a quantidade de gasolina excede o disponível no "
                     "tanque do posto\n",
                     C_RED, C_RESET);
            }
            printf("\n por favor "
                   "redigite:");
            scanf("%f", &gas_abastecer);
          }

          break;
        } // abastecimento especifico

        case 2: {
          if (carro[0].tank_max - carro[0].tank_atual > gas_tank) {
            gas_abastecer = gas_tank;
          } else {
            gas_abastecer = carro[0].tank_max - carro[0].tank_atual;
          }
          break;
        } // abastecimento total
        }

        gas_vendido = gas_vendido + gas_abastecer;
        gas_tank = gas_tank - gas_abastecer;
        fila_atual = fila_atual - 1;
        atendido[carro_atendido] = carro[0];
        carro_atendido = carro_atendido + 1;

        atendido = (struct TCarro *)realloc(
            atendido, (carro_atendido + 1) * sizeof(struct TCarro));

        attFila(&fila_atual, carro);

        printf("%sCarro atendido%s\ngasolina restante no tanque:%.2f", C_GREEN,
               C_RESET, gas_tank);
        
      } else { // ERROS
        if(fila_atual > 0){
        printf("%sERRO!%s a fila está vazia", C_RED, C_RESET);
      }else{
          printf("%sERRO!%s o tanque está vazio", C_RED, C_RESET);
      }
        }
      tipo = 0;
      break;
    }

    case 3: // carros na fila
    {
      printf("carros na fila:%s%d%s\n", C_GREEN, fila_atual, C_RESET);
      for (int i = 0; i < fila_atual; i++) {
        printf("\n[carro nº%d]\n", i + 1);
        printf("nome:%s\n", carro[i].nome);
        printf("marca:%s\n", carro[i].marca);
        printf("gasolina atual:%.2f de %.2f \n\n", carro[i].tank_atual,
               carro[i].tank_max);
      }
      break;
    }

    case 4: // relatório
    {
      tipo = 1;
      Menu(&opcao, tipo);

      while (opcao != 6) {

        switch (opcao) {
        case 1:
          printf("quantidade de litros vendida:%s%.2f%s", C_GREEN, gas_vendido,
                 C_RESET);
          break;
        case 2:

          printf("valor total arrecadado com as vendas:%s%.2f%s", C_GREEN,
                 banco, C_RESET);
          break;
        case 3:
          printf("\ncarros atendidos:%s%d%s\n\n", C_GREEN, carro_atendido,
                 C_RESET);
          for (int i = 0; i < carro_atendido; i++) {
            printf("[nº%d carro atendido]\n", i + 1);
            printf("nome:%s\n", atendido[i].nome);
            printf("marca:%s\n\n", atendido[i].marca);
          }
          break;
        case 4:
          printf("quantidade de combustivel restante no tanque:%s%.2f%s",
                 C_GREEN, gas_tank, C_RESET);
          break;
        case 5: // gerar arquivos para impressão

          fprintf(fp,
                  "Quantidade de gasolina vendida: %.2f litros\nQuantidade de "
                  "carros tendidos: %d carro(s)\nValor total arrecadado com as "
                  "vendas: R$ %.2f\n",
                  gas_vendido, carro_atendido, banco);
          fclose(fp);

          printf("quantidade de litros vendida:%s%.2f%s\ncarros atendidos: "
                 "%s%d%svalor arecadado das "
                 "vendas:%s%.2f%s",
                 C_GREEN, gas_vendido, C_RESET, C_GREEN, carro_atendido,
                 C_RESET, C_GREEN, banco, C_RESET);
          break;
        case 6:

          break;
        }
        Menu(&opcao, tipo);
      }
      tipo = 0;
      break;
    }

    case 5: // estatisticas gerais
    {
      printf("fila atual:%s%d%s\t\tatendidos:%s%d%s\nbanco:%sR$%.2f%s\t\tpreço "
             "da gasolina:%sR$%.2f%s\n\ngasolina disponível:%s%.2f "
             "L%s\ngasolina vendida:\t%s%.2f L%s",
             C_GREEN, fila_atual, C_RESET, C_GREEN, carro_atendido, C_RESET,
             C_GREEN, banco, C_RESET, C_GREEN, gas_preco, C_RESET, C_GREEN,
             gas_tank, C_RESET, C_GREEN, gas_vendido, C_RESET);
      break;
    }
    }
    Menu(&opcao, tipo);
  }

  printf("\n\n\t\t%sFin.\n\n\n\n\n", C_RED);

  return 0;
}
