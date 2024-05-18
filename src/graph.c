#include "header.h"

#pragma region criarGrafo (Txt/Csv)

graph* criaGrafo(const char* filename, int nTotalVert){
    int i=0;
    bool *b;
    adj* adj=NULL;
    vertice* v=NULL;
    FILE* file=fopen(filename,"r");
    if(file==NULL)return NULL;
    graph* grafo=(graph*)malloc(sizeof(graph));
    if(grafo==NULL)return NULL;
    grafo->nVert=1;
    grafo->numTv=nTotalVert;
    grafo->inicio=NULL;
    while (!feof(file))
    {
        adj=lerFull(file);
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
    return grafo;
}

adj* lerFull(FILE* file){
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

/* int saveFileToBin(a *ini,char *filename[]){
    a *aux=ini;
    FILE* file=fopen(filename,"wb");
    if (file==NULL)return 1;    
    while (aux!=NULL)
    {
        fwrite(aux,sizeof(a),1,file);
        aux=aux->prox;
    }
    return 0;
} */

#pragma endregion

#pragma region Import (bin)

#pragma endregion