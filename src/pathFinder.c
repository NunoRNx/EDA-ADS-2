/**
 * @file pathFinder.c
 * @author Nuno Silva (a28005@alunos.ipca.pt)
 * @brief Ficheiro com o algoritmo DFT/DFS com opção de calcular o caminho de maior custo
 * @version 0.1
 * @date 2024-05-21
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "header.h"

#pragma region DFS stack Estatico
/* 
int DFS(graph* gini, int oriID, int destID, bool cost){
    int stack[numTv];
    int highPath[numTv];
    int maior=0, sizeHighPath=0;
    if(existeVert(gini,oriID)==false || existeVert(gini,destID)==false)return NULL;
    vertice* vert=gini->inicio;
    while(vert->id!=oriID)vert=vert->proxv;
    if(cost==true){
        DFSrecursive(gini,vert,destID,0,stack,highPath,0,true,&maior,&sizeHighPath);
        printf("\n\nHighest Value Path:");
        printPath(highPath,sizeHighPath);
        return maior;
    }
    DFSrecursive(gini,vert,destID,0,stack,highPath,0,false,&maior,&sizeHighPath);
    return 0;
}

int DFSrecursive(graph* gini, vertice* vert, int destID, int custo, int stack[], int highPath[], int stackSize, bool high, int* maior, int* sizeHighPath){
    int x=0;
    vertice* v=vert;
    
    stack[stackSize]=v->id;
    stackSize++;
    if(v->id==destID){
        //printf("\nteste fim: %d %d\n", v->id,destID);
        if(high==false)printPath(stack,stackSize);
        else if(*maior==0)*maior=custo;
        else if(custo>*maior){
            *maior=custo;
            for(x=0;x<stackSize;x++){
                highPath[x]=stack[x];
            }
            *sizeHighPath=x;
        }
    }else{
        adj* aux=v->ini;
        while(aux!=NULL){
            //printf("\nteste2.5 vert %d size %d\n", vert->id, stackSize);
            //stackprint(stack,stackSize);
            //printf("\nteste3");
            if(checkStack(aux->id,stack,stackSize)==true){
                //printf("\nteste4");
                v=gini->inicio;
                while(v->id!=aux->id)v=v->proxv;
                //printf("\nteste vAtual %d pVert %d\n", vert->id, v->id);
                //printf("\nteste custo %d + adj %d", custo, aux->custo);
                DFSrecursive(gini,v,destID,custo+aux->custo,stack,highPath,stackSize,high,maior,sizeHighPath);
                //printf("\nteste 5: %d %d\n", v->id, custo);
            }
            //printf("\nteste4.5");
            aux=aux->prox; 
        }
    }
    //printf("\nteste2 vert: %d\n",v->ini->id);
    //stackSize--;
    //printf("\ntesteAcabou maior: %d\n", *maior);
    return *maior;
}

bool checkStack(int v, int stack[], int stackSize){
    for (int i = 0; i < stackSize; i++)
    {
        if(v==stack[i])return false;
    }
    return true;
}
//debugg
void stackprint(int stack[], int stackSize){
    for (int i = 0; i < stackSize; i++)
    {
        printf("\nstack:%d", stack[i]);
    }
}
void printPath(int stack[], int i){
    for (int x=0; x < i-1; x++)
    {
        printf("%d->",stack[x]);
    }
    printf("%d\n",stack[i-1]);
}*/
#pragma endregion

#pragma region DFS stack Dinamico

/**
 * @brief Verificação & Preparação para DFT/DFS
 * 
 * @param gini Inicio do grafo
 * @param oriID ID origem
 * @param destID ID destino
 * @param cost booleano que indica se o utilizador o caminho de maior custo e o respetivo custo ou se quer apenas todos os caminhos de ID origem a ID destino
 * @return retorna o custo do caminho de maior custo entre origem e destino
 */

int DFS(graph* gini, int oriID, int destID, bool cost) {
    int maior = 0;
    stacks* stack = NULL;
    stacks* highPath = NULL;
    
    if (!existeVert(gini, oriID) || !existeVert(gini, destID)) {
        return -1;
    }

    vertice* vert = gini->inicio;
    while (vert->id != oriID) {
        vert = vert->proxv;
    }

    if (cost) {
        DFSrecursive(gini, vert, destID, 0, stack, &highPath, true, &maior);
        printPath(highPath);
        clearPath(highPath);
        return maior;
    } else {
        DFSrecursive(gini, vert, destID, 0, stack, &highPath, false, &maior);
        clearPath(stack);
        return 0;
    }
}

/**
 * @brief Algoritmo DFT/DFS
 * 
 * @param gini Inicio do grafo
 * @param vert vértice origem
 * @param destID ID destino
 * @param custo inteiro que guardar o valor de um caminho até ao ponto atual
 * @param stack lista que guarda o caminho
 * @param highPath guarda o caminho de maior custo
 * @param high determina se vai ser calcular o caminho de maior custo ou vão ser mostrados todos os caminhos do ID origem ao ID destino
 * @param maior guarda o valor do caminho de maior custo
 * @return retorna o custo do caminho de maior custo entre origem e destino, se o mesmo não for calculado retorna 0
 */

int DFSrecursive(graph* gini, vertice* vert, int destID, int custo, stacks* stack, stacks** highPath, bool high, int* maior) {
    stack = push(stack, vert->id);
    if (vert->id == destID) {
        if (!high) {
            printPath(stack);
        } else if (custo > *maior || *maior == 0) {
            *maior = custo;
            clearPath(*highPath);
            *highPath = copyPath(stack);
        }
    } else {
        adj* aux = vert->ini;
        while (aux != NULL) {
            if (checkStack(aux->id, stack)) {
                vertice* v = gini->inicio;
                while (v->id != aux->id) {
                    v = v->proxv;
                }
                DFSrecursive(gini, v, destID, custo + aux->custo, stack, highPath, high, maior);
            }
            aux = aux->prox;
        }
    }
    stack = pop(stack);
    return *maior;
}

#pragma endregion