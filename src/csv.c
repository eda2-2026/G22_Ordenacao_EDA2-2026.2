#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv.h"

#define TAM_LINHA      256
#define CAPACIDADE_INI 16

/* Remove '\n' e '\r' do fim da linha (arquivos salvos no Windows usam \r\n). */
static void remover_quebra(char *linha) {
    linha[strcspn(linha, "\r\n")] = '\0';
}

Produto *ler_csv(const char *caminho, int *n) {
    *n = 0;

    FILE *arq = fopen(caminho, "r");
    if (arq == NULL) {
        fprintf(stderr, "Erro: nao foi possivel abrir '%s'\n", caminho);
        return NULL;
    }

    int capacidade = CAPACIDADE_INI;
    Produto *v = malloc(capacidade * sizeof(Produto));
    if (v == NULL) {
        fprintf(stderr, "Erro: memoria insuficiente\n");
        fclose(arq);
        return NULL;
    }

    char linha[TAM_LINHA];
    int num_linha = 0;

    /* Ignora a linha de cabeçalho. */
    if (fgets(linha, sizeof linha, arq) == NULL) {
        fclose(arq);
        return v;  /* arquivo vazio: vetor válido com 0 produtos */
    }
    num_linha++;

    while (fgets(linha, sizeof linha, arq) != NULL) {
        num_linha++;
        remover_quebra(linha);
        if (linha[0] == '\0') {
            continue;  /* pula linhas em branco */
        }

        /* Dobra a capacidade quando o vetor enche. */
        if (*n == capacidade) {
            capacidade *= 2;
            Produto *novo = realloc(v, capacidade * sizeof(Produto));
            if (novo == NULL) {
                fprintf(stderr, "Erro: memoria insuficiente\n");
                free(v);
                fclose(arq);
                *n = 0;
                return NULL;
            }
            v = novo;
        }

        Produto p;
        /* %99[^,] lê o nome até a próxima vírgula (máx. 99 caracteres + '\0'). */
        int lidos = sscanf(linha, "%d,%99[^,],%f,%f,%d",
                           &p.id, p.nome, &p.preco, &p.avaliacao, &p.vendas);
        if (lidos != 5) {
            fprintf(stderr, "Aviso: linha %d ignorada (formato invalido)\n", num_linha);
            continue;
        }

        v[*n] = p;
        (*n)++;
    }

    fclose(arq);
    return v;
}