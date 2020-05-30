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


}

void HilbertMatrix(int N, double** H)
{
	for (int i= 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			H[i][j] = 1. / (1. + i + j);

	}
}

void displayMatrix(int N, double** H)
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
