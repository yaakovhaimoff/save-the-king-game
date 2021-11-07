#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <vector>

// include src files
#include "Controller.hpp"
#include "Board.hpp"

//---------------using section---------------

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::setw;
using std::string;
using std::vector;

int main()
{
    Controller player;
    player.runGame();

return 0;
}
