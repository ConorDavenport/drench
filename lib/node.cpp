#include "node.h"
#include <vector>

Node::Node(int c, int id) {
  grouped = false;
  isParent = false;
  colour = c;
  id = id;
}

Node::Node(bool g, int c, int id) {
  isParent = false;
  grouped = g;
  colour = c;
  id = id;
}