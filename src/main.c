#include "header.h"
//passeio

int main(){
    char filename[8]="nums.txt";
    bool *r;
    graph* ini=criaGrafo(filename,10);
    printf("\nAdd vertice to graph\n");
    addVertice(ini,&r);
    printf("\nAdd destination to a vertice\n");
    addAdj(ini,3,40,&r);
    /*
    *r==0 erro ao abrir ficheiro
    *r==-1 vertice erro
    *r==-2 adj erro
    */
    return 0;
}

void printGraph(graph *ini){
    vertice* vert=ini;
    adj* aux=NULL;
    while (vert!=NULL)
    {
        aux=vert->ini;
        printf("De %d \npara:\t",vert->id);
        while (aux!=NULL)
        {
            printf("id:%d custo:%d",aux->id,aux->custo);
            aux=aux->prox;
        }
        vert=vert->proxv;
    }
}

vertice* addVertice(graph* ini, bool *b){
    vertice* aux=NULL;
    vertice* ant=ini;
    printf("\nteste1\n");
    aux=(vertice*)malloc(sizeof(vertice));
    if (aux==NULL){
        *b=false;
        return NULL;
    }
    printf("\nteste2\n");
    aux->proxv=NULL;
    printf("\nteste3\n");
    aux->ini=NULL;
    printf("\nteste4\n");
    aux->id=ini->id;
    printf("\nteste5\n");
    ini->id++;
    printf("\nteste5.5\n");
    if(ini==NULL){
        ini->inicio=aux;
        *b=true;
        return aux;
    }
    printf("\nteste6\n");
    while (ant->proxv!=NULL)ant=ant->proxv;
    if(ant!=NULL)ant->proxv=aux;
    *b=true;
    return aux;
}

bool addAdj(graph* inicio, int oriID, int destID, int custo){
    vertice* vert=inicio;
    adj* ant=NULL;
    while(vert->id!=oriID){
        if(vert->proxv!=NULL)vert=vert->proxv;
        else return false;
    }
    adj* aux=(adj*)malloc(sizeof(adj));
    if (aux==NULL)return false;
    aux->prox=NULL;
    aux->custo=custo;
    aux->id=destID;
    if(vert->ini!=NULL)ant=vert->ini;
    else vert->ini=aux;
    while (ant->prox!=NULL)ant=ant->prox;
    if(ant!=NULL)ant->prox=aux;
    return true;
}

bool removeAdj(graph* inicio, int oriID, int destID){
    vertice* vert=inicio;
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
    adj* ante=NULL;
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
                ante=aux;
                aux=aux->prox;
                atual=aux;
                aux=aux->prox;
                ant->proxv=aux;
                free(atual);
            }
        }
        vert=vert->proxv;
    }
    *e=0;
    return graph;
}

graph* mLine(char* filename, int *id, int local){
    graph* ini=NULL;
    int num;
    char s;
    bool r;
    FILE* file=fopen(filename,"r");
    if(file==NULL)return NULL;
    for (int i = 0; i < local; i++)
    {
        fscanf(file, "%*[^\n]\n");
    }
    if(fscanf(file,"%d",num)!=1)return ini;
    vertice* vert=addVertice(ini,&r);
    ini->inicio=vert;
    int custoIni=num;
    vertice* aux=NULL;
    while (fscanf(file,"%c%d",num,s)==2)
    {
        if(s=='\n')break;
        aux=addVertice(ini,&r);
        vert->proxv=aux;
        addAdj(ini,vert->id,aux->id,num);
        vert=vert->proxv;
    }
    vert=ini;
    adj* aux2=vert->ini;
    aux2->custo+=custoIni;
    fclose(file);
    return ini;
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
    grafo->id=0;
    grafo->numTv=nTotalVert;
    grafo->inicio=NULL;
    while (!feof(file))
    {
        adj=lerFull(file);
        if(adj!=NULL){ //erro ao criar adj em ler()
            v=addVertice(grafo,&b);
            printf("\nteste\n");
            v->ini=adj;
            if(i==0){
                grafo->inicio=v;
                i++;
            }
        }
    }
    verticeCheck(grafo->inicio);
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
            printf("\nteste3 %d %d\n",num, i);
            if(aux==NULL)return NULL;//erro ao criar adj
            if(i==1)ini=aux;
            else ant->prox=aux; 
            ant=aux;
        }
        if(feof(file) || c=='\n'){
            //printf("\ntesteMEGA %c1\n",c);
            break;
        }
        i++;
    }
    printf("\ntesteExit %d %d\n",ini->custo,ini->id);
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
            if(!found)addVertice(ini,&b);
            aux=aux->prox;
            found=false;
        }
        vert=vert->proxv;
    }
    return true;
}