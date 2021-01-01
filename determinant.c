#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int det(int **matrix, int order);
int **alloc_tbl_2D(int lignes, int colonnes);
void init_matrix(int **matrix, int order);
void minor(int **from, int **to, int from_order, int to_order, int except);
void display(int **arr, int order);
void init_tableau(int **tbl, int lignes, int colonnes) {
	int i, j;
	srand(time(NULL));
	for(int i = 0; i < lignes; i++) {
		for(int j = 0; j < colonnes; j++) {
			tbl[i][j] = rand()%100;
		}
	}
}

int main(int argc, char const *argv[])
{
	int **matrix, determinant, order;
	printf("\nCalculer le determinant\n");
	printf("Entez la taille de votre matrice: ");
	scanf("%d", &order);
	matrix = alloc_tbl_2D(order, order);
	init_matrix(matrix, order);
	// init_tableau(matrix, order, order);
	display(matrix, order);
	determinant = det(matrix, order);
	printf("\n\tLe determinant de votre matrice est: %d\n", determinant);
	return 0;
}

void display(int **arr, int order) {
	for(int i = 0; i < order; i++) {
		printf("\n\t|");
		for(int j = 0; j < order; j++) {
			printf(" %2d ", arr[i][j]);
		}
		printf("|");
	}
	printf("\n");
}

int **alloc_tbl_2D(int lignes, int colonnes) {
	int **tbl, i;
	tbl = (int **)malloc(sizeof(int *) * lignes);
	if(tbl == NULL) {
		printf("Erreur allocation\n");
		exit(22);
	}
	for(i = 0; i < lignes; i++) {
		tbl[i] = (int *)malloc(sizeof(int) * colonnes);
		if(tbl[i] == NULL) {
			printf("Erreur allocation\n");
			exit(22 + i);
		}
	}
	return tbl;
}

void init_matrix(int **matrix, int order) {
	int i, j;
	for(i = 0; i < order; i++) {
		printf("Line %d: \n", i+1);
		for(j = 0; j < order; j++) {
			printf("\tColonne %d: ", j+1);
			scanf("%d", &matrix[i][j]);
		}
	}
}

void minor(int **from, int **to, int from_order, int to_order, int except) {
	int i, j;
	int i_to = 0;
	int j_to = 0;
	for(i = 1; i < from_order; i++) {
		for(j = 0; j < from_order; j++) {
			if(j == except) {
				continue;
			} else {
				to[i_to][j_to] = from[i][j];
				j_to++;
			}
		}
		i_to++;
		j_to = 0;
	}
}

int det(int **matrix, int order) {
	int i, j;
	int determinant = 0;
	int **sub_matrix;
	if(order == 2) {
		return (matrix[0][0]*matrix[1][1])-(matrix[0][1]*matrix[1][0]);
	} else {
		for(i = 0; i < order; i++) {
			sub_matrix = alloc_tbl_2D(order-1, order-1);
			minor(matrix, sub_matrix, order, order-1, i);
			determinant += matrix[0][i]*pow(-1, 2+i)*det(sub_matrix, order-1);
		}
	}
	return determinant;
}
