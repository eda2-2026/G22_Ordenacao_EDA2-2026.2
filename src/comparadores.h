#ifndef COMPARADORES_H
#define COMPARADORES_H

#include "produto.h"

int cmp_preco_asc(const Produto *a, const Produto *b);
int cmp_preco_desc(const Produto *a, const Produto *b);

int cmp_avaliacao_asc(const Produto *a, const Produto *b);
int cmp_avaliacao_desc(const Produto *a, const Produto *b);

int cmp_vendas_asc(const Produto *a, const Produto *b);
int cmp_vendas_desc(const Produto *a, const Produto *b);

int cmp_nome_asc(const Produto *a, const Produto *b);
int cmp_nome_desc(const Produto *a, const Produto *b);

#endif
