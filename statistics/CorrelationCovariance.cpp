#include <iostream>

using namespace std; 


/** This function print the values in the data Matrix 
 * @param DataMatrix  a 2D array
 * @param N_REGIONS num
*/

void printData(double** DataMatrix, int N_REGIONS, int M_WINES);

void getRow(double** DataMatrix, int M_WINES, int row_index, double row[]);

void getColumn(double** DataMatrix, int N_REGIONS, int column_index, double column[]);


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

    // testing getRow function 
    double row[m_cols];

    getRow(dataMatrix, m_cols, 1, row);

    cout << row[0] << endl;



    // delete pointer 
    
    for(int i=0; i<n_rows; i++)
        delete []dataMatrix[i];
    delete []dataMatrix;
    

    return 0;
}

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
    cout << endl;
}