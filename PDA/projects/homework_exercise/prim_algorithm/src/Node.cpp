// Taken from https://github.com/abangfarhan/graph-sfml/blob/master/src/Node.cpp

#include <vector>
#include <string>
#include <math.h>

#include "Node.h"

Node::Node() {
    setX(0);
    setY(0);
    setName("");
}

Node::Node(float x, float y, std::string name) {
    setX(x);
    setY(y);
    setName(name);
}

Node::Node(Node* node) {
    /* copy properties, except the neighbors */
    setX(node->x());
    setY(node->y());
    setName(node->name());
}

float Node::x() { 
      return _x; 
}

float Node::y() { 
      return _y; 
}

std::string Node::name() {
      return _name;
}

void Node::setX(float x) {
      _x = x;
}

void Node::setY(float y) {
      _y = y;
}

void Node::setName(std::string name) {
      _name = name;
}

void Node::addNeighbor(Node* node) {
     // Add neighbor node to this->_neighbors if not exist,
     // and add this to the neighbor node->_neighbors
     for (Node* neighbor: _neighbors)
         if (neighbor == node)
            return;
     _neighbors.push_back(node);
     node->addNeighbor(this);
}

std::vector<Node*> Node::neighbors() {
     return _neighbors;
}
         
float Node::distance(Node* neighbor) {
      return sqrt(pow(_x - neighbor->x(), 2) + pow(_y - neighbor->y(), 2));
}
