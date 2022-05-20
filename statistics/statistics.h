#ifndef STATISTICS
#define STATISTICS

/** This function print the values in the data Matrix 
 * @param DataMatrix  a 2D array
 * @param N_REGIONS num
*/
void printData(double** DataMatrix, int N_REGIONS, int M_WINES);

void getRow(double** DataMatrix, int M_WINES, int row_index, double row[]);

void getColumn(double** DataMatrix, int N_REGIONS, int column_index, double column[]);



#endif 