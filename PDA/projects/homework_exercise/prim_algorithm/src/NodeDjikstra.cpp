// Taken from https://github.com/abangfarhan/graph-sfml/blob/master/src/NodeDjikstra.cpp

#include <vector>
#include <string>

#include "Node.h"
#include "NodeDjikstra.h"

float NodeDj::tnDist () {
      return _tnDist;
}

void NodeDj::setTnDist(float newTnDist) {
     _tnDist = newTnDist;
}

bool NodeDj::visited() {
     return _visited;
}

void NodeDj::setVisited(bool newVisited) {
     _visited = newVisited;
}

NodeDj* NodeDj::prev() {
     return _prev;
}

void NodeDj::setPrev(NodeDj* newPrev) {
     _prev = newPrev;
}

std::vector<NodeDj*> NodeDj::neighbors() {
     return _neighbors;
}

void NodeDj::addNeighbor(NodeDj* node) {
     for (NodeDj* neighbor: _neighbors) 
         if (neighbor == node)
            return;
     _neighbors.push_back(node);
     node->addNeighbor(this);
}
