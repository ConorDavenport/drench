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
    // pointers to other tiles in that block
    vector<Node*> siblings;
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
    void print();
    void search();
};

Grid::Grid() {
  for (int i = 0; i < GRID; i ++) {
    for (int j = 0; j < GRID; j++) {
      grid[i][j].id = ((i * GRID) + j);
      grid[i][j].colour = rng();
    }
  }
}

void Grid::print() {
  for (int i = 0; i < GRID; i ++) {
    for (int j = 0; j < GRID; j++) {
      cout << grid[i][j].id << " ";
    }
    cout << endl;
  }
}

void Grid::search() {
  for (int i = 0; i < GRID; i ++) {
    for (int j = 0; j < GRID; j++) {
      Node* thisNode = &grid[i][j];

      //      ┌───┐	  
      //      │ 1 │
      //  ┌───┼───┼───┐
      //  │ 0 │ x │ 2 │
      //  └───┼───┼───┘
      //      │ 3 │
      //      └───┘ 	

      Node* adjacent[4];
      
      adjacent[0] = &grid[i-1][j];
      adjacent[1] = &grid[i][j-1];
      adjacent[2] = &grid[i+1][j];
      adjacent[3] = &grid[i][j+1];

      Node n;
      n.colour = 6;
      n.id = 200;
      Node* ptr;
      ptr = &n;

      if (i == 0) {
        adjacent[0] = ptr;
      } if (i == (GRID - 1)) {
        adjacent[2] = ptr;
      } if (j == 0) {
        adjacent[1] = ptr;
      } if (j == (GRID - 1)) {
        adjacent[3] = ptr;
      }

      for (int k = 0; k < 4; k++) {
        if (thisNode->colour == adjacent[k]->colour) {
          thisNode->siblings.push_back(adjacent[k]);
        } else if ((thisNode->colour != adjacent[k]->colour) && (adjacent[k]->id != 200)) {
          thisNode->connections.push_back(adjacent[k]);
        }
      }
    }
  }
}

int main() {
  // init random number generation
  srand(time(NULL));

  Grid g;
  g.search();
  //g.print();
  return 0;
}