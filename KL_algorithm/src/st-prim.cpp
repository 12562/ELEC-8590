// Taken from https://github.com/abangfarhan/graph-sfml/blob/master/src/st-prim.cpp
#include <iostream>
#include <sstream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Node.h"
#include "NodeDjikstra.h"
#include "graphHelper.h"

int main(int argc, char* argv[]) {
    int gridWidth = 20;
    int gridHeight = 10;
    if (argc == 3) {
       std::stringstream ss;
       ss << argv[1];
       ss >> gridWidth;
       ss << argv[2];
       ss >> gridHeight;
    }
    const int n_nodes = gridWidth * gridHeight;
    const int space = 50;
    const int screenWidth = gridWidth * space;
    const int screenHeight = gridHeight * space;
    NodeDj* nodeList[n_nodes];
    fillGraphGrid<NodeDj>(nodeList, space, gridWidth, gridHeight);
    std::vector<NodeDj*> visitedNodes;
    
    bool is_solving = true;
    NodeDj* start = nodeList[gridWidth/2 + (gridHeight/2) * gridWidth];
    start->setVisited(true);
    visitedNodes.push_back(start);
    
    const int radius = 3;
    sf::CircleShape nodeMarkers[n_nodes];
    for (int i = 0; i < n_nodes; ++i) {
      sf::CircleShape marker;
      marker.setPosition(nodeList[i]->x() - radius, nodeList[i]->y() - radius);
      marker.setRadius(radius);
      marker.setFillColor(sf::Color::Black);
      if (nodeList[i] == start) 
         marker.setFillColor(sf::Color::Blue);
      nodeMarkers[i] = marker;
    }  
    
    sf::ContextSettings settings;
    settings.antialiasingLevel = 5;
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Prim's Algorithm", sf::Style::Default, settings);
    while ( window.isOpen()) { 
      sf::Event event;
      while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
           window.close();
        }
      }
      
      window.clear(sf::Color::White);

      // line connecting all nodes
      for (int i = 0; i < n_nodes; ++i) {
        for (NodeDj* neighbor: nodeList[i]->neighbors()) {
          sf::RectangleShape line = Line(nodeList[i]->x(), nodeList[i]->y(), neighbor->x(), neighbor->y());
          line.setFillColor(sf::Color(220,220,220));
          window.draw(line);
        }
      } 
      
      for (int i = 0;i < n_nodes; ++i) {
        if (nodeList[i]->prev() != NULL) {
          NodeDj* prev = nodeList[i]->prev();
          sf::RectangleShape line = Line(nodeList[i]->x(), nodeList[i]->y(), prev->x(), prev->y(), 2);
          line.setFillColor(sf::Color::Black);
          window.draw(line);
        }
      }
       
      if ( is_solving ) {
         NodeDj* chosenNode = NULL;
         NodeDj* closestNeighbor = NULL;
         for (NodeDj* node: visitedNodes) {
           for (NodeDj* neighbor: node->neighbors()) {
             if (neighbor->visited())
               continue;
             if (chosenNode == NULL || closestNeighbor == NULL || node->distance(neighbor) < chosenNode->distance(closestNeighbor)) {
               chosenNode = node;
               closestNeighbor = neighbor;
             }
           }
         }
         if (chosenNode != NULL && closestNeighbor != NULL ) { 
            closestNeighbor->setVisited(true);
            closestNeighbor->setPrev(chosenNode);
            visitedNodes.push_back(closestNeighbor);
         } else {
            is_solving = false;
            std::cout << "Some nodes are not reachable" << std::endl; 
         }
      }
      
      for ( int i = 0; i < n_nodes; ++i)
          window.draw(nodeMarkers[i]);
      
      window.display();
      sf::sleep(sf::milliseconds(1000));
    }
}
