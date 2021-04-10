#include <algorithm>
#include <vector>
#include "comparisons.h"
#include "defines.h"
#include "node.h"

void _recursiveSolve(std::vector<Node*> network) {
  if (network.size() == 1) {
    return;
  }

  printf("%i\n",(int)network.size());
  Node* player = network[0];

  for (std::vector<Node*>::iterator i = player->connections.begin(); i != player->connections.end(); i++) {
    Node* nextMove = (*i);
    int nextMoveColour = nextMove->colour;

    std::vector<Node*> nextMovesVec;
    std::vector<Node*> newConnections;
    for(std::vector<Node*>::iterator i = player->connections.begin(); i != player->connections.end(); i++) {
      if((*i)->colour == nextMoveColour) {
        nextMovesVec.push_back(*i);
        newConnections.insert(newConnections.end(), (*i)->connections.begin(), (*i)->connections.end());
      }
    }

    player->connections.insert(player->connections.end(), newConnections.begin(), newConnections.end());
    std::sort(player->connections.begin(), player->connections.end(), compId);
    player->connections.erase(unique(player->connections.begin(), player->connections.end()), player->connections.end());

    for(std::vector<Node*>::iterator i = network.begin(); i != network.end(); i++) {
      for(std::vector<Node*>::iterator j = nextMovesVec.begin(); j != nextMovesVec.end(); j++) {
        replace((*i)->connections.begin(), (*i)->connections.end(), *j, player);
      }
      sort((*i)->connections.begin(), (*i)->connections.end(), compId);
      (*i)->connections.erase(unique((*i)->connections.begin(), (*i)->connections.end()), (*i)->connections.end());
    }

    std::vector<Node*>::iterator playerRef = find(player->connections.begin(), player->connections.end(), player);
    if (playerRef != player->connections.end()) {
      player->connections.erase(playerRef);
    }

    for(std::vector<Node*>::iterator i = nextMovesVec.begin(); i != nextMovesVec.end(); i++) {
      network.erase(remove(network.begin(), network.end(), *i), network.end());
    }
     _recursiveSolve(network);
  }
  return;
}

void recursiveSolve(std::vector<Node*>& network) {
  _recursiveSolve(network);
}