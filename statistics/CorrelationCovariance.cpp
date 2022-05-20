#include "statistics.h"
#include <iostream>

using namespace std; 



int main()
{
    int n_rows, m_cols;
    double** dataMatrix;
    cout << "Enter the number of rows" << endl;
    cin >> n_rows;
    //dataMatrix = new double*[n_rows];
    cout << "Enter the number of columns" << endl;
    cin >> m_cols;

    cout << "Enter elements of a matrix with " << n_rows << " rows and " 
                                               << m_cols << " columns\n";

    cout << "#####################" << endl;
    double arr[4] = {1, 2, 3, 4};
    dataMatrix = matrixFromArray(arr, n_rows, m_cols);

    // testing printData function 

    printData(dataMatrix, n_rows, m_cols);
    
    cout << "#####################" << endl;

    // testing getRow function 
    double row[m_cols];

    getRow(dataMatrix, m_cols, 1, row);

    for(int i=0; i<m_cols; i++)
    {
        cout << row[i] << " ";
    }
    cout << endl;
    cout << "#####################" << endl;

    // testing getColumn function 
    double column[n_rows];

    getColumn(dataMatrix, n_rows, 1, column);

    for(int i=0; i<n_rows; i++)
    {
        cout << column[i] << endl;
    }
    cout << "#####################" << endl; 

    cout << "Calculate the mean and the variance of the row above.\n";
    cout << "The mean is " << CalculateMean(row, m_cols) << endl;
    cout << "The variance is " << CalculateVariance(column, n_rows) << endl;
    cout << "The covariance of row and cols is " << CalculateCovariance(row, column, n_rows) << endl;


    cout << "#####################" << endl; 
    // delete pointer 
    cleanup(dataMatrix, n_rows);

    return 0;
}
