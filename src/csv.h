#ifndef CSV_H
#define CSV_H

#include "produto.h"

/*
 * Lê um catálogo de produtos de um arquivo CSV.
 * Formato esperado (com cabeçalho): id,nome,preco,avaliacao,vendas
 *
 * Retorna um vetor alocado dinamicamente e grava em *n a quantidade lida.
 * Em caso de erro retorna NULL e *n = 0.
 * Quem chama deve liberar o vetor com free().
 */
Produto *ler_csv(const char *caminho, int *n);

#endif /* CSV_H */