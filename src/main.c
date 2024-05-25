#include "header.h"

int main(){
    //graph* ini=LoadGraph();
    //printGraph(ini);
    const char* filename="nums.txt";
    graph* ini=criaGrafo(filename);
    bool *r;
    printf("\nAdd vertice to graph\n");
    addVertice(ini,ini->nVert);
    printf("\nAdd destination to a vertice\n");
    addAdj(ini,3,40,23);
    addAdj(ini,40,6,47);
    printGraph(ini);

   /*  DFS(ini,1,5,false);
    int custo=DFS(ini,1,5,true);
    printf("\nCaminho de maior custo entre 1 e 5: %d\n",custo);
    removeVert(ini,5,&r);
    custo=DFS(ini,1,5,true);
    printf("\nCaminho de maior custo entre 1 e 5: %d\n",custo); */

    SaveGraph(ini);
    return 0;
}