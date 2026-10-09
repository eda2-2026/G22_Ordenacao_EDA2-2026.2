#include "bubblesort.h"
#include "quicksort.h"
#include "comparadores.h"
#include <stdio.h>
#include <stdlib.h>

static int total = 0, passaram = 0;

static void checa(const char *nome, int cond) {
    total++;
    if (cond) { passaram++; printf("  [ok]     %s\n", nome); }
    else      {             printf("  [FALHOU] %s\n", nome); }
}

static int esta_ordenado(const Produto *v, int n, Comparador cmp) {
    for (int i = 1; i < n; i++)
        if (cmp(&v[i - 1], &v[i]) > 0) return 0;
    return 1;
}

static Produto prod(int id, float preco) {
    Produto p;
    p.id = id;
    p.preco = preco;
    p.avaliacao = 0.0f;
    p.vendas = 0;
    p.nome[0] = '\0';
    return p;
}

int main(void) {
    printf("== Testes do Bubble Sort ==\n");

    bubblesort(NULL, 10, cmp_preco_asc);
    checa("ponteiro NULL nao quebra", 1);

    {
        Produto v[1] = { prod(1, 5.0f) };
        bubblesort(v, 1, cmp_preco_asc);
        checa("um elemento", esta_ordenado(v, 1, cmp_preco_asc));
    }

    {
        Produto v[5] = {
            prod(1, 9.0f), prod(2, 1.0f), prod(3, 5.0f),
            prod(4, 1.0f), prod(5, 9.0f)
        };
        bubblesort(v, 5, cmp_preco_asc);
        checa("ordena com repetidos", esta_ordenado(v, 5, cmp_preco_asc));
    }

    {
        int n = 500;
        Produto *v = malloc(n * sizeof(Produto));
        for (int i = 0; i < n; i++) v[i] = prod(i, (float)i);
        bubblesort(v, n, cmp_preco_asc);
        checa("ja ordenado (500)", esta_ordenado(v, n, cmp_preco_asc));
        free(v);
    }

    {
        int n = 2000;
        Produto *a = malloc(n * sizeof(Produto));
        Produto *b = malloc(n * sizeof(Produto));
        srand(7);
        for (int i = 0; i < n; i++) {
            Produto p = prod(i, (float)(rand() % 500));
            a[i] = p;
            b[i] = p;
        }
        bubblesort(a, n, cmp_avaliacao_desc);
        quicksort(b, n, cmp_avaliacao_desc);
        int iguais = 1;
        for (int i = 0; i < n; i++)
            if (a[i].id != b[i].id) { iguais = 0; break; }
        checa("Bubble e Quick produzem a mesma ordem (2000)", iguais);
        checa("resultado ordenado segundo o comparador",
              esta_ordenado(a, n, cmp_avaliacao_desc));
        free(a);
        free(b);
    }

    printf("\n== Resumo: %d/%d passaram ==\n", passaram, total);
    if (passaram == total) {
        printf("RESULTADO: SUCESSO\n");
        return 0;
    }
    printf("RESULTADO: FALHA\n");
    return 1;
}
