#include "header.h"
//passeio


int main(){
    const char* filename="nums.txt";
    bool *r;
    int stack[numTv];
    int highPath[numTv];
    int maior=0, sizeHighPath=0;
    graph* ini=criaGrafo(filename);
    printf("\nAdd vertice to graph\n");
    addVertice(ini,ini->nVert,&r);
    printf("\nAdd destination to a vertice\n"); 
    addAdj(ini,3,40,23);
    addAdj(ini,40,6,47);
    printGraph(ini);
    //DFS(ini, ini->inicio,6,0,stack,highPath,0,false,&maior,&sizeHighPath);
    int i=DFS(ini, ini->inicio,6,0,stack,highPath,0,true,&maior,&sizeHighPath);
    printf("teste custo: %d\n", maior);
    printf("teste2 custo: %d\n", i);
    //printPath(highPath,sizeHighPath);
    //printf("\nCusto: %d",*maior);
    /* saveGraphToBin(ini,"export.bin");
    loadBinGraph(ini,"export.bin"); */
    /*
    *r==0 erro ao abrir ficheiro
    *r==-1 vertice erro
    *r==-2 adj erro
    */
    return 0;
}