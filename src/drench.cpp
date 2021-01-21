#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

#define GRID 14

class Node {
  public:
    // 0 green
    // 1 pink
    // 2 purple
    // 3 white
    // 4 red
    // 5 yellow
    int colour;
    // uuid
    int id;
    // connections to other tiles
    vector<Node*> connections;
};

// get drench example game
// load game into grid, 1d vector
void parseData(string fileName, vector<int>& grid) {
  ifstream file;
  file.open(fileName);
  string field;

  for (int i = 0; i < 81; i++) {
    getline(file, field, ','); // read char from example
    grid.push_back(stoi(field));  // string to int
  }
  file.close();
}

int main(int argc, char* argv[]) {
  // init memory for grid
  vector<int> grid;

  // load data from file into grid
  parseData(argv[1], grid);

  return 0;
}