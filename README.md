# G22_Ordenacao — Ranking de Produtos com Quick Sort

**Disciplina:** Estruturas de Dados 2 (EDA2) — 2026.2
**Professor:** Maurício Serrano
**Trabalho:** T2 — Ordenação
**Dupla:** Anna Clara Cardoso Evangelista Brandão (222006354) e Esdras de Sousa Nogueira (222006230)
**Repositório:** `github.com/eda2-2026/G22_Ordenacao_EDA2-2026.2`

---

## 1. Problema

Dado um catálogo de produtos em CSV, produzir um **ranking** ordenado por um
critério — **preço**, **avaliação**, **vendas** ou **nome** — em ordem
**crescente** ou **decrescente**.

## 2. Técnica — Quick Sort

Ordenação com **Quick Sort genérico**: a mesma função ordena por qualquer
critério, recebendo a comparação por ponteiro de função

```c
void quicksort(Produto *v, int n, int (*cmp)(const Produto*, const Produto*));
```

Detalhes a documentar ao longo do desenvolvimento: escolha do pivô (mediana de
três), esquema de partição e desempate por `id`.

## 3. Linguagem e build

C (padrão **C11**), compilando **sem warnings** com `gcc -Wall -Wextra -std=c11`.

## 4. Como executar

*(a preencher — Dia 4)*

```
make
./ranking data/produtos.csv preco asc 10
```

## 5. Desempenho (Quick Sort × Bubble Sort × qsort)

*(a preencher — Dia 6; média de 3 execuções)*

| n | Bubble Sort | Quick Sort | qsort (libc) |
| --- | --- | --- | --- |
| 1.000 | | | |
| 10.000 | | | |
| 100.000 | | | |

## 6. Divisão de trabalho

- **Anna (Pessoa B):** quicksort, comparadores, bubble sort, benchmark, testes.
- **Esdras (Pessoa A):** produto, leitura de CSV, gerador, interface (main), Makefile.
