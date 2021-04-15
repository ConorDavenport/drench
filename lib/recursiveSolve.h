#include <algorithm>
#include <vector>
#include "comparisons.h"
#include "defines.h"
#include "node.h"

void _recursiveSolve(std::vector<std::vector<Node*>> stack) {
  std::vector<Node*> currentState = stack.back();
  if (currentState.size() == 1) {
    return;
  }

  Node* player = currentState[0];

  for(std::vector<Node*>::iterator i = player->connections.begin(); i != player->connections.end(); i++) {
    Node* nextMove = (*i);
    int nextMoveColour = nextMove->colour;
    printf("%i\n", nextMoveColour);
    nextMove->colour = nextMoveColour;
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
    for(std::vector<Node*>::iterator i = currentState.begin(); i != currentState.end(); i++) {
      for(std::vector<Node*>::iterator j = nextMovesVec.begin(); j != nextMovesVec.end(); j++) {
        replace((*i)->connections.begin(), (*i)->connections.end(), *j, player);
      }
      sort((*i)->connections.begin(), (*i)->connections.end(), compId);
      (*i)->connections.erase(unique((*i)->connections.begin(), (*i)->connections.end()), (*i)->connections.end());
    }
    
    player->connections.erase(find(player->connections.begin(), player->connections.end(), player));
    stack.push_back(currentState);
    _recursiveSolve(stack);
    stack.pop_back();
  }
}

void recursiveSolve(std::vector<Node*> network) {
  std::vector<std::vector<Node*>> stack;
  stack.push_back(network);
  _recursiveSolve(stack);
  printf("exit\n");
}