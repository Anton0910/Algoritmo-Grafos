#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0
typedef int bool;
typedef int TIPOPESO;

typedef struct adjacencia {
    int vertice;
    TIPOPESO peso;
    struct adjacencia *prox;
}ADJACENCIA;

typedef struct vertice {

    ADJACENCIA *cab;
}VERTICE;

typedef struct grafo {
    int vertices;
    int arestas;
    VERTICE *adj;
}GRAFO;

GRAFO *criaGrafo (int v) {
	int i;

	GRAFO *g = (GRAFO *)malloc(sizeof(GRAFO));
	g->vertices = v;
	g->arestas = 0;
	g->adj = (VERTICE *)malloc(v*sizeof(VERTICE));


	for (i=0; i<v; i++){
		g->adj[i].cab=NULL;
	}
	return(g);
}



ADJACENCIA *criaAdj(int v, int peso){
	ADJACENCIA *temp = (ADJACENCIA *) malloc (sizeof(ADJACENCIA));
	temp->vertice =v;
	temp->peso = peso;
	temp->prox = NULL;
	return(temp);
}

bool criaAresta(GRAFO *gr, int vi, int vf, TIPOPESO p) {
	if(!gr) return (false);
	if((vf<0)||(vf >= gr->vertices))return(false);
	if((vi<0)||(vf >= gr->vertices))return(false);

	ADJACENCIA *novo = criaAdj(vf,p);

	novo->prox = gr->adj[vi].cab;
	gr->adj[vi].cab=novo;
	gr->arestas++;
	return (true);
}

void imprime(GRAFO *gr){


	printf("Vertices: %d. Arestas: %d. \n",gr->vertices,gr->arestas);
	int i;

	for(i=0; i<gr->vertices; i++){
		printf("v%d: ",i);
		ADJACENCIA *ad = gr->adj[i].cab;
			while(ad){
				printf("v%d(%d) ",ad->vertice,ad->peso);
				ad=ad->prox;
			}
		printf("\n");
	}
}


void DFS(GRAFO *g, int v, int *visitado) {
    visitado[v] = true;
    printf("%d ", v);

    ADJACENCIA *adj = g->adj[v].cab;
    while (adj != NULL) {
        if (!visitado[adj->vertice]) {
            DFS(g, adj->vertice, visitado);
        }
        adj = adj->prox;
    }
}

void buscaProfundidade(GRAFO *g) {
    int i;
    int visitado[g->vertices];

    for (i = 0; i < g->vertices; i++) {
        visitado[i] = false;
    }

    for (i = 0; i < g->vertices; i++) {
        if (!visitado[i]) {
            DFS(g, i, visitado);
        }
    }
}


void BFS(GRAFO *g, int v, int *visitado) {
   //CRIA FILA E INSERE O INICIO NA FILA
    int fila[g->vertices];
    int inicio = 0;
    int fim = 0;

    visitado[v] = true;
    printf("%d ", v);
    fila[fim++] = v;
    //PEGA O PRIMEIRO ELEMENTO DA FILA
    while (inicio != fim) {
        int u = fila[inicio++];
        ADJACENCIA *adj = g->adj[u].cab;
        //VISITA OS VIZINHOS AINDA NAO VISITADOS E COLOCA ELES NA FILA
        while (adj != NULL) {
            if (!visitado[adj->vertice]) {
                visitado[adj->vertice] = true;
                printf("%d ", adj->vertice);
                fila[fim++] = adj->vertice;
            }
            adj = adj->prox;
        }
    }
}

void buscaLargura(GRAFO *g) {
    int i;
    int visitado[g->vertices];

    for (i = 0; i < g->vertices; i++) {
        visitado[i] = false;
    }

    for (i = 0; i < g->vertices; i++) {
        if (!visitado[i]) {
            BFS(g, i, visitado);
        }
    }
}

int main()
{

	GRAFO * gr = criaGrafo(5);
	criaAresta(gr, 0, 1, 2);
	criaAresta(gr, 1, 2, 4);
	criaAresta(gr, 2, 0, 12);
	criaAresta(gr, 2, 4, 40);
	criaAresta(gr, 3, 1, 3);
	criaAresta(gr, 4, 3, 8);

    imprime(gr);

    printf("\nBusca em profundidade: ");
    buscaProfundidade(gr);

    printf("\n\nBusca em largura: ");
    buscaLargura(gr);
}
