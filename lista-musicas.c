/*            Lista de músicas

Criar um sistema para criar, visualizar,
editar e excluir músicas de uma lista

*/
#include <stdio.h>
#include <stdlib.h>
#define TAM 20

void interface() {
  printf("\n\tLista de músicas\n"
         "\nEscolha uma opção:\n"
         "\n1 - Adicionar música"
         "\n2 - Ver músicas"
         "\n3 - Editar música"
         "\n4 - Excluir música"
         "\n5 - Sair\n");
}

void create() {

  char nome[TAM];
  FILE *Arquivo = fopen("lista.txt", "a");

  if (Arquivo == NULL) {
    printf("Arquivo não encontrado\n");
  }

  else {
    printf("Escreva o nome da música: ");
    scanf("%s", nome);
    fwrite(nome, 1, strlen(nome), Arquivo);
    fputc('\n', Arquivo);
  }

  fclose(Arquivo);
}

int main() {
  int opcao;

  do {
    interface();
    scanf("%i", &opcao);

    switch (opcao) {
      case 1:
        create();
        break;
      case 2:
        break;
      case 3:
        break;
      case 4:
        break;
      case 5: {
        printf("Fim do programa!\n");
        break;
      }
      default: {
        printf("\7Caractere inválido! tente novamente\n");
      }
    }
  } while (opcao != 5);

  return 0;
}