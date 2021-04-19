// Taken from https://github.com/abangfarhan/graph-sfml/blob/master/src/base.cpp

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Node.h"
#include "KL_graphHelper.h"

int main () {
    const int width = 1200;
    const int height = 600;

    int n_nodes = 50;
    Node* nodeList[n_nodes];
    fillGraph<Node>(nodeList, n_nodes, width, height, 2, 3);
    graphInfo<Node>(nodeList, n_nodes);

    sf::CircleShape nodeCircles[n_nodes];
    for (int i = 0; i < n_nodes; ++i) {
        float radius = 5;
        nodeCircles[i].setRadius(radius);
        nodeCircles[i].setPosition(sf::Vector2f(nodeList[i]->x() - radius, nodeList[i]->y() - radius));
        nodeCircles[i].setFillColor(sf::Color(255, 0, 0, 90));
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
              sf::RectangleShape line = Line(nodeList[i]->x(), nodeList[i]->y(), neighbor->x(), neighbor->y(),0.5);
              line.setOutlineColor(sf::Color(0,0,0,50));
              window.draw(line);
          }
      }
      sf::RectangleShape line = Line((width/2),0,(width/2),height);
      line.setFillColor(sf::Color(0,0,255));
      line.setOutlineColor(sf::Color(0,0,255));
      window.draw(line);
      //sf::RectangleShape rect1(sf::Vector2f((width/2)-4, height-4));
      //rect1.setFillColor(sf::Color(255,255,255,10));
      //rect1.setPosition(2,2); 
      //rect1.setOutlineThickness(2);
      //rect1.setOutlineColor(sf::Color(0,0,255)); 
      //window.draw(rect1);
      //sf::RectangleShape rect2(sf::Vector2f((width/2), height));
      //rect2.setPosition((width/2) + 1, 0);
      //rect2.setFillColor(sf::Color(255,255,255,10));
      //window.draw(rect2);
      window.display();
    }
}
