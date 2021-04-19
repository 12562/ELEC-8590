#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

#include "Node.h"
#include "NodeDjikstra.h"
#include "graphHelper.h"

int main(int argc, char* argv[]) {
    bool complete_traversal = true;
    int gridWidth = 20;
    int gridHeight = 10;
    if (argc == 3) {
       std::stringstream ss;
       ss << argv[1];
       ss >> gridWidth;
       ss << argv[2];
       ss >> gridHeight;
    }
    const int space = 50;
    const int screenWidth = gridWidth * space;
    const int screenHeight = gridHeight * space;
    const int n_nodes = gridWidth * gridHeight;
    
    NodeDj* nodeList[n_nodes];
    fillGraphGrid<NodeDj>(nodeList, space, gridWidth, gridHeight);
     
    bool is_solving = true;
    NodeDj* start = nodeList[0];
    NodeDj* dest = nodeList[n_nodes - 1];
    NodeDj* current = start;
    start->setTnDist(0);
      
    // mark beginning and ending node
    const int radius = 3;
    sf::CircleShape nodeMarkers[n_nodes];
    for (int i = 0; i < n_nodes; ++i) {
        sf::CircleShape marker;
        marker.setPosition(nodeList[i]->x() - radius, nodeList[i]->y() - radius);
        marker.setRadius(radius);
        marker.setFillColor(sf::Color::Black);
        if (nodeList[i] == start)
           marker.setFillColor(sf::Color::Blue);
        else if (nodeList[i] == dest)
           marker.setFillColor(sf::Color::Red);
        nodeMarkers[i] = marker;
    }
 
    sf::ContextSettings settings;
    settings.antialiasingLevel = 5;
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Djikstra", sf::Style::Default, settings);
    while (window.isOpen()) {
      sf::Event event;
      while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
           window.close();
        }
      }

      window.clear(sf::Color::White);
      
      //line connecting all nodes
      for (int i = 0;i < n_nodes; ++i) {
        for (NodeDj* neighbor: nodeList[i]->neighbors()) {
          sf::RectangleShape line = Line(nodeList[i]->x(), nodeList[i]->y(), neighbor->x(), neighbor->y());          
          line.setFillColor(sf::Color(220,220,220));
          window.draw(line);
        }    
      }
      
      // Line connecting visited nodes
      // Why separate loop with the above? To avoid lines overlapping
      for (int i = 0;i < n_nodes; ++i) {
        if (nodeList[i]->prev() != NULL) {
          NodeDj* prev = nodeList[i]->prev();
          sf::RectangleShape line = Line(nodeList[i]->x(), nodeList[i]->y(), prev->x(), prev->y(), 2);
          line.setFillColor(sf::Color::Black);
          window.draw(line);
        }
      }
      
      if (is_solving) {
         for (NodeDj* neighbor: current->neighbors()) {
           if (neighbor->visited()) 
              continue;
           float currentToNeighborDist = current->distance(neighbor);
           float newNeighborTentativeDist = currentToNeighborDist + current->tnDist();
           if (newNeighborTentativeDist < neighbor->tnDist()) {
              neighbor->setTnDist(newNeighborTentativeDist);
              neighbor->setPrev(current);
           }
         }
         current->setVisited(true);
          
         // find unvisited nodes with the smalled tnDist
         NodeDj* closestNode = NULL;
         for (int i = 0; i < n_nodes; ++i) {
           if (nodeList[i]->visited())
             continue;
           if (closestNode == NULL || nodeList[i]->tnDist() < closestNode->tnDist())
             closestNode = nodeList[i];
         }
         current = closestNode;
         if ( complete_traversal && (closestNode == NULL || closestNode->tnDist() == large_number)) {
            is_solving = false;
            if (closestNode == NULL )
               std::cout << "Shortest path to every node discovere!" << std::endl;
            else
               std::cout << "Found no way to visit unvisited nodes" << std::endl;
         } else if (!complete_traversal && dest->visited()) {
            is_solving = false;
            std::cout << "Shortest path to destination discovered!" << std::endl;
         }
      }

      // Line from destination to the start
      if (dest->prev() != NULL ) {
         NodeDj* node = dest;
         NodeDj* prev;
         while (node->prev() != NULL ) {
           prev = node->prev();
           sf::RectangleShape line = Line(node->x(), node->y(), prev->x(), prev->y(), 3);
           line.setFillColor(sf::Color::Green);
           window.draw(line);
           node = prev;
         }
      }

      // Markers for each node. We want this to be on top of all other drawings.

      for (int i = 0;i < n_nodes; ++i)
          window.draw(nodeMarkers[i]);
      
      window.display();
      // sf::sleep(sf::milliseconds(50));
    }
    return 0;
} 

