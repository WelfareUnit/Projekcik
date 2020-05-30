#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "gauss.h"					//załączona biblioteka z funkcją RK
#pragma warning(disable:4996)		//umożlliwienie uzywania scanf w Visual 2019

void HilbertMatrix(int N, double** H);
void displayMatrix(int N, double** H);
void computeVec(int N, double** H, double* b);
void plotVec(int N, double* v);


int main()

{
	double tablica[2] = { 13,13 };
	double macierz[2][2];
	double** hilbert;
	
	int N = 2;
	int i = 0;
	int j = 0;
	hilbert = (double**)(malloc(N * sizeof(double*)));
	for (i = 0; i < N; i++)
	{
		hilbert[i] = (double*)(malloc(N * sizeof(double)));
	}
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			macierz[i][j] = i;

		}
		printf("\n");
	}	
	HilbertMatrix(N, hilbert);
	displayMatrix(N, hilbert);
	plotVec(N, tablica);

}

void HilbertMatrix(int N, double** H)
{
	for (int i= 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			H[i][j] = 1. / (1. + i + j);

	}
}

void plotVec(int N, double* v)
{
	for (int i = 0; i < N; i++)
	{
		printf("%lf", v[i]);
	}
}

void displayMatrix(int N, double(**H) )
{
	int i = 0, j = 0;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			printf("%lf\t", H[i][j]);

		}
		printf("\n");
	}
}
