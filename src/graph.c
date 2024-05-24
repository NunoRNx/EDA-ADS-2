/**
 * @file graph.c
 * @author Nuno Silva (a28005@alunos.ipca.pt)
 * @brief Ficheiro com processo de criação/exportação e importação do grafo
 * @version 0.1
 * @date 2024-05-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "header.h"

#pragma region criarGrafo (Txt/Csv)

graph* criaGrafo(const char* filename){
    int i=0;
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
        if(adj!=NULL){
            v=addvertice(grafo,grafo->nVert);
            if(v!=NULL){
                v->ini=adj;
                if(i==0){
                    grafo->inicio=v;
                    i++;
                }
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

int SaveGraph(graph* ini, char* filename) {

	if (ini==NULL || ini->inicio==NULL) return -1;
	FILE* file = fopen(filename, "wb");
	if (file == NULL) return -2;

	vertice* vert = ini->inicio;
    verticeBin auxfile;	//estrutura de vertice para gravar em ficheiro
	while (vert != NULL) {
		auxfile.id = vert->id;
		fwrite(&auxfile, 1, sizeof(verticeBin), file);
		//Pode gravar de imediato as adjacencias!
		if (vert->ini) {
            int size=snprintf(NULL, 0, "%d.bin", vert->id)+1;
            char* adjfile=(char*)malloc(size);
            if(!adjfile)perror("Erro");return -3;
            snprintf(adjfile, size, "%d.bin", vert->id);
			int r = SaveAdj(vert->ini, adjfile);
            free(adjfile);
			if (!r) break;
		}
		vert = vert->proxv;
	}
	fclose(file);
	return 1;
}
bool SaveAdj(adj* ini, char* filename) {
	FILE* file=fopen(filename,"wb");
	if (ini == NULL) return false;
	adj* aux = ini;
	adjBin auxFile;
	while (aux) {
		auxFile.id = aux->id;
		auxFile.custo = aux->custo;
		fwrite(&auxFile, 1, sizeof(adjBin), file);
		aux = aux->prox;
	}
	fclose(file);
	return true;
}

#pragma endregion

#pragma region Import (bin)

graph* LoadGraph(char* fileName, bool* res) {
    graph* ini=criaGrafoIni();
    if(!ini)return NULL;
	FILE* file = fopen(fileName, "rb");
	if (file == NULL) perror("Erro");return NULL;
    *res = false;
	verticeBin auxfile;
	while (fread(&auxfile, 1, sizeof(verticeBin), file)) {
		addVertice(ini, auxfile.id);
	}
	fclose(file);
	return ini;
}

/**
 * @brief Load de Adjacencias de um Grafo. REVER!!!
 *
 * @param g
 * @param fileName
 * @param res
 * @return
 * @author lufer
 *
 */
vertice* LoadAdj(vertice* g, bool* res) {
	*res = false;
	FILE* fp;
	if (g == NULL) return -1;
	AdjFile aux;
	vertice* auxGraph = g;
	while (auxGraph) {
		fp = fopen(auxGraph->cidade, "rb");
		if (fp != NULL) {
			while (fread(&aux, 1, sizeof(AdjFile), fp)) {
				g = InsereAdjacenteverticeCod(g, aux.codOrigem, aux.codDestino, aux.weight, res);
			}
			fclose(fp);
		}
		auxGraph = auxGraph->next;
	}
	return g;
}

graph* criaGrafoIni(){
    graph* ini=(graph*)malloc(sizeof(graph));
    if(!ini)perror("Erro");return NULL;
    return ini;
}

#pragma endregion