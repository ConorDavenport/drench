#include <algorithm>
#include <vector>
#include "colours.h"
#include "comparisons.h"
#include "defines.h"
#include "node.h"

void quickSolve(std::vector<Node*>& network) {
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
  std::sort(colours, colours + len, compColourStructFrequency);

  // choose next move as the most frequent colour
  int nextMoveColour = colours[0].colour;
  player->colour = nextMoveColour;
  printf("%i ", nextMoveColour);

  // select all adjacent nodes that colour is nextMoveColour
  // append their connections to player.connections
  std::vector<Node*> nextMovesVec;
  std::vector<Node*> newConnections;
  for(std::vector<Node*>::iterator i = player->connections.begin(); i != player->connections.end(); i++) {
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
  for(std::vector<Node*>::iterator i = network.begin(); i != network.end(); i++) {
    for(std::vector<Node*>::iterator j = nextMovesVec.begin(); j != nextMovesVec.end(); j++) {
      replace((*i)->connections.begin(), (*i)->connections.end(), *j, player);
    }
    sort((*i)->connections.begin(), (*i)->connections.end(), compId);
    (*i)->connections.erase(unique((*i)->connections.begin(), (*i)->connections.end()), (*i)->connections.end());
  }
  
  player->connections.erase(find(player->connections.begin(), player->connections.end(), player));

  // remove all adjacent nodes with colour nextMoveColour from network
  for(std::vector<Node*>::iterator i = nextMovesVec.begin(); i != nextMovesVec.end(); i++) {
    network.erase(remove(network.begin(), network.end(), *i), network.end());
  }

  quickSolve(network);
}