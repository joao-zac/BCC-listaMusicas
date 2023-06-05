#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define TAM 50

typedef struct musica MUSICA;
struct musica {
  int id, cantores, estilo;
  char nome[TAM];
};

typedef struct cantor CANTOR;
struct cantor {
  int id, estilo;
  char nome[TAM];
} Cantor;

typedef struct estilo ESTILO;
struct estilo {
  int id;
  char estilo[TAM];
} Estilo;

void create();
void ler();
void modificar();
void excluir();
void interface();
void Menssage(char frase[]);
void MenssageError();
void estilos();
void cantores();

int main() {
  setlocale(LC_ALL,"Portuguese");
  int opcao;

  do {
    interface();
    scanf("%i", &opcao);

    switch (opcao) {
      case 1:
        create();
        break;
      case 2:
        ler();
        break;
      case 3:
        modificar();
        break;
      case 4:
       excluir();
       break;
      case 5: {
        Menssage("Volte Sempre!");
        break;
      }
      default: {
        Menssage("Opcao Invalida...");
        break;
      }
    }
  } while (opcao != 5);

  return 0;
}

void interface() {
  Menssage("Lista de Musicas");
  printf("|     Escolha uma opção:\n|"
         "\n|   1 - Adicionar música"
         "\n|   2 - Ver músicas"
         "\n|   3 - Editar música"
         "\n|   4 - Excluir música"
         "\n|   5 - Sair\n"
         "-----------------------------------------------------\n");
}

void create() {
  int aux = 0;
  
  MUSICA Musica;
  CANTOR Cantor;
  
  FILE *file = fopen("musica.txt", "a");
  
  if (file == NULL) {
    MenssageError();
  } 
  else {
    Menssage("Escreva o nome da música:");
    scanf(" %50[^\n]s", Musica.nome);
    
    Menssage("Digite o ID:");
    scanf("%d", &Musica.id);

    cantores();
    
    Menssage("Digite o ID do cator:");
    scanf("%d", &Musica.cantores);

    estilos();
    
    Menssage("Digite o ID do estilo:");
    scanf("%d", &Musica.estilo);
    Cantor.estilo = Musica.estilo;

    printf("\nMúsica salva!");

    fwrite(&Musica, sizeof(MUSICA), 1, file);
    fclose(file);
    
  }
}

void ler() {

  MUSICA Musica;
  CANTOR Cantor;
  int op;

  FILE *file = fopen("musica.txt", "rb");
  FILE *fileCantor = fopen("cantor.txt", "rb");
  FILE *fileEstilos = fopen("estilo.txt", "rb");
  
  if (file == NULL) {
    MenssageError();
  }

  Menssage("Opções de busca: ");
  printf("-----------------------------------------------------\n"
         "|0 - Mostrar todas as musicas\n"
         "|1 - Buscar pela musica\n"
         "|2 - Buscar pelo estilo\n"
         "|3 - Buscar pelo cantor\n"
         "-----------------------------------------------------\n");

  scanf("%i", &op);

  switch (op) {
    case 0: {

      Menssage("Lista de Musicas");
      printf("\t  ID  | MUSICA | CANTOR \n\n");

      while (fread(&Musica, sizeof(MUSICA), 1, file) != NULL) {
        printf("\t%d - %s - ", Musica.id, Musica.nome);  

        fread(&Cantor, sizeof(CANTOR), 1, fileCantor);
        printf("%s\n", Cantor.nome);

      }

      printf("\n\n");
      break;
    }

    case 1: {
      int id, aux = 0;

      Menssage("Digite o ID da musica: ");
      scanf("%i", &id);
      printf("-----------------------------------------------------\n");
  
      while (fread(&Musica, sizeof(MUSICA), 1, file)) {
        if (Musica.id == id) {
          while (fread(&Cantor, sizeof(CANTOR), 1, fileCantor)){
            if(Cantor.id == Musica.cantores){
              while (fread(&Estilo, sizeof(ESTILO), 1, fileEstilos)){
                if(Estilo.id == Musica.estilo){
                  printf("|\tMusica: %s\tID: %d \n|\n|\tCantor: %s\tID Cantor: %d\n|\n|\tEstilo: %s\tID Estilo: %d",
               Musica.nome, Musica.id, Cantor.nome, Cantor.id, Estilo.estilo, Estilo.id);
                }
              }        
            }
          }      
          aux++;
        }
      }

      if (aux == 0) {
      Menssage("Música não encontrada!");
      }
      break;
    }
    case 2: {
      int idEstilo;

      Menssage("Estilos Existentes");
      printf("\t      ID  | Estilo \n\n");

      while (fread(&Estilo, sizeof(ESTILO), 1, fileEstilos) != NULL) 
        printf("\t%d - %s\n", Estilo.id, Estilo.estilo);

      Menssage("Digite o ID do estilo");
      scanf("%d", &idEstilo);

      printf("\n------------------------------------------------------\n");
      printf("|   Lista de musicas de %s   \n", Estilo.estilo);
      printf("-----------------------------------------------------\n");
      printf("\t  ID  | MUSICA | CANTOR \n\n");
      
      while (fread(&Musica, sizeof(MUSICA), 1, file) != NULL) {
        if(Musica.estilo == idEstilo){
          printf("\t%d - %s - ", Musica.id, Musica.nome);  

          fread(&Cantor, sizeof(CANTOR), 1, fileCantor);
          printf("%s\n", Cantor.nome);
        }
      }
      break;
    }
    case 3: {
      int idCantor;

      Menssage("Cantores Existentes");
      printf("\t      ID  |  Cantor\n\n"); 

      while (fread(&Cantor, sizeof(CANTOR), 1, fileCantor) != NULL) 
        printf("\t%d - %s\n", Cantor.id, Cantor.nome);

      Menssage("Digite o ID do cantor");
      scanf("%d", &idCantor);

      printf("\n------------------------------------------------------\n");
      printf("|   Lista de musicas do %s   \n", Cantor.nome);
      printf("------------------------------------------------------\n");
      printf("\t  ID  | MUSICA | CANTOR \n\n");

      while (fread(&Musica, sizeof(MUSICA), 1, file) != NULL) {
        if(Musica.cantores == idCantor){
          printf("\t%d - %s - ", Musica.id, Musica.nome);  

          fread(&Cantor, sizeof(CANTOR), 1, fileCantor);
          printf("%s\n", Cantor.nome);
        }
      }
      break;
    }
    fclose(file);
    fclose(fileEstilos);
    fclose(fileCantor);
  }
}

