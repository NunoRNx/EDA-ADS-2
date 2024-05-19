#include "header.h"
//passeio


int main(){
    const char* filename="nums.txt";
    bool *r;
    graph* ini=criaGrafo(filename);
    printf("\nAdd vertice to graph\n");
    addVertice(ini,ini->nVert,&r);
    printf("\nAdd destination to a vertice\n"); 
    addAdj(ini,3,40,23);
    addAdj(ini,40,6,47);
    printGraph(ini);
    //DFS(ini, ini->inicio,6,0,stack,highPath,0,false,&maior,&sizeHighPath);
    int custo=DFS(ini,1,6,true);
    printf("Caminho de maior custo entre 1 e 6: %d",custo);
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