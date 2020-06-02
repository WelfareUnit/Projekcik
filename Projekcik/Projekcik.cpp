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
void space()
{
	printf("\n");
}

int main()

{

	double Bst[N];
	double Xst[N];
	double macierz[N][N];
	double** hilbert;

	int n = 0;
	printf("Podaj ilosc rownan<=50\n");
	do
	{
		scanf("%d" ,& n);
		space();
	} while (n > 50 || n <= 0);
	int i = 0;
	int j = 0;
	hilbert = (double**)(malloc(N * sizeof(double*)));
	for (i = 0; i < n; i++)
	{
		hilbert[i] = (double*)(malloc(N * sizeof(double)));
	}

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			macierz[i][j] = 1. / (1. + i + j);


		}
		space();
	}

	
	HilbertMatrix(n, macierz);
	displayMatrix(n, macierz);
	computeVec(n, macierz, Bst);
	gauss(n, macierz, Bst, Xst);
	plotVec(n, Xst);

	return 0;
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
		printf("%lg\t", v[i]);
	}
	printf("\n");
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
	printf("\n");
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
