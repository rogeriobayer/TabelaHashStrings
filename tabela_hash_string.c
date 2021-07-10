#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define TAMANHO_TABELA 19

struct Item {
  char * data;
};

struct Item * tabelaHash[TAMANHO_TABELA];
struct Item * extraItem;
struct Item * item;

int string_hash(char * s) {
  char c;
  int p = 31;
  int hash_value = 0, p_pow = 1;

  while (c = * s++) {
    hash_value = (hash_value + (c - 'a' + 1) * p_pow) % TAMANHO_TABELA;
    p_pow = (p_pow * p) % TAMANHO_TABELA;
  }
  return (hash_value);
}

struct Item * busca(char * data) {
  int index = string_hash(data);
  while (tabelaHash[index] != NULL) {

    if (strcmp(tabelaHash[index] -> data, data) == 0)
      return tabelaHash[index];
    ++index;
    index %= TAMANHO_TABELA;
  }
  return NULL;
}

void inserir(char * data) {
  struct Item * item = (struct Item * ) malloc(sizeof(struct Item));
  item -> data = data;
  int index = string_hash(data);
  while (tabelaHash[index] != NULL) {
    ++index;
    index %= TAMANHO_TABELA;
  }
  tabelaHash[index] = item;
}

struct Item * excluir(struct Item * item) {
  int index = string_hash(item -> data);

  while (tabelaHash[index] != NULL) {

    if (strcmp(tabelaHash[index] -> data, item -> data) == 0) {
      struct Item * temp = tabelaHash[index];

      tabelaHash[index] = extraItem;
      return temp;
    }

    ++index;

    index %= TAMANHO_TABELA;
  }

  return NULL;
}

void exibir() {
  int i = 0;

  for (i = 0; i < TAMANHO_TABELA; i++) {

    if (tabelaHash[i] != NULL)
      printf("(%s) \n", tabelaHash[i] -> data);
    else
      printf(" ~~ \n");
  }

  printf("\n");
}

int main() {
  extraItem = (struct Item * ) malloc(sizeof(struct Item));
  extraItem -> data = -1;

  inserir("Mariah");
  inserir("Carrey");
  inserir("Tidal");
  inserir("Michael");
  inserir("Joanne");
  inserir("Pauli");
  inserir("Luan");
  inserir("Tico");

  exibir();
  item = busca("Mariah");

  item != NULL ?
    printf("Encontrado: %s\n", item -> data) :
    printf("Nao Encontrado\n");

  excluir(item);
  item = busca("");

  item != NULL ?
    printf("Encontrado: %s\n", item -> data) :
    printf("Nao Encontrado\n");
}
