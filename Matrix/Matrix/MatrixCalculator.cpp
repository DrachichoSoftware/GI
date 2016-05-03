#include "stdafx.h"
#include "math.h"
#include "MatrixCalculator.h"
#include "iostream"
#include "vector"

using namespace std;

double MatrixCalculator::GetDeterminant(MATRIX matrix)
{
	if (matrix.size() != matrix[0].size())
	{
		throw "Матрица не квадратная";
	}

	double determinant = 0;
	int rank = matrix.size();

	if (rank == 1)
	{
		determinant = matrix[0][0];
	}
	else if (rank == 2)
	{
		determinant = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	}
	else
	{
		for (size_t i = 0; i < matrix[0].size(); i++)
		{
			determinant += pow(-1, i) * matrix[0][i] * GetDeterminant(GetMinor(matrix, 0, i));
		}
	}

	return determinant;
}


MATRIX MatrixCalculator::GetMinor(MATRIX matrix, int row, int column)
{
	if (matrix.size() != matrix[0].size())
	{
		throw "Матрица не квадратная";
	}
	
	MATRIX finalMatrix(matrix.size() - 1, vector<double>(matrix.size() - 1));

	for (size_t i = 0; i < matrix.size(); i++)
	{
		for (size_t j = 0; j < matrix[i].size(); j++)
		{
			if (i != row || j != column)
			{
				if ((int)i > row && (int)j < column) finalMatrix[i - 1][j] = matrix[i][j];
				if ((int)i < row && (int)j > column) finalMatrix[i][j - 1] = matrix[i][j];
				if ((int)i > row && (int)j > column) finalMatrix[i - 1][j - 1] = matrix[i][j];
				if ((int)i < row && (int)j < column) finalMatrix[i][j] = matrix[i][j];
			}
		}
	}
	
	return finalMatrix;
}

MATRIX MatrixCalculator::Exclude(MATRIX matrix, int row, int column)
{
	for (size_t i = 0; i < matrix.size(); i++)
	{
		for (size_t j = 0; j < matrix[j].size(); j++)
		{
			if ((int)j == column)
			{
				matrix[i].erase(matrix[i].begin() + j); // Удаляем столбец поэлементно
			}
		}
	}

	matrix.erase(matrix.begin() + row); // Удаляем строку

	return matrix;
}

MatrixCalculator::MatrixCalculator()
{
}


MatrixCalculator::~MatrixCalculator()
{
}

MATRIX MatrixCalculator::AddMatrix(MATRIX firstMatrix, MATRIX secondMatrix)
{
	MATRIX finalMatrix;
	for (size_t i = 0; i < firstMatrix.size(); i++)
	{
		for (size_t j = 0; j < firstMatrix[i].size(); j++)
		{
			finalMatrix[i][j] = firstMatrix[i][j] + secondMatrix[i][j];
		}
	}
	
	return finalMatrix;
}


MATRIX MatrixCalculator::MultiplyMatrix(MATRIX firstMatrix, MATRIX secondMatrix)
{
	MATRIX finalMatrix;
	int rows = firstMatrix.size();
	int cols = secondMatrix[0].size();
	int inner = secondMatrix.size();

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			for (int k = 0; k < inner; k++)
			{
				finalMatrix[i][j] = firstMatrix[i][k] * secondMatrix[k][j];
			}
		}
	}
	
	return finalMatrix;
}

MATRIX MatrixCalculator::MultiplyOnNumber(double number, MATRIX multiplyingMatrix)
{
	MATRIX finalMatrix;

	for (size_t i = 0; i < multiplyingMatrix.size(); i++)
	{
		for (size_t j = 0; j < multiplyingMatrix[i].size(); j++)
		{
			finalMatrix[i][j] = number * multiplyingMatrix[i][j];
		}
	}
	
	return finalMatrix;
}

MATRIX MatrixCalculator::TransposeMatrix(MATRIX transposeningMatrix)
{
	double tmp;

	for (size_t i = 0; i < transposeningMatrix.size(); i++)
	{
		for (size_t j = 0; j < transposeningMatrix[j].size(); j++)
		{
			tmp = transposeningMatrix[i][j];
			transposeningMatrix[i][j] = transposeningMatrix[j][i];
			transposeningMatrix[j][i] = tmp;
		}
	}

	return transposeningMatrix;
}

MATRIX MatrixCalculator::GetReverceMatrix(MATRIX revercingMatrix)
{
	if (revercingMatrix.size() != revercingMatrix[0].size())
	{
		throw "Матрица не квадратная";
	}

	MATRIX finalMatrix(revercingMatrix.size(), vector<double>(revercingMatrix.size()));
	double determinant = GetDeterminant(revercingMatrix);

	if (determinant == 0) // Вырожденная матрица
		return revercingMatrix;

	for (size_t i = 0; i < revercingMatrix.size(); i++)
	{
		for (size_t j = 0; j < revercingMatrix[i].size(); j++)
		{
			MATRIX tmp = Exclude(revercingMatrix, i, j);  // Получаем матрицу без i-го столбца и j-ой строки
			finalMatrix[i][j] = (1 / determinant) * GetDeterminant(tmp);
		}
	}

	return finalMatrix;
}

