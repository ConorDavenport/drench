#ifndef NODE_H
#define NODE_H

#include <vector>

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
    // tracks whether node has been grouped
    bool grouped;
    // connections to other tiles
    std::vector<Node*> connections;
    // parent node of same-colour group
    Node* parent;
    bool isParent;
    Node() { grouped = false; isParent = false; };
    Node(int c, int id);
    Node(bool g, int c, int id);
    bool operator== (const Node* other ) const { return id == other->id; };
};
#endif