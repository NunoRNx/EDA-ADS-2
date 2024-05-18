#include "header.h"
//passeio

int main(){
    const char* filename="nums.txt";
    bool *r;
    graph* ini=criaGrafo(filename,10);
    /* printf("\nAdd vertice to graph\n");
    addVertice(ini,ini->nVert,&r);
    printf("\nAdd destination to a vertice\n"); 
    addAdj(ini,3,40,23);
    addAdj(ini,40,6,47); */
    printGraph(ini);
    /*
    *r==0 erro ao abrir ficheiro
    *r==-1 vertice erro
    *r==-2 adj erro
    */
    return 0;
}