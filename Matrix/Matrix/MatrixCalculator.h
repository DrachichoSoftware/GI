#pragma once
#include "iostream"
#include "vector"

using namespace std;

typedef vector<vector<double>> MATRIX;

static class MatrixCalculator
{
private:
	static double GetDeterminant(MATRIX matrix);
	static MATRIX GetMinor(MATRIX matrix, int row, int column);
	static MATRIX Exclude(MATRIX matrix, int row, int column);
public:
	MatrixCalculator();
	~MatrixCalculator();

	static MATRIX AddMatrix(MATRIX firstMATRIX, MATRIX secondMATRIX);
	static MATRIX MultiplyMatrix(MATRIX firstMATRIX, MATRIX secondMATRIX);
	static MATRIX MultiplyOnNumber(double number, MATRIX MATRIX);
	static MATRIX TransposeMatrix(MATRIX MATRIX);
	static MATRIX GetReverceMatrix(MATRIX MATRIX);
};

