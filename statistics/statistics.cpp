#include "statistics.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

void printData(double** DataMatrix, int N_REGIONS, int M_WINES)
{
    for(int i=0; i<N_REGIONS; i++)
    {
        for(int j=0; j<M_WINES; j++)
        {
            cout << DataMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

void getRow(double** DataMatrix, int M_WINES, int row_index, double row[])
{
    for(int i=0; i<M_WINES; i++)
    {
        row[i] = DataMatrix[row_index][i];
    }
}

void getColumn(double** DataMatrix, int N_REGIONS, int column_index, double column[])
{
    for(int j=0; j<N_REGIONS; j++)
    {
        column[j] = DataMatrix[j][column_index];
    }
}

double CalculateMean(double values[], int length)
{
    double sum = 0.0;
    for(int i=0; i<length; i++)
        sum += values[i];
    
    return sum / length;
}

double CalculateVariance(double values[], int length)
{
    double sum = 0.0; 
    double mean = CalculateMean(values, length);
    for(int i=0; i<length; i++)
        sum += pow(values[i]-mean, 2);
    
    return sum / length;
}

double CalculateSampleVariance(double values[], int length)
{
    double sum = 0.0; 
    double mean = CalculateMean(values, length);
    for(int i=0; i<length; i++)
        sum += pow(values[i]-mean, 2);
    
    return sum / (length-1);
}

double GetStandardDeviation(double values[], int length)
{
    double variance = CalculateVariance(values, length);
    return sqrt(variance);
}

double GetSampleStandardDeviation(double values[], int length)
{
    double sampleVariance = CalculateSampleVariance(values, length);
    return sqrt(sampleVariance);
}

double CalculateCovariance(double values1[], double values2[], int lenght)
{
    int m = sizeof(values1) / sizeof(*values1);
    int n = sizeof(values2) / sizeof(*values2);

    if (m == n && std::equal(values1, values1 + m, values2))
    {
        return CalculateVariance(values1, lenght);
    } 
    else
    {
        double sum = 0.0;
        double mean1 = CalculateMean(values1, lenght);
        double mean2 = CalculateMean(values2, lenght);

        for(int i=0; i<lenght; i++)
            sum += (values1[i] - mean1) * (values2[i] - mean2);
        
        return sum / lenght;
    }
}

double CalculateCorrelation(double values1[], double values2[], int lenght)
{
    double covariance = CalculateCovariance(values1, values2, lenght);
    double variance1 = CalculateVariance(values1, lenght);
    double variance2 = CalculateVariance(values2, lenght);
    double denominator = sqrt(variance1 * variance2);

    return covariance / denominator;
}



void ComputeCovarianceMatrix(double** DataMatrix, double** CovarianceMatrix, int M_WINES, int N_REGIONS)
{
    
}





double **matrixFromArray (double array[], int rows, int columns) 
{
    double **matrix = new double*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new double[columns];
        for (int j = 0; j < columns; j++)
            matrix[i][j] = array[i*columns + j];
    }
    return matrix;
}

double **transpose (double **matrix, int rows, int columns) 
{
    double **transposed = new double*[columns];
    for (int i = 0; i < columns; i++) {
        transposed[i] = new double[rows];
        getColumn(matrix, rows, i, transposed[i]);
    }
    return transposed;
}

void readMatrix (double **matrix, int rows, int columns)
{
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = new double[columns];
        for (int j = 0; j < columns; j++)
            cin >> matrix[i][j];
    }
}

void printArray (double values[], int length)
{
    for (int i = 0; i < length - 1; i++)
        cout << values[i] << " ";

    cout << values[length - 1];
}

// Prepare an empty matrix
double **prepareMatrix(int rows, int columns) 
{
    double **matrix = new double* [rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new double[columns];
        for (int j = 0; j < columns; j++)
            matrix[i][j] = 0;
    }

    return matrix;
}

double **unpack (double values[], vector<int> &scenario, int size, int rows, int columns) 
{
    double **matrix = new double*[size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new double[size];
        if (i < rows) {
            for (int j = 0; j < columns; j++)
                matrix[i][j] = values[i*columns + j];
            for (int j = columns; j < size; j++)
                matrix[i][j] = 1;
        } else {
            for (int j = 0; j < size; j++)
                matrix[i][j] = 1;
        }
    }

    return matrix;
}

double hash (double vector[], int length) 
{
    double sum  = 0;
    for (int i = 0; i < length; i++)
        sum += vector[i];
    return sum;
} 

void cleanup (double **matrix, int rows)
{
    for (int i = 0; i < rows; i++)
        delete[] matrix[i];
    delete matrix;
}