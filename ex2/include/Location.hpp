#include <stdio.h>

struct Location
{
public:
    int getRow();
    int getCol();
    Location(int row, int col) : m_row(row), m_col(col) {}
    
    
private:
    int m_col; // x
    int m_row; // y
    
};
