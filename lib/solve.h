#include <algorithm>
#include <vector>
#include "comparisons.h"
#include "node.h"

void solve(std::vector<Node*>& network) {
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
  for (std::vector<Node*>::iterator i = network.begin(); i != network.end(); i++) {
    replace((*i)->connections.begin(), (*i)->connections.end(), nextMove, player);
    sort((*i)->connections.begin(), (*i)->connections.end(), compId);
    (*i)->connections.erase(unique((*i)->connections.begin(), (*i)->connections.end()), (*i)->connections.end());
  }

  // clean player connections vector
  player->connections.erase(find(player->connections.begin(), player->connections.end(), player));

  network.erase(remove(network.begin(), network.end(), nextMove), network.end());

  solve(network);
}
