#include "header.h"

/* bool DFS(graph* ini, int oriID, int destID){


    int stack[numTv];
    int high[numTv];
    int cust[numTv];
    int i=0, paths=0;
    vertice* vert=ini->inicio;
    vertice* vaux=NULL;
    adj* aux=NULL;
    aux=vert->ini;
    //verificar se existe Origem e Destino
    if(existeVert(ini,oriID)==false || existeVert(ini,destID)==false)return false;
    //vertice origem
    while(vert->id!=oriID)vert=vert->proxv;
    vert->visited=true;
    stack[i]=vert->id;
    cust[i]=0;
    i++;
    aux=vert->ini;

    while(i!=1 && paths==0){
        while(aux!=NULL){
            vaux=ini->inicio;
            while (vaux->id!=aux->id)
            {
                vaux=vaux->proxv;
            }
            if(vaux->visited==false){
                stack[i]=vaux->id;
                cust[i]=aux->custo;
                i++;
                vaux->visited=true;
                aux=vaux->ini;
            }else{
                aux=aux->prox;
            }
            if(vaux->id==destID)break;
        }
        if(vert->id==destID){
            printPath(stack, i);
            paths++;
            vert->visited=false;
        }
        i--;
        vaux=ini->inicio;
        while(vaux->id!=stack[i])vaux=vaux->proxv;
        aux=vaux->ini;
    }
    resetVisited(ini);
    return true;
} */

bool resetVisited(graph* ini){
    if(ini==NULL)return false;
    vertice* aux=ini->inicio;
    while(aux!=NULL){
        aux->visited=false;
        aux=aux->proxv;
    }
    return true;
}

void printPath(int stack[], int i){
    for (int x=0; x < i-1; x++)
    {
        printf("%d->",stack[x]);
    }
    printf("%d\n",stack[i-1]);
}

bool existeVert(graph* ini, int id){
    vertice* vert=ini->inicio;
    while(vert->id!=id || vert!=NULL){
        vert=vert->proxv;
    }
    if(vert==NULL)return false;
    return true;
}

int DFS(graph* gini, vertice* vert, int destID, int custo, int stack[], int highPath[], int stackSize, bool high, int* maior, int* sizeHighPath){
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
                printf("\nteste custo %d + adj %d", custo, aux->custo);
                DFS(gini,v,destID,custo+aux->custo,stack,highPath,stackSize,high,maior,sizeHighPath);
                //printf("\nteste 5: %d %d\n", v->id, custo);
            }
            //printf("\nteste4.5");
            aux=aux->prox; 
        }
    }
    //printf("\nteste2 vert: %d\n",v->ini->id);
    //stackSize--;
    //printf("\ntesteAcabou maior: %d\n", *maior);
    return 0;
}

bool checkStack(int v, int stack[], int stackSize){
    for (int i = 0; i < stackSize; i++)
    {
        if(v==stack[i])return false;
    }
    return true;
}

void stackprint(int stack[], int stackSize){
    for (int i = 0; i < stackSize; i++)
    {
        printf("\nstack:%d", stack[i]);
    }
    
}