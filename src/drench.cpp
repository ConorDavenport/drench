#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include "../lib/node.h"
#include "../lib/comparisons.h"
#include "../lib/colours.h"

using namespace std;

#define GRID 14
#define NUM_COLOURS 6
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
      printf("%i", grid[i][j].parent->id);
    }
    printf("\n");
  }
}

void print(vector<Node> vec) {
  for (vector<Node>::iterator i = vec.begin(); i != vec.end(); i++) {
    printf("%i: %i", (*i).id, (*i).connections.size());
    printf("\n");
  }
}

void print(vector<Node*> vec) {
  for (vector<Node*>::iterator i = vec.begin(); i != vec.end(); i++) {
    printf("%i (%i): [%i] ", (*i)->id, (*i)->colour, (*i)->connections.size());
    for (vector<Node*>::iterator j = (*i)->connections.begin(); j != (*i)->connections.end(); j++) {
      printf("%i, ", (*j)->id);
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

void group(int i, int j, Node** grid, Node* parent) {
  // at first call n = parent
  Node* n = &grid[i][j];
  n->parent = parent;
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

  for (int k = 0; k < 4; k++) {
    if (adjacent[k].n->colour == n->colour && adjacent[k].n->grouped == false) {
      n->parent = parent;
      group(adjacent[k].i, adjacent[k].j, grid, parent);
    }
  }
}

void establishConnections(int i, int j, Node** grid) {
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
  
  for (int k = 0; k < 4; k++) {
    if (adjacent[k].n->colour != n->colour && adjacent[k].n->colour != 200) {
      n->parent->connections.push_back(adjacent[k].n->parent);
    }
  }
}

// generateNetwork() iterates through the grid
// and finds all adjacent cells that are the same
// colour and groups them together into one node
// per grouping
vector<Node*> generateNetwork(Node** grid) {
  vector<Node*> network;

  for (int i = 0; i < GRID; ++i) {
    for (int j = 0; j < GRID; ++j) {
      if (!grid[i][j].grouped) {
        grid[i][j].isParent = true;
        network.push_back(&grid[i][j]);
        group(i, j, grid, &grid[i][j]);
      }
    }
  }
  for (int i = 0; i < GRID; ++i) {
    for (int j = 0; j < GRID; ++j) {
      establishConnections(i, j, grid);
    }
  }
  for (vector<Node*>::iterator i = network.begin(); i != network.end(); i++) {
    sort((*i)->connections.begin(), (*i)->connections.end(), compLessThan);
    (*i)->connections.erase(unique((*i)->connections.begin(), (*i)->connections.end(), compEquals), (*i)->connections.end());
  }
  return network;
}

void solve(vector<Node*>& network) {
  if(network.size() == 1) {
    return;
  }
  // start in top right of grid
  // change colour of player to that of the connection with most connections
  // add nextMove's connections to player's connections vector
  Node* player = network[0];
  sort(player->connections.begin(), player->connections.end(), compNumConnections);
  Node* nextMove = player->connections[0];
  player->colour = nextMove->colour;
  printf("%i ", nextMove->colour);
  player->connections.insert(player->connections.end(), nextMove->connections.begin(), nextMove->connections.end());
  
  // update all nodes in network to point connect to player instead of nextMove
  for (vector<Node*>::iterator i = network.begin(); i != network.end(); i++) {
    replace((*i)->connections.begin(), (*i)->connections.end(), nextMove, player);
    sort((*i)->connections.begin(), (*i)->connections.end(), compId);
    (*i)->connections.erase(unique((*i)->connections.begin(), (*i)->connections.end()), (*i)->connections.end());
  }

  // clean player connections vector
  player->connections.erase(find(player->connections.begin(), player->connections.end(), player));

  network.erase(remove(network.begin(), network.end(), nextMove), network.end());

  solve(network);
}

void quickSolve(vector<Node*>& network) {
  if(network.size() == 1) {
    return;
  }
  
  Node* player = network[0];

  colour colours[NUM_COLOURS];

  // sort player connections by frequency of colour
  for (int i = 0; i < NUM_COLOURS; i++) {
    colours[i].colour = i;
    colours[i].frequency = count_if(player->connections.begin(), player->connections.end(), [i](const Node* n){return n->colour == i;});
  }

  int len = sizeof(colours) / sizeof(colours[0]);
  sort(colours, colours + len, compColourStructFrequency);

  // choose next move as the most frequent colour
  int nextMoveColour = colours[0].colour;
  player->colour = nextMoveColour;
  printf("%i ", nextMoveColour);

  // select all adjacent nodes that colour is nextMoveColour
  // append their connections to player.connections
  vector<Node*> nextMovesVec;
  vector<Node*> newConnections;
  for(vector<Node*>::iterator i = player->connections.begin(); i != player->connections.end(); i++) {
    if((*i)->colour == nextMoveColour) {
      nextMovesVec.push_back(*i);
      newConnections.insert(newConnections.end(), (*i)->connections.begin(), (*i)->connections.end());
    }
  }
  // remove duplicates and references to player in player.connections
  player->connections.insert(player->connections.end(), newConnections.begin(), newConnections.end());
  sort(player->connections.begin(), player->connections.end(), compId);
  player->connections.erase(unique(player->connections.begin(), player->connections.end()), player->connections.end());
  player->connections.erase(remove(player->connections.begin(), player->connections.end(), player), player->connections.end());

  // update all nodes that point to any node in nextMovesVec to point to player
  for(vector<Node*>::iterator i = network.begin(); i != network.end(); i++) {
    for(vector<Node*>::iterator j = nextMovesVec.begin(); j != nextMovesVec.end(); j++) {
      replace((*i)->connections.begin(), (*i)->connections.end(), *j, player);
    }
    sort((*i)->connections.begin(), (*i)->connections.end(), compId);
    (*i)->connections.erase(unique((*i)->connections.begin(), (*i)->connections.end()), (*i)->connections.end());
  }
  
  player->connections.erase(find(player->connections.begin(), player->connections.end(), player));

  // remove all adjacent nodes with colour nextMoveColour from network
  for(vector<Node*>::iterator i = nextMovesVec.begin(); i != nextMovesVec.end(); i++) {
    network.erase(remove(network.begin(), network.end(), *i), network.end());
  }
  
  quickSolve(network);
}

int main(int argc, char* argv[]) {
  // load data from file into grid
  Node** grid = parseData(argv[1]);
  vector<Node*> network = generateNetwork(grid);
  print(network);
  quickSolve(network);
  clean(grid);

  return 0;
}