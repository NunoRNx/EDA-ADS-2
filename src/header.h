/**
 * @file header.h
 * @author Nuno Silva (a28005@alunos.ipca.pt)
 * @brief Ficheiro de organização com as bibliotecas, estruturas e declaração de funções utilizadas
 * @version 0.1
 * @date 2024-05-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

/**
 * @brief 
 * Bibliotecas utilizadas
 */

#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

/**
 * @brief 
 * Declaração das estruturas
 */

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
typedef struct stacks {
    int id;
    struct stacks *next;
}stacks;

#pragma funcoes

/**
 * @brief 
 * Declaração de todas as funções
 */

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
bool existeVert(graph* ini, int id);
//int saveGraphToBin(graph *ini,const char *filename);
//int loadBinGraph(graph *ini,const char *filename);

/*DFS com stack estático
int DFS(graph* gini, int oriID, int destID, bool cost);
int DFSrecursive(graph *ini, vertice* vert, int destID, int custo, int stack[], int highPath[], int stackSize, bool high, int* maior, int* sizeHighPath);
void printPath(int stack[], int i);
bool checkStack(int v, int stack[], int stackSize);
*/

int DFS(graph* gini, int oriID, int destID, bool cost);
int DFSrecursive(graph* gini, vertice* vert, int destID, int custo, stacks* stack, stacks** highPath, bool high, int* maior);
bool checkStack(int v, stacks* stack);
void printPath(stacks* stack);
stacks* push(stacks* stack, int id);
stacks* pop(stacks* stack);
stacks* copyPath(stacks* src);
void clearPath(stacks* stack);
