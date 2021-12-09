// MSMPI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

void merge(int*, int*, int, int, int);
void mergeSort(int*, int*, int, int);

int main(int argc, char** argv) {

	
	/********** Inicijalizacija MPI **********/
	int world_rank;
	int world_size;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	/********** Alociraj niza so golemina n i dodeli vrednosti **********/
	int n = atoi(argv[1]);
	int* original_array{ new int[n] {} };
	int c;
	srand(time(NULL));

	if (world_rank == 0) {
		printf("This is the unsorted array: ");
		for (c = 0; c < n; c++) {

		original_array[c] = rand() % n;
		printf("%d ", original_array[c]);

		}
		printf("\n");
		printf("\n");
	}
	
	
	

	/********** Razdelija nizata na ednakvi delovi **********/
	int size = n / world_size;
	int* sub_array=NULL;
	int* tmp_array = NULL;
	int* sorted = NULL;

	if (world_rank == 0) {

		sorted = { new int[n] {} };

	}
		/********** Isprati na sekoj proces pod-niza **********/
		sub_array = { new int[size] {} };
		MPI_Scatter(original_array, size, MPI_INT, sub_array, size, MPI_INT, 0, MPI_COMM_WORLD);

		/********** Izvrsi go mergeSort na sekoj proces **********/
		tmp_array = { new int[size] {} };
		mergeSort(sub_array, tmp_array, 0, (size - 1));

		/********** Zemi gi sortirana pod-nizi i spoi gi **********/

		for (int i = 0; i < world_size; i++) {
			if (world_rank == i) {
				printf("Process [%d]: ", world_rank);
				for (int c1 = 0; c1 < size; c1++) {
					printf("%d ", sub_array[c1]);
				}
			}
		}

		MPI_Gather(sub_array, size, MPI_INT, sorted, size, MPI_INT, 0, MPI_COMM_WORLD);
	
		

	
	/********** Povik na posledniot mergeSort call **********/
	if (world_rank == 0) {

		printf("\nArray state before final mergeSort call: ");
		for (c = 0; c < n; c++) {

			printf("%d ", sorted[c]);

		}
		
		printf("\n");

		int* other_array{ new int[n] {} };
		mergeSort(sorted, other_array, 0, (n - 1));

		/********** Pecati sortirana niza **********/
		printf("This is the sorted array: ");
		for (c = 0; c < n; c++) {

			printf("%d ", sorted[c]);

		}

		printf("\n");
		printf("\n");

		/********** Oslobodi memorija **********/
		delete[] sorted;
		delete[] other_array;

	}

	/********** Oslobodi memorija **********/
	delete[] original_array;
	delete[] sub_array;
	delete[] tmp_array;

	/********** Finalize MPI **********/
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();

}

/********** Merge funkcija **********/
void merge(int* a, int* b, int l, int m, int r) {

	int h, i, j, k;
	h = l;
	i = l;
	j = m + 1;

	while ((h <= m) && (j <= r)) {

		if (a[h] <= a[j]) {

			b[i] = a[h];
			h++;

		}

		else {

			b[i] = a[j];
			j++;

		}

		i++;

	}

	if (m < h) {

		for (k = j; k <= r; k++) {

			b[i] = a[k];
			i++;

		}

	}

	else {

		for (k = h; k <= m; k++) {

			b[i] = a[k];
			i++;

		}

	}

	for (k = l; k <= r; k++) {

		a[k] = b[k];

	}

}

/********** Rekurzivna Merge Function **********/
void mergeSort(int* a, int* b, int l, int r) {

	int m;

	if (l < r) {

		m = (l + r) / 2;

		mergeSort(a, b, l, m);
		mergeSort(a, b, (m + 1), r);
		merge(a, b, l, m, r);

	}

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
