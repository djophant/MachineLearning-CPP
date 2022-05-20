#include "statistics.h"
#include <iostream>
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
    
    return sum / (length-1);
}