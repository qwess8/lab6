// lab6.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <malloc.h>
#include <random>
#include <time.h>

int **createG(int size){
	int **G;
	G = (int**)malloc(size * sizeof(int*));
	for(int i = 0; i < size; i++){
		G[i] = (int*)malloc(size*sizeof(int));
	}
	for(int i = 0; i < size; i++){
		for(int j = i; j < size; j++){
			G[i][j] = rand()%2;
			if(i==j) G[i][j] = 0;
			G[j][i] = G[i][j];
		}
	}
	return G;
	}

void printG(int **G, int size){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			printf("%d ", G[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int **delG(int **G, int size, int v){
	int **G1 = createG(size-1);
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(j<v && i<v)	G1[i][j] = G[i][j];
			if(j>v && i<v)	G1[i][j-1] = G[i][j];
			if(j<v && i>v)	G1[i-1][j] = G[i][j];
			if(j>v && i>v)	G1[i-1][j-1] = G[i][j];
		}
	}

	for(int i = 0; i < size; i++){
		free(G[i]);
	}
	free(G);
	G = NULL;

	return G1;
}

//Отождествление
int **unionV(int **G, int size){
	int v1=0, v2=0;
	printf("ver1 for union =");
	scanf("%d", &v1);
	printf("ver2 for union =");
	scanf("%d", &v2);
	for(int i = 0; i < size; i++){
		if(G[i][v2] == 1){ 
			G[i][v1] = G[i][v2];
			G[v1][i] = G[v2][i];
		}
	}
	if(G[v1][v2] == 1) G[v1][v1] = 1;
	G = delG(G,size,v2);
	return G;
}

int **contrV(int **G, int size, int v1, int v2){
		G[v1][v2] = 0;
		G[v2][v1] = 0;
		for(int i = 0; i < size; i++){
			if(G[i][v2] == 1){ 
				G[i][v1] = G[i][v2];
				G[v1][i] = G[v2][i];
			}
		}
	
		G = delG(G,size,v2);
		G[v1][v1] = 0;
		return G;
}

int **splitV(int **G, int size, int v){
	int **G1 = createG(size+1);
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			G1[i][j] = G[i][j];
		}
	}
	for(int i = 0; i < size; i++){
		G1[size][i] = G[v][i];
		G1[i][size] = G[i][v];
	}

	G1[size][size] = 0;

	for(int i = 0; i < size; i++){
		free(G[i]);
	}
	free(G);
	G = NULL;

	printG(G1, size +1);
	return G1;

}

int **unionG(int **G1, int **G2, int size1, int size2){
	int sizemax = (size1>size2)?size1:size2;
	int sizemin = (size1<size2)?size1:size2;
	int **Gmax = (size1>size2)?G1:G2;
	int **Gmin = (size1<size2)?G1:G2;
	int **G3 = createG(sizemax);

	for(int i = 0; i < sizemin; i++){
		for(int j = 0; j < sizemin; j++){
			G3[i][j] = Gmin[i][j] | Gmax[i][j];
		}
	}
	for(int i = 0; i < sizemax; i++){
		for(int j = sizemin; j < sizemax; j++){
			G3[i][j] = Gmax[i][j];
			G3[j][i] = G3[i][j];
		}
	}

	printG(G3, sizemax);
	return G3;
}

int **intersectG(int **G1, int **G2, int size1, int size2){
	int sizemin = (size1<size2)?size1:size2;
	int **G3 = createG(sizemin);

	for(int i = 0; i < sizemin; i++){
		for(int j = 0; j < sizemin; j++){
			G3[i][j] = G1[i][j] & G2[i][j];
		}
	}

	printG(G3, sizemin);

	return G3;
}

int **xorG(int **G1, int **G2, int size1, int size2){
	int sizemax = (size1>size2)?size1:size2;
	int sizemin = (size1<size2)?size1:size2;
	int **Gmax = (size1>size2)?G1:G2;
	int **Gmin = (size1<size2)?G1:G2;
	int **G3 = createG(sizemax-sizemin);

	for(int i = sizemin; i < sizemax; i++){
		for(int j = sizemin; j < sizemax; j++){
			G3[i-sizemin][j-sizemin] = Gmax[i][j];
		}
	}

	return G3;
}

int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));
	int nG1, nG2, v1, v2;
	printf("nG1 =");
	scanf("%d", &nG1);
	printf("nG2 =");
	scanf("%d", &nG2);	

	int **G1 = createG(nG1);
	int **G2 = createG(nG2);

	printG(G1, nG1);
	printG(G2, nG2);
	/*
	printf("ver1 for contr =");
	scanf("%d", &v1);
	printf("ver2 for contr =");
	scanf("%d", &v2);
	
	
	if(G2[v1][v2] != 1){
		printf("No rebra");
	}
	else{
		G2 = contrV(G2,nG2, v1, v2);
		nG2--;
	}
	

	printf("\n");
	printG(G2, nG2);
	
	G1 = splitV(G1, nG1, 1);
	nG1++;
	*/

	int **G3 = unionG(G1,G2,nG1,nG2);
	int nG3 = (nG1>nG2)?nG1:nG2;

	int **G5 = xorG(G1, G2, nG1, nG2);
	int nG5 = (nG1-nG2>=0)?nG1:nG2;

	printG(G5,nG5);

	getchar();
	getchar();
	return 0;
}

