#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <time.h>
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
    // represents game board
    Node grid[GRID][GRID] = {};
    // represents game board condensed so that each block of tiles with the same
    // colour are represented as a single node in the network
    vector<Node> network = {};

    Grid();
    void print();
    void search();
};

Grid::Grid() {
  ifstream file;
  file.open("../examples/1.csv");
  string field;
  
  // get colours from file and assign each element in grid array the
  // corresponding colour
  for (int i = 0; i < GRID; i ++) {
    for (int j = 0; j < GRID; j++) {
      grid[i][j].id = ((i * GRID) + j);
      getline(file, field, ',');
      grid[i][j].colour = (stoi(field), true);
    }
  }
  file.close();
}

void Grid::print() {
  for (int i = 0; i < GRID; i ++) {
    for (int j = 0; j < GRID; j++) {
      cout << grid[i][j].colour << " ";
    }
    cout << endl;
  }
}

void Grid::search() {
  // for each element of grid get the four adjacent elements
  // if the adjacent element is the same colour, add it to siblings else add to
  // connections
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
      
      adjacent[0] = &grid[i][j-1];
      adjacent[1] = &grid[i-1][j];
      adjacent[2] = &grid[i][j+1];
      adjacent[3] = &grid[i+1][j];

      Node n;
      n.colour = 200;
      n.id = 200;
      Node* ptr;
      ptr = &n;

      // out of bounds checking
      if (i == 0) {
        adjacent[1] = ptr;
      } if (i == (GRID - 1)) {
        adjacent[3] = ptr;
      } if (j == 0) {
        adjacent[0] = ptr;
      } if (j == (GRID - 1)) {
        adjacent[2] = ptr;
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
  return 0;
}