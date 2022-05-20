#include "statistics.h"
#include <iostream>
#include <algorithm>
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