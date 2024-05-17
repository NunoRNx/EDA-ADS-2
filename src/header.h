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
    int id;
    int numTv;//numTotalVertices
}graph;

#pragma funcoes

void printGraph(graph *ini);
vertice* addVertice(graph* ini, bool *b);
bool addAdj(graph* inicio, int oriID, int destID, int custo);
bool removeAdj(graph* inicio, int oriID, int destID);
graph* removeVert(graph* graph, int id, int* e);
graph* criaGrafo(const char* filename, int nTotalVert);
adj* lerFull(FILE* file);
adj* adjMalloc(int num, int id);
bool delAllAdj(adj* ini);
bool verticeCheck(graph* ini);