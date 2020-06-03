#include <iostream>
#include <math.h>
#include <stdlib.h>
#define N 50			
#pragma warning(disable:4996)		//umożlliwienie uzywania scanf w Visual 2019
void gauss(int n,/* double a[][N],*/double**a, double *b, double *x)			//funkcja z biblioteki gauss, przeklejona tutaj w celu modyfikacji dla alok. dyn.
{
	int i, j, k;
	double s;
	double wsp;

	//eliminacja

	// wiersz przy pomocy którego eliminujemy elementy
	for (i = 0; i < n - 1; i++)
	{
		// wersz którego elementy eliminujemy
		for (k = i + 1; k < n; k++)
		{
			wsp = a[k][i] / a[i][i];
			// odejmowanie elementów wiersza "i" od wiersza "k"
			for (j = i + 1; j < n; j++)
				a[k][j] -= a[i][j] * wsp;

			// odejmowanie prawych stron
			b[k] -= b[i] * wsp;
		}
	}

	//rozwiazanie ukladu
	x[n - 1] = b[n - 1] / a[n - 1][n - 1];

	for (i = n - 1; i >= 0; i--)
	{
		s = 0.0;
		for (j = i + 1; j < n; j++)
			s += a[i][j] * x[j];

		x[i] = (b[i] - s) / a[i][i];
	}
}
void HilbertMatrix(int n/*, double H[][N]*/, double** H)		//zakomentowane części są dla tablic alokowanych statycznie, odkomentowane dla dynamicznie
{
	int i = 0;
	int j = 0;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			H[i][j] = 1. / (1. + i + j);
		}

	}
}

void plotVec(int n, double* b)
{
	for (int i = 0; i < n; i++)
	{
		printf("%lg\t", b[i]);
	}
	printf("\n");
}

void displayMatrix(int n/*, double H[][N]*/, double** H)
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


void computeVec(int n/*, double H[][N]*/, double** H, double* v)
{
	for (int i = 0; i < n; i++)
	{
		v[i] = 0;
		for (int j = 0; j < n; j++)
		{
			v[i] += H[i][j];
		}
	}
}
double maxAbsError(int n, double *x)
{
	double max = 0;
	double error = 0;
	for (int i = 0; i < n; i++)
	{
		error = fabs(1 - x[i]);
		if (max < error)
		{
			max = error;
		}
	}
	return max;
}


void endl()
{
	printf("\n");
}

int main()
{
	int n = 1;
	int nmax = 0;
	printf("Podaj max ilosc rownan<=50\n");
	do
	{
		scanf("%d", &nmax);
		endl();
	} while (nmax > 50 || nmax <= 0);

	int i = 0;
	int j = 0;
	FILE* f1 = fopen("wyniki.txt", "w");
	double blad = 0;
	/*double bst[N];
	double xst[N];
	double macierz[N][N];
	*/
	double* xdyn;
	double* bdyn;
	double** hilbert;

	hilbert = (double**)(malloc(nmax * sizeof(double*)));			//dynamiczna alokacja macierzy na Hilberta
	for (i = 0; i < nmax; i++)
	{
		hilbert[i] = (double*)(malloc(nmax * sizeof(double)));
	}
	xdyn = (double*)(malloc(nmax * sizeof(double)));			//dynamiczna tablica na szukane i wyrazy wolne
	bdyn = (double*)(malloc(nmax * sizeof(double)));


	/*HilbertMatrix(n, macierz);						//dla alokacji statycznej
	displayMatrix(n, macierz);
	computeVec(n, macierz, bst);
	gauss(n, macierz, bst, xst);
	plotVec(n, xst);
	blad = maxAbsError(n, xst);
	*/
	fprintf(f1, "n\t bladmax\n");
	while (n <= nmax)
	{
		
		HilbertMatrix(n, hilbert);
		computeVec(n, hilbert, bdyn);
		gauss(n, hilbert, bdyn, xdyn);
		displayMatrix(n, hilbert);
		plotVec(n, xdyn);
		blad = maxAbsError(n, xdyn);
		fprintf(f1, "%d,%lf\n",n, blad);
		printf("%d,%lg\n", n, blad);
		n++;
	}
	for (i = 0; i < nmax; i++)
	{
		free(hilbert[i]);
	}
	free(hilbert);
	free(xdyn);
	free(bdyn);
	fclose(f1);
	return 0;
}

