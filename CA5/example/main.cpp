#include "TankTrouble.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;


int main(int argc, char **argv) {
  if (argc != 2)
    cout << "Enter the filename" << endl;
  TankTrouble tt(argv[1]);
  tt.run();
  return 0;
}
