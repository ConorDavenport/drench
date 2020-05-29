#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

#define GRID_SIZE 14

class Node {
  private:
    // 0 green
    // 1 pink
    // 2 purple
    // 3 white
    // 4 red
    // 5 yellow
    int colour;
    // number of tiles in that block
    int volume;
    // uuid
    int id;
    // connections to other tiles
    vector<Node*> connections;

  public:
};

int rng() {
  return rand() % 6 + 0;
}

int main() {
  // init random number generation
  srand(time(NULL));

  // represents the grid of tiles
  int grid[GRID_SIZE][GRID_SIZE] = {};

  // fill grid with random numbers (colours)
  for (int i = 0; i < GRID_SIZE; i++) {
    for (int j = 0; j < GRID_SIZE; j++) {
      grid[i][j] = rng();
      cout << grid[i][j];
    }
    cout << endl;
  }
  
  // create vector of nodes that represents groups of adjacent
  // tiles of the same colour
  vector<Node> grid;
  
  return 0;
}