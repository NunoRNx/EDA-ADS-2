#include "header.h"
//passeio

int main(){
    const char* filename="nums.txt";
    bool *r;
    graph* ini=criaGrafo(filename,10);
    printf("\nAdd vertice to graph\n");
    addVertice(ini,ini->nVert,&r);
    printf("\nAdd destination to a vertice\n"); 
    addAdj(ini,3,40,23);
    addAdj(ini,40,6,47);
    printGraph(ini);
    /*
    *r==0 erro ao abrir ficheiro
    *r==-1 vertice erro
    *r==-2 adj erro
    */
    return 0;
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
    printf("\nFim de grafo\n");
}

vertice* addVertice(graph* ini, int id, bool *b){
    vertice* aux=NULL;
    vertice* ant=ini->inicio;
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
    adj* aux=(adj*)malloc(sizeof(adj));
    if (aux==NULL)return false;
    aux->prox=NULL;
    aux->custo=custo;
    aux->id=destID;
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


#pragma criarGrafo

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

adj* adjMalloc(int num, int id){
    adj* aux=NULL;
    aux=(adj*)malloc(sizeof(adj));
    if (aux==NULL)return NULL;
    aux->id=id;
    aux->custo=num;
    aux->prox=NULL;
    return aux;
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