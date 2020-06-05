
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define N 50
#pragma warning(disable:4996)		//umożlliwienie uzywania scanf w Visual 2019
void gauss(int n,/* float a[][N],*/float**a, float *b, float *x)			//funkcja z biblioteki gauss, przeklejona tutaj w celu modyfikacji dla alok. dyn.
{
	int i, j, k;
	float s;
	float wsp;

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
void trojk(int n,/* float a[][N],*/float** a,/* float t[][N],*/float** t) //funkcja obliczająca macierz trójkątną górną z danej macierz
{
	int i, j, k;
	float wsp=0;
	for (i = 0; i < n; i++) //przepisanie elementow macierzy na macierz, na której zapisana będzie trójkątna- pierwotna jest nietknięta
	{
		for (j = 0; j < n; j++)
		{
			t[i][j] = a[i][j];
		}

	}
	for (i = 0; i < n - 1; i++)
	{
		for (k = i + 1; k < n; k++)
		{
			wsp = t[k][i] / t[i][i];
			for (j = i; j < n; j++)
			{
				t[k][j] -= t[i][j] * wsp;
				
			}
		}
	}
}
float wyznaczniktrojk(int n,/* float a[][N],*/float** a)		//funkcja licząca wyznacznik macierzy trójkątnej
{
	float iloczyn = 1;
	int i = 0;
	for (i = 0; i < n; i++)
	{
		iloczyn *= a[i][i];			//mnożymy po porstu wszystkie elementy po przekątnej
	}
	return iloczyn;
}
void HilbertMatrix(int n/*, float H[][N]*/, float** H)		//zakomentowane części są dla tablic alokowanych statycznie, odkomentowane dla dynamicznie
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

void plotVec(int n, float* b)		//wyswietlanie wektora na ekran
{
	for (int i = 0; i < n; i++)
	{
		printf("%g\t", b[i]);
	}
	printf("\n");
}

void displayMatrix(int n/*, float H[][N]*/, float** H)		//wyswietlanie macierzy
{
	int i = 0, j = 0;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			printf("%f\t", H[i][j]);

		}
		printf("\n");
	}
	printf("\n");
}


void computeVec(int n/*, float H[][N]*/, float** H, float* v)		//obliczanie wektora B w Hilbercie
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
float maxAbsError(int n, float *x)			//funkcja liczaca maksymalne bezwzgl. odejście od wyniku w Hilbercie( Gdzie powinno wyjść 1)
{
	float max = 0;
	float error = 0;
	for (int i = 0; i < n; i++)
	{
		error = fabsf(1 - x[i]);
		if (max < error)
		{
			max = error;
		}
	}
	return max;
}

void endl()						//kiedy nie chce mi sie pisac printf("\n")
{
	printf("\n");
}

int main()
{
	int ktore;
	int n = 1;
	int nf1;
	int nf2;
	int nmax = 0;
	int wyznacznik = 0;
	FILE* f1 = fopen("bladfloat.txt", "w");
	FILE* f2 = fopen("macierz.txt", "r");
	FILE* f3 = fopen("wektor.txt", "r");
	do
	{	
		printf("1- Hilbert 2- Dane z pliku\n ");
		scanf("%d", &ktore);
	} while (ktore != 1 && ktore != 2);
	int i = 0;
	int j = 0;
	switch (ktore)							//Program ma dwie funkcje- 1 rozwiązuje układ równań z macierzą Hilberta, 
											//2- Rozwiązuje układ równań z danych w pliku
	{
	case 1:

		do
		{
			printf("Podaj max ilosc rownan<=50\n");		//wczytywanie ilosci rownan z klawiatury
			scanf("%d", &nmax);
			endl();
		} while (nmax > 50 || nmax <= 0);
		break;
	case 2:

		fscanf(f2, "%d", &nf1);		//wczytywanie ilosci rownan z plikow i ich porownywanie-
		fscanf(f3, "%d", &nf2);		//na poczatku pliku napisane jest, dla ilu rownan są te zapisane w nim dane
		if (nf1 != nf2)
		{
			printf("bledne dane w plikach!");
			return 0;
		}
		else nmax = nf1;
		break;
	}

	float blad = 0;
	/*float bst[N];
	float xst[N];
	float macierz[N][N];
	float trojkatna[N][N];
	*/
	float* xdyn;
	float* bdyn;
	float** macierzdyn;
	float** trojkatna;

	macierzdyn = (float**)(malloc(nmax * sizeof(float*)));			//dynamiczna alokacja macierzy na Hilberta
	for (i = 0; i < nmax; i++)
	{
		macierzdyn[i] = (float*)(malloc(nmax * sizeof(float)));
	}

	trojkatna = (float**)(malloc(nmax * sizeof(float*)));			//dynamiczna alokacja macierzy na trójkątną
	for (i = 0; i < nmax; i++)
	{
		trojkatna[i] = (float*)(malloc(nmax * sizeof(float)));
	}
	xdyn = (float*)(malloc(nmax * sizeof(float)));			//dynamiczna tablica na szukane i wyrazy wolne
	bdyn = (float*)(malloc(nmax * sizeof(float)));
	switch (ktore)
	{

	case 1:

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

			HilbertMatrix(n, macierzdyn);
			displayMatrix(n, macierzdyn);
			computeVec(n, macierzdyn, bdyn);
			trojk(n, macierzdyn, trojkatna);					// "Trójkącenie" macierzy Hilberta
			gauss(n, macierzdyn, bdyn, xdyn);

			displayMatrix(n, trojkatna);
			plotVec(n, xdyn);
			blad = maxAbsError(n, xdyn);
			fprintf(f1, "%d\t%g\n", n, blad);
			printf("%d\t%g\n", n, blad);
			n++;
		}
		break;

	case 2:

		for (i = 0; i < nmax; i++)
		{
			fscanf(f3, "%f", &bdyn[i]);			//pobieranie wektora z pliku
			for (j = 0; j < nmax; j++)
			{
				fscanf(f2, "%f", &macierzdyn[i][j]);			//pobieranie macierzy z pliku
			}
		}
		plotVec(nmax, bdyn);
		displayMatrix(nmax, macierzdyn);
		trojk(nmax, macierzdyn, trojkatna);
		endl();
		displayMatrix(nmax, trojkatna);
		if (fabsf(wyznaczniktrojk(n, trojkatna)) <= 0.00001)			//dla większych układów macierz trójkątna nie jest idealna, więc wyznacznik może nie być dokładnie =0 dla błędnej
		{
			gauss(nmax, macierzdyn, bdyn, xdyn);
			plotVec(nmax, xdyn);
		}
		else
		{
			printf("Wyznacznik macierzy rowny 0! Sprzeczny uklad rownan");
		}
			break;
		
	}
	for (i = 0; i < nmax; i++)
	{
		free(macierzdyn[i]);
	}
	free(macierzdyn);

	free(xdyn);
	free(bdyn);
	fclose(f1);
	fclose(f3);
	fclose(f2);

	return 0;
}

