#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void SwapRows(float** Matrix, int pivotIndx, int kIndx, int Size)
{
	int i = 0;
	float tempValP = 0.0;
	for (i = 0; i < Size; i++)
	{
		tempValP = Matrix[kIndx][i];
		Matrix[kIndx][i] = Matrix[pivotIndx][i];
		Matrix[pivotIndx][i] = tempValP;
	}
}

void Multiply(float** Matrix, float** L, float** U, int Size)
{
	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			Matrix[i][j] = 0;
			for (int k = 0; k < Size; k++)
				Matrix[i][j] += L[i][k] * U[k][j];
		}
	}
}

void FillMatrixWithZeros(float** matrix, int matrixLength)
{
	for (int i = 0; i < matrixLength; i++)
	{
		for (int j = 0; j < matrixLength; j++)
		{
			matrix[i][j] = 0;
		}
	}
}

void ShowMatrix(float** matrix, int matrixLength)
{

	for (int i = 0; i < matrixLength; i++)
	{
		for (int j = 0; j < matrixLength; j++)
		{
			printf("%.2lf \t", matrix[i][j]);
		}
		printf("\n");
	}
}

float** AllocateMemory(int matrixLength)
{
	float** matrix = malloc(matrixLength * sizeof(float*));

	for (int i = 0; i < matrixLength; i++)
	{
		matrix[i] = malloc(matrixLength * sizeof(float));
	}

	return matrix;
}

void Doolittle(float** Matrix, float** L, float** U, float** P, int Size)
{
	int i, j, k, p, pivotIndex;
	float tempSum, pivot;
	float *arr = (float*)malloc(sizeof(float) * Size);

	//////// Identity matrix ////////
	for (i = 0; i<Size; i++)
	{
		P[i][i] = 1.0;
	}

	//////// Ones on diagonal ///////
	for (i = 0; i<Size; i++)
	{
		L[i][i] = 1.0;
	}

	/////// Creating local copy of main matrix //////////
	float** MatrixPrim = AllocateMemory(Size);
	for (i = 0; i < Size; i++)
	{
		for (j = 0; j < Size; j++)
		{
			MatrixPrim[i][j] = Matrix[i][j];
		}
	}

	/////// Main loop for 1, ..., Size //////
	for (k = 0; k<Size; k++)
	{
		/////// Handle pivot selection //////
		pivot = MatrixPrim[k][k];
		pivotIndex = k;

		for (i = 0; i < Size; i++)
		{
			arr[i] = MatrixPrim[i][k];
			if (MatrixPrim[i][k] < 0.0)
				arr[i] = fabsf(MatrixPrim[k][i]);
		}

		for (i = k; i < Size; i++)
		{
			if (arr[i] > fabsf(MatrixPrim[k][pivotIndex]))
				pivotIndex = i;
		}

		/////// Swap rows in MatrixPrim /////
		/////// and identity matrix P ///////
		if (pivotIndex != k)
		{
			SwapRows(MatrixPrim, pivotIndex, k, Size);
			SwapRows(P, pivotIndex, k, Size);
		}

		if (MatrixPrim[k][k] == 0.0)
		{
			printf("Matrix is singular.");
			system("pause");

		}
		
		/////// Loop for columns in U ///////
		/////// Row k in matrix U ///////////
		for (j = k; j<Size; j++)
		{
			tempSum = 0.0;

			for (p = 0; p<k; p++)
			{
				tempSum += L[k][p] * U[p][j];
			}
			U[k][j] = MatrixPrim[k][j] - tempSum;
		}

		/////// Loop for rows in L ///////
		/////// Column k in matrix L /////
		for (i = k + 1; i<Size; i++)
		{
			tempSum = 0.0;

			for (p = 0; p<k; p++)
			{
				tempSum += L[i][p] * U[p][k];
			}
			L[i][k] = (MatrixPrim[i][k] - tempSum) / U[k][k];
		}
	}

	return;
}

void DoolittleOriginal(float** Matrix, float** L, float** U, int Size)
{
	int i, j, k, p;
	float tempSum;

	//////// Ones on diagonal ///////
	for (i = 0; i<Size; i++)
	{
		L[i][i] = 1.0;
	}

	/////// Main loop for 1, ..., Size //////
	for (k = 0; k<Size; k++)
	{
		/////// Loop for columns in U ///////
		/////// Row k in matrix U ///////////
		for (j = k; j<Size; j++)
		{
			tempSum = 0.0;


			for (p = 0; p<k; p++)
			{
				tempSum += L[k][p] * U[p][j];
			}
			U[k][j] = Matrix[k][j] - tempSum;
		}

		/////// Loop for rows in L ///////
		/////// Column k in matrix L /////
		for (i = k + 1; i<Size; i++)
		{
			tempSum = 0.0;

			for (p = 0; p<k; p++)
			{
				tempSum += L[i][p] * U[p][k];
			}
			L[i][k] = (Matrix[i][k] - tempSum) / U[k][k];
		}
	}

	return;
}

int main()
{
	int Size, i, j;
	printf("Write size of matrix:\n");
	scanf("%d", &Size);

	float** Matrix = AllocateMemory(Size);
	float** L = AllocateMemory(Size);
	float** U = AllocateMemory(Size);
	float** Rec = AllocateMemory(Size);
	float** P = AllocateMemory(Size);
	float** TempLU = AllocateMemory(Size);

	///
	/*
	int x = 0;

	FILE *pFile;
	fopen_s(&pFile, "C:\\Users\\komputer\\Desktop\\Zad5NewVersion\\Zad5NewVersion\\Zad5NewVersion\\macierz.txt", "a+");
	fseek(pFile, 0, SEEK_SET);

	for (int i = 0; i < Size; i++)
	{
	for (int j = 0; j < Size; j++)
	{
	fscanf_s(pFile, "%d", &x);
	printf("%d \n", x);
	}
	}
	*/
	///

	printf("\nEnter matrix element:\n");
	for (i = 0; i<Size; i++)
	{
		for (j = 0; j<Size; j++)
		{
			printf("Enter Matrix[%d][%d] element: ", i, j);
			scanf("%f", &Matrix[i][j]);
		}
	}

	///

	FillMatrixWithZeros(L, Size);
	FillMatrixWithZeros(U, Size);
	FillMatrixWithZeros(Rec, Size);
	FillMatrixWithZeros(TempLU, Size);
	FillMatrixWithZeros(P, Size);

	Doolittle(Matrix, L, U, P, Size);

	printf("Matrix:\n");
	ShowMatrix(Matrix, Size);
	printf("\nL:\n");
	ShowMatrix(L, Size);
	printf("\nU:\n");
	ShowMatrix(U, Size);
	printf("\nP:\n");
	ShowMatrix(P, Size);

	Multiply(TempLU, L, U, Size);
	printf("\nReconstructed LU:\n");
	ShowMatrix(TempLU, Size);
	Multiply(Rec, P, TempLU, Size);
	printf("\nReconstructed Matrix:\n");
	ShowMatrix(Rec, Size);

	//fclose(pFile);

	system("pause");
}