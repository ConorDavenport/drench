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
    // tracks whether node has been grouped
    bool grouped;
    // connections to other tiles
    vector<Node*> connections;
  
    Node() { grouped = false; };
    Node(int c, int id);
    void addConnection(Node* conn);
    void rmConnection(int id);
};

Node::Node(int c, int id) {
  grouped = false;
  colour = c;
  id = id;
}

void Node::addConnection(Node* conn) {
  connections.push_back(conn);
}

void Node::rmConnection(int id) {
  
}

// get drench example game
// load game into grid, return 2d array
Node** parseData(string fileName) {
  ifstream file;
  file.open(fileName);
  string field;

  Node** grid = 0;
  grid = new Node*[GRID];

  int id = 0;

  for (int h = 0; h < GRID; h++) {
    grid[h] = new Node[GRID];
    for (int w = 0; w < GRID; w++) {
      getline(file, field, ','); // read char from example
      grid[h][w].colour = stoi(field);
      grid[h][w].id = id;
      ++id;
    }
  }
  file.close();
  return grid;
}

void print(Node** grid) {
  for (int i = 0; i < GRID; i++) {
    for (int j = 0; j < GRID; j++) {
      printf("%i", grid[i][j].colour);
    }
    printf("\n");
  }
}

void clean(Node** grid) {
  for (int h = 0; h < GRID; h++) {
    delete [] grid[h];
  }
  delete [] grid;
  grid = 0;
}

// generateNetwork() iterates through the grid
// and finds all adjacent cells that are the same
// colour and groups them together into one node
// per grouping
// when this works I can probably put this into
// the parseData function
vector<Node> generateNetwork(Node** grid) {
  vector<Node> network;

  for (int i = 0; i < GRID; ++i) {
    for (int j = 0; j < GRID; ++j) {
      Node* n = &grid[i][j];

      Node* n_up = &grid[i-1][j];
      Node* n_down = &grid[i+1][j];
      Node* n_right = &grid[i][j-1];
      Node* n_left = &grid[i][j+1];

      // out of bounds check
      Node n_null(200,200);

      if (i == 0) {
        n_up = &n_null;
      } if (i == (GRID - 1)) {
        n_down = &n_null;
      } if (j == 0) {
        n_right = &n_null;
      } if (j == (GRID - 1)) {
        n_left = &n_null;
      }
    }
  }
}

int main(int argc, char* argv[]) {
  // load data from file into grid
  Node** grid = parseData(argv[1]);
  vector<Node> network = generateNetwork(grid);
  clean(grid);

  return 0;
}