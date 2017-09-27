#include "bibliotecas.h"

double** declaraMatriz(int nroCidades){
	int i,j;

	double** Grafo = new double*[nroCidades];
	for(i = 0; i < nroCidades; i++)
    	Grafo[i] = new double[nroCidades];

	for(i = 0; i < nroCidades; i++){
		for(j = 0;j < nroCidades; j++){
			Grafo[i][j] = 0x3f3f3f; //seta como infinito
		}
	}

    return Grafo;
}

void insereAresta(double **M, int cidade1, int cidade2, double peso){
	//Supõe-se que sempre deslocarão pela estrada de menor peso entre 2 cidades.
	M[cidade1][cidade2] = min(M[cidade1][cidade2], peso);
	M[cidade2][cidade1] = min(M[cidade2][cidade1], peso);
}

void floydWarshall(double **M, int nrocidades){
	int i,j,k;

	for(i = 0;i<nrocidades;i++)
		M[i][i] = 0; //diagonais como 0

	for(k = 0;k<nrocidades;k++){
		for(i = 0; i < nrocidades; i++){
			for(j = 0;j < nrocidades; j++){
					M[i][j] = min(M[i][j], M[i][k] + M[k][j]);
			}
		}
	}

}

int criterioUm(double **M, int nrocidades, int *distribAlunos){
	floydWarshall(M, nrocidades);

	double *auxPeso = new double[nrocidades]; //equivalente ao malloc
	memset(auxPeso, 0, sizeof(auxPeso)); //Seta a matriz toda como zero

	int i,j;
	for(i = 0; i < nrocidades; i++){
		for(j = 0;j < nrocidades; j++){
			auxPeso[j] += M[i][j] * distribAlunos[i];
		}
	}

	double minDist = 0x3f3f3f; //Infinito
	int cidadeEscolhida;
	for(i=0;i<nrocidades;i++){
		if(auxPeso[i] < minDist){
			minDist = auxPeso[i];
			cidadeEscolhida = i;
		}
	}

	for(i=0;i<nrocidades;i++)
		cout << auxPeso[i] << " ";

	free(auxPeso); //free no vetor auxiliar
	return cidadeEscolhida; //transforma em 1 based para o retorno
}