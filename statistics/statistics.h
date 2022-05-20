#ifndef STATISTICS
#define STATISTICS
#include <vector>

using namespace std;

void printData(double** DataMatrix, int N_REGIONS, int M_WINES);
void getRow(double** DataMatrix, int M_WINES, int row_index, double row[]);
void getColumn(double** DataMatrix, int N_REGIONS, int column_index, double column[]);
double CalculateMean(double values[], int length);
double CalculateVariance(double values[], int length);
double CalculateSampleVariance(double values[], int length);
double GetStandardDeviation(double values[], int length);
double GetSampleStandardDeviation(double values[], int length);
double CalculateCovariance(double values1[], double values2[], int lenght);
double CalculateCorrelation(double values1[], double values2[], int lenght);
void ComputeCovarianceMatrix(double** DataMatrix, double** CovarianceMatrix, int M_WINES, int N_REGIONS);
/********************
 * Helper functions *
 ********************/
// for cleaning the memory
void cleanup(double** matrix, int rows);  // for cleaning the memory
double **transpose (double **matrix, int rows, int columns);
double **matrixFromArray (double array[], int rows, int columns);
// Read the data matrix from the standard input
void readMatrix (double **matrix, int rows, int columns);
// Print an array on the standard output
void printArray (double values[], int length);
// Prepare an empty matrix
double **prepareMatrix(int rows, int columns);
double **unpack (double values[], std::vector<int> &scenario, int size, int rows, int columns);
double hash (double vector[], int length);
#endif 