#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <time.h>

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
    // number of tiles in that block
    int volume;
    // uuid
    int id;
    // connections to other tiles
    vector<Node*> connections;
};

int rng() {
  return rand() % 6 + 0;
}

class Grid {
  public:
    Node grid[GRID][GRID] = {};
    vector<Node> network = {};

    Grid();
};

Grid::Grid() {
  for (int i = 0; i < GRID; i ++) {
    for (int j = 0; j < GRID; j++) {
      grid[i][j].id = ((i * GRID) + j);
      grid[i][j].colour = rng();
    }
  }
}

int main() {
  // init random number generation
  srand(time(NULL));

  Grid g();
  
  return 0;
}