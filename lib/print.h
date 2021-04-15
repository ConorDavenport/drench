#ifndef PRINT_H
#define PRINT_H

#include "defines.h"
#include "node.h"
#include <vector>

void print(Node** grid) {
  for (int i = 0; i < GRID; i++) {
    for (int j = 0; j < GRID; j++) {
      printf("%i", grid[i][j].parent->id);
    }
    printf("\n");
  }
}

void print(std::vector<Node> vec) {
  for (std::vector<Node>::iterator i = vec.begin(); i != vec.end(); i++) {
    printf("%i: %i", (*i).id, (int)(*i).connections.size());
    printf("\n");
  }
}

void print(std::vector<Node*> vec) {
  for (std::vector<Node*>::iterator i = vec.begin(); i != vec.end(); i++) {
    printf("%i (%i): [%i] ", (*i)->id, (*i)->colour, (int)(*i)->connections.size());
    for (std::vector<Node*>::iterator j = (*i)->connections.begin(); j != (*i)->connections.end(); j++) {
      printf("%i, ", (*j)->id);
    }
    printf("\n");
  }
}


#endif