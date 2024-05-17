#include "header.h"
//passeio

int main(){
    const char* filename="nums.txt";
    bool *r;
    int *id=0;
    graph* ini=criaGraph(filename,&r,&id,1,2);
    printf("\nAdd vertice to graph\n");
    addVertice(ini,&id,&r);
    printf("\nAdd destination to a vertice\n");
    addAdj(ini,3,id,40,&r);
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

vertice* addVertice(graph* ini, int *id, bool *b){
    vertice* aux=NULL;
    vertice* ant=ini;
    aux=(vertice*)malloc(sizeof(vertice));
    if (aux==NULL){
        *b=false;
        return NULL;
    }
    aux->proxv=NULL;
    aux->ini=NULL;
    aux->id=*id;
    (*id)++;
    if(ini==NULL){
        ini->inicio=aux;
        *b=true;
        return aux;
    }
    while (ant->proxv!=NULL)ant=ant->proxv;
    if(ant!=NULL)ant->proxv=aux;
    *b=true;
    return aux;
}

bool addAdj(graph* inicio, int vertID, int adjID, int custo){
    vertice* vert=inicio;
    adj* ant=NULL;
    while(vert->id!=vertID){
        if(vert->proxv!=NULL)vert=vert->proxv;
        else return false;
    }
    adj* aux=(adj*)malloc(sizeof(adj));
    if (aux==NULL)return false;
    aux->prox=NULL;
    aux->custo=custo;
    aux->id=adjID;
    if(vert->ini!=NULL)ant=vert->ini;
    else vert->ini=aux;
    while (ant->prox!=NULL)ant=ant->prox;
    if(ant!=NULL)ant->prox=aux;
    return true;
}

bool removeAdj(graph* inicio, int oriID, int destID){
    vertice* vert=inicio;
    adj* ant=NULL;
    while(vert->id!=oriID){
        if(vert->proxv!=NULL)vert=vert->proxv;
        else
        {
            return false;
        }
    }
    if(vert->ini!=NULL)ant=vert->ini;
    else return false;
    while(ant->prox->id!=adjID){
        if(ant->prox!=NULL)ant=ant->prox;
        else
        {
            return false;
        }
    }
    adj* del=ant->prox;
    adj* aux=NULL;
    if(del->prox!=NULL)aux=del->prox;
    ant->prox=aux;
    free(del);
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

graph* criaGrafo(char* filename, bool *r, int *id, int method){
    graph* ini;
    switch (method)
    {
    case 1:
        //line
        break;
    case 2:
        //column
        break;
    case 3:
        //full
        ini=criaGrafoFull(ini,&id,filename);
        break;
    default:
        *r=false;
        return NULL;
        break;
    }
    *r=true;
    return ini;
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
    vertice* vert=addVertice(ini,&id,&r);
    ini->inicio=vert;
    int custoIni=num;
    vertice* aux=NULL;
    while (fscanf(file,"%c%d",num,s)==2)
    {
        if(s=='\n')break;
        aux=addVertice(ini,&id,&r);
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

graph* criaGrafoFull(graph* graph, int *id, char* filename){
    FILE* file=fopen(filename,"r");
    if(file==NULL)return NULL;
    int i=0;
    bool *b;
    adj* adj=NULL;
    vertice* v=NULL;
    while (!eof(file))
    {
        adj=lerFull(file);
        if(adj!=NULL){ //erro ao criar adj em ler()
            v=addVertice(graph,&id,&b);
            v->ini=adj;
            if(i==0)graph->inicio=v;i++;
        }
    }
    verticeCheck(graph->inicio);
    return graph;
}

adj* lerFull(FILE* file){
    int num=NULL;
    char c='.';
    int i=0;
    adj* aux=NULL;
    adj* ant=NULL;
    adj* ini=NULL;
    while (c==';')
    {
        fscanf(file,"%d%c",num, c);
        if(num!=-1 && num!=NULL){
            aux=adjMalloc(num,i);
            if(aux==NULL)return NULL;//erro ao criar adj
            if(i==0)ini=aux;
            else ant->prox=aux; 
            ant=aux;
        }else if(num==NULL)i=-1;break;
        num=NULL;
        i++;
    }
    if (i==-1)delAllAdj(ini);return NULL;
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