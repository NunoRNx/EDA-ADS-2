#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>

typedef struct adj {
    int id;//char* nome;
    int custo;
    struct adj *prox;
}adj;
typedef struct vertice {
    int id;//char* nome;
    struct vertice *proxv;
    struct adj *ini;
}vertice;
typedef struct graph {
    struct vertice *inicio;
}graph;