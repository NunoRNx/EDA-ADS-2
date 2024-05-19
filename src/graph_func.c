#include "header.h"

#pragma region ADD

vertice* addVertice(graph* ini, int id, bool *b){
    vertice* aux=NULL;
    vertice* ant=ini->inicio;
    if(existeVert(ini,id)==true)return NULL;
    aux=(vertice*)malloc(sizeof(vertice));
    if (aux==NULL){
        *b=false;
        return NULL;
    }
    aux->proxv=NULL;
    aux->ini=NULL;
    aux->id=id;
    ini->nVert++;
    if(ini==NULL){
        ini->inicio=aux;
        *b=true;
        return aux;
    }
    if (ini->inicio==NULL)
    {
        ini->inicio=aux;
        *b=true;
        return aux;
    }
    while (ant->proxv!=NULL)ant=ant->proxv;
    if(ant!=NULL)ant->proxv=aux;
    *b=true;
    return aux;
}

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

bool removeAdj(graph* ini, int oriID, int destID){
    vertice* vert=ini->inicio;
    adj* ant=NULL;
    adj* aux=NULL;
    adj* cur=NULL;
    while(vert->id!=oriID || vert!=NULL){
        vert=vert->proxv;
    }if(vert==NULL)return false;
    if(vert->ini!=NULL)aux=vert->ini;
    else return false;
    while(aux->prox->id!=destID || aux!=NULL){
        aux=aux->prox;
    }if(aux==NULL)return false;
    ant=aux;
    cur=aux;
    aux=aux->prox;
    ant->prox=aux;
    free(cur);
    return true;
}

graph* removeVert(graph* graph, int id, int* e){
    vertice* vert=graph->inicio;
    vertice* ant=NULL;
    if (graph == NULL || graph->inicio == NULL){
        *e = -1;
        return NULL;
    }
    if(graph->inicio->id!=id){
        while (vert!=NULL && vert->proxv->id!=id)
        {
            vert=vert->proxv;
        }
        if (vert==NULL)
        {
            *e=-2;
            return graph;
        }
        ant=vert;
        vert=vert->proxv;
    }
    delAllAdj(vert->ini);
    //se for o primeiro vertice do grafo
    if(graph->inicio->id==id)graph->inicio=vert->proxv;
    else if(ant!=NULL)ant->proxv=vert->proxv;
    free(vert);
    //foi apagado o unico vertice no grafo
    if(graph->inicio==NULL){
        *e = -1;
        return NULL;
    }
    //remover todas as adj com o ID indicado
    vert=graph->inicio;
    adj* prev=NULL;
    adj* aux=NULL;
    adj* atual=NULL;
    while (vert!=NULL)
    {
        aux=vert->ini;
        while (aux->prox!=NULL)
        {
            if(vert->ini->id==id){
                vert->ini=aux->prox;
                atual=aux;
                aux=vert->ini;
                free(atual);
            }
            if(aux->prox->id==id){
                prev=aux;
                aux=aux->prox;
                atual=aux;
                aux=aux->prox;
                prev->prox=aux;
                free(atual);
            }
        }
        vert=vert->proxv;
    }
    *e=0;
    return graph;
}

bool delAllAdj(adj* ini){
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

bool verticeCheck(graph* ini){
    vertice* vert=ini->inicio;
    vertice* vaux=NULL;
    adj* aux=NULL;
    bool found=false;
    bool *b;
    while (vert!=NULL){
        aux=vert->ini;
        while (aux!=NULL)
        {
            vaux=ini->inicio;
            while (vaux!=NULL)
            {
                if(vaux->id==aux->id){
                    found=true;
                    break;
                }
                vaux=vaux->proxv;
            }
            if(!found)addVertice(ini,aux->id,&b);
            aux=aux->prox;
            found=false;
        }
        vert=vert->proxv;
    }
    return true;
}

bool existeVert(graph* ini, int id){
    vertice* vert=ini->inicio;
    while(vert->id!=id && vert!=NULL){
        vert=vert->proxv;
    }
    if(vert==NULL)return false;
    return true;
}

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