/**
 * @file graph_func.c
 * @author Nuno Silva (a28005@alunos.ipca.pt)
 * @brief Ficheiro com diversas operações no grafo
 * @version 0.1
 * @date 2024-05-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "header.h"

#pragma region ADD

/**
 * @brief Adicionar vértice ao grafo
 * 
 * @param ini inicio do grafo
 * @param id ID do vértice
 * @param aux novo nó do vértice criado
 * @param ant no caso de já existirem vértices no grafo, este apontador desloca-se para o ultimo vértice e adicionar o novo na casa seguinte
 * @return retorna o novo vértice
 */
vertice* addVertice(graph* ini, int id){
    vertice* aux=NULL;
    vertice* ant=ini->inicio;
    if(existeVert(ini,id)==true)return NULL;
    aux=(vertice*)malloc(sizeof(vertice));
    if (aux==NULL)return NULL;
    aux->proxv=NULL;
    aux->ini=NULL;
    aux->id=id;
    ini->nVert++;
    if (ini->inicio==NULL)return aux;
    while (ant->proxv!=NULL)ant=ant->proxv;
    ant->proxv=aux;
    return aux;
}

/**
 * @brief Adicionar nova adjacência ao grafo
 * 
 * @param ini inicio do grafo
 * @param oriID ID de origem
 * @param destID ID de destino
 * @param custo Custo da adjacência
 * @return true, se o vértice de origem existir
 * @return false, se os dados inseridos são inválidos
 * @note verticeCheck verifica se todos os vértices de todas adjacências existem, caso algum não exista é criado (exemplo: se for adicionada uma adjacência de um vértice que existe no grafo para um que não existe, o vértice com o ID não reconhecido irá ser criado)
 */
bool addAdj(graph* ini, int oriID, int destID, int custo){
    vertice* vert=ini->inicio;
    adj* ant=NULL;
    while(vert!=NULL){
        if(vert->id==oriID)break;
        vert=vert->proxv;
    }if(vert==NULL)return false;
    adj* aux=adjMalloc(custo,destID);
    if(vert->ini==NULL){
        vert->ini=aux;
    }else{
        ant=vert->ini;
        while(ant->prox!=NULL)ant=ant->prox;
        ant->prox=aux;
    }
    verticeCheck(ini);
    return true;
}

adj* adjMalloc(int custo, int id){
    adj* aux=NULL;
    aux=(adj*)malloc(sizeof(adj));
    if (aux==NULL)return NULL;
    aux->id=id;
    aux->custo=custo;
    aux->prox=NULL;
    return aux;
}

#pragma endregion
#pragma region DELETE

/**
 * @brief Remover adjacência
 * 
 * @param ini inicio do grafo
 * @param oriID ID origem
 * @param destID ID destino
 * @return true, se a adjacência indicada for encontrada e apagada
 * @return false, se o vértice ou a adjacência não existirem
 * @note aux/ant/cur servem para caso da adjacência não estar no inicio ou fim e que a ligação da restante lista seja mantida
 */
bool removeAdj(graph* ini, int oriID, int destID){
    vertice* vert=ini->inicio;
    adj* ant=NULL;
    adj* aux=NULL;
    while(vert->id!=oriID){
        vert=vert->proxv;
        if(vert==NULL)break;
    }if(vert==NULL || vert->ini==NULL)return false;
    aux=vert->ini;
    if(aux->id==destID){
        if(aux->prox!=NULL)vert->ini=aux->prox;
        free(aux);
        return true;
    }
    while(aux->id!=destID){
        ant=aux;
        aux=aux->prox;
        if(aux==NULL)break;
    }if(aux==NULL)return false;
    ant->prox=aux->prox;
    free(aux);
    return true;
}

/**
 * @brief Remove todos os dados relacionados ao vértice
 * 
 * @param graph inicio do grafo
 * @param id ID do vértice cujo os dados vão ser removidos
 * @param e e=-1 se o grafo estiver vazio, e=-2 se o vértice indicado não for encontrado, e=0 se funcionou com sucesso
 * @return inicio do grafo
 */
graph* removeVert(graph* graph, int id, int* e){
    vertice* vert=graph->inicio;
    vertice* ant=NULL;
    if (graph == NULL || graph->inicio == NULL){
        *e = -1;
        return graph;
    }
    if(vert->id!=id){
        while (vert->id!=id)
        {
            if(vert==NULL)break;
            ant=vert;
            vert=vert->proxv;
        }
        if (vert==NULL)
        {
            *e=-2;
            return graph;
        }
        ant->proxv=vert->proxv;
    }else graph->inicio=vert->proxv;//se for o primeiro vertice do grafo
    delAllAdj(vert->ini);
    free(vert);
    //foi apagado o unico vertice no grafo
    if(graph->inicio==NULL){
        *e = 0;
        return NULL;
    }
    //remover todas as adj com o ID indicado
    vert=graph->inicio;
    while (vert!=NULL)
    {
        while(removeAdj(graph,vert->id,id));
        vert=vert->proxv;
    }
    *e=0;
    return graph;
}

/**
 * @brief Apagar todas as seguintes adjacências
 * 
 * @param ini adjacência inicial a ser apagada
 * @return true, se todas as adjacêcias forem apagadas
 * @return false, se a adjacência inicial não existir
 */
bool delAllAdj(adj* ini){
    if(ini==NULL)return false;
    adj* aux=ini;
    adj* cur=NULL;
    while (aux!=NULL)
    {
        cur=aux;
        aux=aux->prox;
        free(cur);
    }
   return true; 
}

#pragma endregion
#pragma region Check+Print

/**
 * @brief Verifica existência de vértice de todas as adjacências
 * verifica se todos os vértices de todas adjacências existem, caso algum não exista é criado (exemplo: se for adicionada uma adjacência em um vértice que existe no grafo com destino um vértice que não existe, o vértice com o ID não reconhecido irá ser criado)
 * @param ini inicio do grafo
 * @return true, verificação + criação de vértices com IDs não reconhecidos terminahdo com sucesso
 * @return false, se não existir grafo ou vértices no mesmo
 */
bool verticeCheck(graph* ini){
    if(ini->inicio==NULL || ini==NULL)return false;
    vertice* vert=ini->inicio;
    adj* aux=NULL;
    while (vert!=NULL){
        aux=vert->ini;
        while (aux!=NULL)
        {
            if(!existeVert(ini,aux->id))addVertice(ini,aux->id);
            aux=aux->prox;
        }
        vert=vert->proxv;
    }
    return true;
}

/**
 * @brief Verifica existência de vértice
 * @param ini inicio do grafo
 * @param id ID do vértice a verificar se existe
 * @return true, vértice existe
 * @return false, vértice não existe
 */
bool existeVert(graph* ini, int id){
    if(ini->inicio==NULL || ini==NULL)return false;
    vertice* vert=ini->inicio;
    while(vert!=NULL){
        if(vert->id==id)return true;
        vert=vert->proxv;
    }
    return false;
}

/**
 * @brief Escreve no terminal uma tabela com as informações do grafo
 * 
 * @param ini inicio do grafo
 */
void printGraph(graph *ini){
    vertice* vert=ini->inicio;
    adj* aux=NULL;
    int i;
    while (vert!=NULL)
    {
        i=0;
        aux=vert->ini;
        printf("\n\nOrigem: %d\n", vert->id);
        while (aux!=NULL)
        {
            printf("-> Destino: %d custo: %d\n",aux->id,aux->custo);
            aux=aux->prox;
            i++;
        }
        if(i==0)printf("-> Destino: Nenhum\n");
        vert=vert->proxv;
    }
}

#pragma endregion