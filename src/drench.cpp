#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

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

  
  return 0;
}