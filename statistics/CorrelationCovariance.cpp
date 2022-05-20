#include "statistics.h"
#include <iostream>

using namespace std; 



int main()
{
    double** dataMatrix;
    int n_rows, m_cols;
    cout << "Enter the number of rows" << endl;
    cin >> n_rows;
    dataMatrix = new double*[n_rows];
    cout << "Enter the number of columns" << endl;
    cin >> m_cols;

    cout << "Enter elements of a matrix with " << n_rows << " rows and " 
                                               << m_cols << " columns\n";

    cout << "#####################" << endl;

    for (int i=0; i<n_rows; i++)
    {
        dataMatrix[i] = new double[m_cols];
        for(int j=0; j<m_cols; j++)
        {
            cin >> dataMatrix[i][j];
        }
    }

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

    // delete pointer 
    
    for(int i=0; i<n_rows; i++)
        delete []dataMatrix[i];
    delete []dataMatrix;
    

    return 0;
}
