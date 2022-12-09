// Taken from https://github.com/abangfarhan/graph-sfml/blob/master/src/base.cpp

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Node.h"
#include "graphHelper.h"

int main () {
    const int width = 800;
    const int height = 600;

    int n_nodes = 10;
    Node* nodeList[n_nodes];
    fillGraph<Node>(nodeList, n_nodes, width, height, 2, 5);
    graphInfo<Node>(nodeList, n_nodes);

    sf::CircleShape nodeCircles[n_nodes];
    for (int i = 0; i < n_nodes; ++i) {
        float radius = 10;
        nodeCircles[i].setRadius(radius);
        nodeCircles[i].setPosition(sf::Vector2f(nodeList[i]->x() - radius, nodeList[i]->y() - radius));
        nodeCircles[i].setFillColor(sf::Color(0, 0, 0, 30));
    }
    
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(width, height), "Graph", sf::Style::Default, settings);
    while (window.isOpen()) {
      sf::Event event;
      while (window.pollEvent(event)) {
        if ( event.type == sf::Event::Closed) {
           window.close();
        }
      }
      window.clear(sf::Color::White);
      for (int i = 0; i < n_nodes; ++i) {
          window.draw(nodeCircles[i]);
          for (Node* neighbor: nodeList[i]->neighbors()) {
              sf::RectangleShape line = Line(nodeList[i]->x(), nodeList[i]->y(), neighbor->x(), neighbor->y());
              window.draw(line);
          }
      }
      window.display();
    }
}
