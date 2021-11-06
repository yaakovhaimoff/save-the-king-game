#include <stdio.h>

struct Location
{
public:
    int getCol();
    int getRow();
    Location(int col, int row) : m_col(col), m_row(row) {}
    
    
private:
    int m_col = 0; // x
    int m_row = 0; // y
    
};
