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

// generateNetwork() iterates through the grid
// and finds all adjacent cells that are the same
// colour and groups them together into one node
// per grouping
Node* generateNetwork(vector<int>& grid) {

}

int main(int argc, char* argv[]) {
  // init memory for grid
  vector<int> grid;

  // load data from file into grid
  parseData(argv[1], grid);

  Node* network = generateNetwork(grid);

  return 0;
}