void Menssage(char frase[]) {
  printf("\n-----------------------------------------------------\n");
  printf("|   %s   \n", frase);
  printf("-----------------------------------------------------\n");
};

void modificar() {
  FILE *file = fopen("musica.txt", "r");
  FILE *newFile = fopen("Novalista.txt", "a");

  if (file == NULL) {
    MenssageError();
  }

  else {
    int idMusica;
    MUSICA Musica;

    Menssage("Digite o ID da musica que quer alterar:");
    scanf("%d", &idMusica);

    while (fread(&Musica, sizeof(MUSICA), 1, file) != NULL) {
      if (idMusica != Musica.id) {
        fwrite(&Musica, sizeof(MUSICA), 1, newFile);
      }

      else {
        Musica.id = idMusica;

        Menssage("Escreva o nome da música:");
        scanf(" %50[^\n]s", Musica.nome);

        cantores();
        Menssage("Digite o ID do Autor:");
        scanf("%d", &Musica.cantores);

        estilos();      
        Menssage("Digite o ID do estilo:");
        scanf("%d", &Musica.estilo);

        fwrite(&Musica, sizeof(MUSICA), 1, newFile);
      }
    }

    fclose(file);
    fclose(newFile);

    remove("musica.txt");
    rename("Novalista.txt", "musica.txt");
  }
}

void excluir() {

  FILE *file = fopen("musica.txt", "r");
  FILE *NewFile = fopen("Novalista.txt", "a");

  if (file == NULL) {
    MenssageError();
  }

  else {
    int idMusica;
    MUSICA Musica;

    Menssage("Digite o ID da musica que quer excluir: ");
    scanf("%d", &idMusica);

    while (fread(&Musica, sizeof(MUSICA), 1, file) != NULL) {
      if (idMusica != Musica.id) {
        fwrite(&Musica, sizeof(MUSICA), 1, NewFile);
      }
    }

    fclose(file);
    fclose(NewFile);

    remove("musica.txt");
    rename("Novalista.txt", "musica.txt");
  }
}

void MenssageError() {
  printf("Arquivo nao pode ser aberto\n");
  getchar();
  exit(0);
}
void estilos(){
  FILE *fileEstilo = fopen("estilo.txt", "rb");
  int aux;
  if(fileEstilo == NULL)
    MenssageError();
  else{
    Menssage("Estilos Existentes");
    printf("\t      ID  | Estilo \n\n");

    while (fread(&Estilo, sizeof(ESTILO), 1, fileEstilo) != NULL) 
        printf("\t%d - %s\n", Estilo.id, Estilo.estilo);
    fclose(fileEstilo);
  
    Menssage("O Estilo Que Deseja já Existe?\n"
             "\t  Sim = 1 | Não = 2");
    scanf("%i", &aux);
    
    if(aux == 2){
      FILE *fileEstilo = fopen("estilo.txt", "a");
    Menssage("Digite o Nome do Novo Estilo");
    scanf(" %50[^\n]s", Estilo.estilo);

    Menssage("Digite o ID:");
    scanf("%i", &Estilo.id);

    printf("\nEstilo salvo!");
      
    fwrite(&Estilo, sizeof(ESTILO), 1, fileEstilo);
    fclose(fileEstilo);
    }  
  }
}

void cantores(){
  FILE *fileCantores = fopen("cantor.txt", "rb");
  int aux;
  if(fileCantores == NULL)
    MenssageError();
  else{
    Menssage("Cantores Existentes");
    printf("\t      ID  |  Cantor\n\n"); 

    while (fread(&Cantor, sizeof(CANTOR), 1, fileCantores) != NULL) 
        printf("\t%d - %s\n", Cantor.id, Cantor.nome);
    fclose(fileCantores);
  
    Menssage("O Cantor Que Deseja já Existe?\n"
             "\t  Sim = 1 | Não = 2");
    scanf("%i", &aux);
    
    if(aux == 2){
      FILE *fileCantores = fopen("cantor.txt", "a");
    Menssage("Digite o Nome do Novo Cantor");
    scanf(" %50[^\n]s", Cantor.nome);
      
    Menssage("Digite o ID:");
    scanf("%i", &Cantor.id);

    printf("\nCantor salvo!");

    fwrite(&Cantor, sizeof(CANTOR), 1, fileCantores);
    fclose(fileCantores);
    }  
  }
}
