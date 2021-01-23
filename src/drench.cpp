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
  
    Node(int c, int id);
    void addConnection(Node* conn);
    void rmConnection(int id);
};

Node::Node(int c, int id) {
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
int** parseData(string fileName) {
  ifstream file;
  file.open(fileName);
  string field;

  int** grid = 0;
  grid = new int*[GRID];

  for (int h = 0; h < GRID; h++) {
    grid[h] = new int[GRID];
    for (int w = 0; w < GRID; w++) {
      getline(file, field, ','); // read char from example
      grid[h][w] = stoi(field);
    }
  }
  file.close();
  return grid;
}

void print(int** grid) {
  for (int i = 0; i < GRID; i++) {
    for (int j = 0; j < GRID; j++) {
      printf("%i", grid[i][j]);
    }
    printf("\n");
  }
}

void clean(int** grid) {
  for (int h = 0; h < GRID; h++) {
    delete [] grid[h];
  }
  delete [] grid;
  grid = 0;
}

void clean(Node* network) {
  delete [] network;
}

// generateNetwork() iterates through the grid
// and finds all adjacent cells that are the same
// colour and groups them together into one node
// per grouping
Node* generateNetwork(int** grid) {

}

int main(int argc, char* argv[]) {
  // load data from file into grid
  int** grid = parseData(argv[1]);
  clean(grid);
  //Node* network = generateNetwork(grid);

  return 0;
}