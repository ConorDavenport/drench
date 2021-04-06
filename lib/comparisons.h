#include "node.h"

bool compLessThan(Node* a, Node* b) {
  return a->id < b->id;
}

bool compEquals(Node* a, Node* b) {
  return a->id == b->id;
}

bool compNumConnections(Node* a, Node* b) {
  return a->connections.size()> b->connections.size();
}

bool compId(Node* a, Node* b) {
  return a->id > b->id;
}

bool compColour(Node* a, Node* b) {
  return a->colour > b->colour;
}