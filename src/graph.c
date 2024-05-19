#include "header.h"

#pragma region criarGrafo (Txt/Csv)

graph* criaGrafo(const char* filename){
    int i=0;
    bool *b;
    adj* adj=NULL;
    vertice* v=NULL;
    FILE* file=fopen(filename,"r");
    if(file==NULL)return NULL;
    graph* grafo=(graph*)malloc(sizeof(graph));
    if(grafo==NULL)return NULL;
    grafo->nVert=1;
    grafo->inicio=NULL;
    while (!feof(file))
    {
        adj=readAllAdj(file);
        if(adj!=NULL){ //erro ao criar adj em ler()
            v=addVertice(grafo,grafo->nVert,&b);
            v->ini=adj;
            if(i==0){
                grafo->inicio=v;
                i++;
            }
        }
    }
    verticeCheck(grafo);
    fclose(file);
    return grafo;
}

adj* readAllAdj(FILE* file){
    int num=0;
    char c;
    int i=1, verf=0;
    adj* aux=NULL;
    adj* ant=NULL;
    adj* ini=NULL;
    while (1)
    {
        num=-1;
        fscanf(file,"%d%c",&num,&c);
        if(num!=-1){
            aux=adjMalloc(num,i);
            if(aux==NULL)return NULL;//erro ao criar adj
            if(i==1)ini=aux;
            else ant->prox=aux; 
            ant=aux;
        }
        if(feof(file) || c=='\n'){
            break;
        }
        i++;
    }
    return ini;
}

#pragma endregion

#pragma region Export (bin)

int saveGraphToBin(graph *ini,const char *filename){
    vertice *aux=ini->inicio;
    FILE* file=fopen(filename,"wb");
    if (file==NULL)return 1;    
    /* while (aux!=NULL)
    {
        fwrite(aux,sizeof(vertice),1,file);
        aux=aux->proxv;
    } */
    fwrite(aux,sizeof(vertice),1,file);
    aux=aux->proxv;
    fwrite(aux->ini,sizeof(adj),1,file);
    aux=aux->proxv;
    fclose(file);
    return 0;
}

#pragma endregion

#pragma region Import (bin)

int loadBinGraph(graph *ini,const char *filename){
    adj* adj=NULL;
    int i=0;
    //criar
    vertice *v=(vertice*)malloc(sizeof(vertice));
    if (v==NULL)return -1; 
    FILE* file=fopen(filename,"rb");
    if (file==NULL)return -2;    
    graph* grafo=(graph*)malloc(sizeof(graph));
    if(grafo==NULL)return -3;
    grafo->nVert=1;
    grafo->inicio=NULL;

    while (!feof(file))
    {
        adj=readAllAdjBin(file);
        if(adj!=NULL){ //erro ao criar adj em ler()
            fread(v,sizeof(vertice),1,file);
            v->ini=adj;
            if(i==0){
                grafo->inicio=v;
                i++;
            }
        }
    }
    fclose(file);
    return 0;
}

#pragma endregion