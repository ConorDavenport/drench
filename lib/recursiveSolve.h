#include <algorithm>
#include <vector>
#include "comparisons.h"
#include "defines.h"
#include "node.h"

void _recursiveSolve(std::vector<Node*> network, std::vector<int>& moves) {
  if(network.size() == 1) {
    printf("here\n");
    // for (std::vector<int>::iterator i = moves.begin(); i != moves.end(); i++) {
    //   printf("%i ", (*i));
    // }
    // printf("\n");
    moves.pop_back();
    return;
  }

  Node* player = network[0];
  printf("%i ", network.size());
  // iterate through player connections
  for (std::vector<Node*>::iterator i = player->connections.begin(); i != player->connections.end(); i++) {
    Node* nextMove = (*i);
    player->colour = nextMove->colour;
    moves.push_back(nextMove->colour);
    
    // select all adjacent nodes that colour is nextMove's colour
    // append their connections to player's connection vector
    std::vector<Node*> nextMovesVec;
    std::vector<Node*> newConnections;
    for(std::vector<Node*>::iterator j = player->connections.begin(); j != player->connections.end(); j++) {
      if((*j)->colour == nextMove->colour) {
        nextMovesVec.push_back(*i);
        newConnections.insert(newConnections.end(), (*i)->connections.begin(), (*i)->connections.end());
      }
    }
    // remove duplicates and references to player in player.connections
    player->connections.insert(player->connections.end(), newConnections.begin(), newConnections.end());
    std::sort(player->connections.begin(), player->connections.end(), compId);
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

    _recursiveSolve(network, moves);
    printf("finished\n");
  }
}

void recursiveSolve(std::vector<Node*> network) {
  std::vector<int> moves;
  _recursiveSolve(network, moves);
}