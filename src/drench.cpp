#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

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
    Node(bool g, int c, int id);
};

Node::Node(int c, int id) {
  grouped = false;
  colour = c;
  id = id;
}

Node::Node(bool g, int c, int id) {
  grouped = g;
  colour = c;
  id = id;
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

vector<Node*> group(int i, int j, Node** grid) {
  Node* n = &grid[i][j];

  Node n_null(true, 200,200);

  // create a structure of containing the four adjacent
  // elements in the 2d array grid
  struct Adjacent {
    Node *n;
    int i;
    int j;

    Adjacent(Node node, int loc_i, int loc_j) {
      n = &node;
      i = loc_i;
      j = loc_j;
    }
  } up(n_null, i-1, j),
  down(n_null, i+1, j),
  left(n_null, i, j-1),
  right(n_null, i, j+1);

  Adjacent adjacent[4] = {
    up, down, left, right
  };
  
  // out of bounds check
  if (i != 0) {
    adjacent[0] = Adjacent(grid[i-1][j], adjacent[0].i, adjacent[0].j);
  } 
  if (i != (GRID - 1)) {
    adjacent[1] = Adjacent(grid[i+1][j], adjacent[1].i, adjacent[1].j);
  } 
  if (j != 0) {
    adjacent[2] = Adjacent(grid[i][j-1], adjacent[2].i, adjacent[2].j);
  } 
  if (j != (GRID - 1)) {
    adjacent[3] = Adjacent(grid[i][j+1], adjacent[3].i, adjacent[3].j);
  }
  
  n->grouped = true;

  // iterate through the adjacent cells
  // if cell k is the same colour, and it's not grouped yet
  // call the group function and pass k
  // don't call on grouped cells to avoid loops
  for (int k = 0; k < 4; k++) {
    if (adjacent[k].n->colour == n->colour && adjacent[k].n->grouped == false) {
      n->connections.push_back(adjacent[k].n);
      vector<Node*> newConnections = group(adjacent[k].i, adjacent[k].j, grid);
      n->connections.insert(end(n->connections), begin(newConnections), end(newConnections));
      sort(n->connections.begin(), n->connections.end());
      n->connections.erase(unique(n->connections.begin(), n->connections.end()), n->connections.end());
    } 
  }
  return n->connections;
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
      if (!grid[i][j].grouped) {
        grid[i][j].connections = group(i, j, grid);
        network.push_back(grid[i][j]);
      }
    }
  }

  return network;
}

int main(int argc, char* argv[]) {
  // load data from file into grid
  Node** grid = parseData(argv[1]);
  vector<Node> network = generateNetwork(grid);
  clean(grid);

  return 0;
}