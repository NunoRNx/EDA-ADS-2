#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>
#define numTv 10

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
    int nVert;
}graph;

#pragma funcoes

void printGraph(graph *ini);
vertice* addVertice(graph* ini, int id, bool *b);
bool addAdj(graph* ini, int oriID, int destID, int custo);
bool removeAdj(graph* ini, int oriID, int destID);
graph* removeVert(graph* graph, int id, int* e);
graph* criaGrafo(const char* filename);
adj* readAllAdj(FILE* file);
adj* adjMalloc(int custo, int id);
bool delAllAdj(adj* ini);
bool verticeCheck(graph* ini);

int saveGraphToBin(graph *ini,const char *filename);
int loadBinGraph(graph *ini,const char *filename);

int DFS(graph* gini, int oriID, int destID, bool cost);
int DFSrecursive(graph *ini, vertice* vert, int destID, int custo, int stack[], int highPath[], int stackSize, bool high, int* maior, int* sizeHighPath);
void printPath(int stack[], int i);
bool existeVert(graph* ini, int id);
bool checkStack(int v, int stack[], int stackSize);