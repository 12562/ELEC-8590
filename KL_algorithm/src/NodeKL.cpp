#include <vector>
#include <string>
#include <utility>
#include <iostream>
#include <iterator>

#include "Node.h"
#include "NodeKL.h"

float NodeKL::getDvalue() {
      return _Dvalue;
}

void NodeKL::setDvalue(float D) {
     _Dvalue = D;
}


std::vector<std::pair<NodeKL*, float>> NodeKL::neighbors() {
     return _neighbors;
     //std::vector<NodeKL*> neighbors_; 
     //for ( std::vector<std::pair<NodeKL*, float>>::iterator it = _neighbors.begin(); it != _neighbors.end(); ++it) {
     //  neighbors_.push_back(it->first);
       //std::cout << "\n" << this->name() << " Current nodes neighbors: " << neighbor.first->name() << " ";
     //}
     //std::cout << std::endl;
     //return neighbors_;
}


void NodeKL::addNeighbor(NodeKL* node, float distance, bool distance_update) {
     //std::cout << " Current node: " << this->name() << std::endl;
     //std::cout << "Neighbor to add: " << node->name() << std::endl;
     //std::cout << "Neighbor to add distance is: " << distance << std::endl;
     for ( std::vector<std::pair<NodeKL*, float>>::iterator it = _neighbors.begin(); it != _neighbors.end(); ++it) {
         //std::cout << "Already neighbor: " << it->first->name() << std::endl;
         //std::cout << "Already neighbor distance: " << it->second << std::endl;
         if (it->first->name() == node->name() ) {
            if ( distance_update ) {
               it->second += distance;
               node->update_distance(this, distance);
            }
            /*for ( std::pair<NodeKL*, float> &neighbor: node->neighbors()) {
               if (neighbor.first->name() == this->name() ) {
                  neighbor.second +=distance;
               }
            }*/
            return;
         }
     }
     //std::cout << "check\n";
     _neighbors.push_back(std::make_pair(node,distance));
     node->addNeighbor(this,distance,false);
}
   
void NodeKL::update_distance (NodeKL* node, float distance) {
     for ( std::pair<NodeKL*, float> &neighbor: _neighbors)
         if (neighbor.first == node)
            neighbor.second += distance;
}

int NodeKL::getGroup() {
     return _Group;
}

void NodeKL::setGroup(int g) {
    _Group = g; 
}

float NodeKL::is_node2_connected(NodeKL node2) {
    for (std::pair<NodeKL*,float> &neighbor: _neighbors) {
          if (neighbor.first->name() == node2.name()  ) {
             return neighbor.second;
          }
    }
    return 0.0;
}
