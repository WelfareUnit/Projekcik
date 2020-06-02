#include <iostream>
#include <math.h>
#include <stdlib.h>
#define N 50
#include "gauss.h"					//załączona biblioteka z funkcją RK
#pragma warning(disable:4996)		//umożlliwienie uzywania scanf w Visual 2019
void HilbertMatrix(int n, double H[][N]);
void displayMatrix(int n, double H[][N]);
void computeVec(int n, double A[][N], double v[]);
void plotVec(int n, double v[]);


int main()

{

	double Bst[2];
	double Xst[2];
	double macierz[2][2];
	double** hilbert;

	int n = 2;
	int i = 0;
	int j = 0;
	hilbert = (double**)(malloc(n * sizeof(double*)));
	for (i = 0; i < n; i++)
	{
		hilbert[i] = (double*)(malloc(n * sizeof(double)));
	}
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			macierz[i][j] = 1. / (1. + i + j);


		}
		printf("\n");
	}


	//HilbertMatrix(n, hilbert);
	gauss(n, hilbert, Bst, Xst);


}

void HilbertMatrix(int n, double H[][N])
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			H[i][j] = 1. / (1. + i + j);

	}
}

void plotVec(int n, double v[])
{
	for (int i = 0; i < n; i++)
	{
		printf("%lf", v[i]);
	}
}

void displayMatrix(int n, double H[][N])
{
	int i = 0, j = 0;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			printf("%lf\t", H[i][j]);

		}
		printf("\n");
	}
}

void computeVec(int n, double A[][N], double v[])
{
	for (int i = 0; i < n; i++)
	{
		v[i] = 0;
		for (int j = 0; j < n; j++)
		{
			v[i] += A[i][j];
		}
	}
}
