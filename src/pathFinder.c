#include "header.h"

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
}