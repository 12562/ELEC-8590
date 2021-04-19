// Taken from https://github.com/abangfarhan/graph-sfml/blob/master/include/graphHelper.h

#include <math.h>
#include <time.h>

#define PI 3.14159265

sf::RectangleShape Line(float x1, float y1, float x2, float y2, float thickness = 1) { 
     sf::RectangleShape line;
     float len, angle;
 
     line.setPosition(x1, y1);
     len = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
     angle = atan((y2 - y1) / (x2 -x1)) * 180 / PI;
     // line pointing down-left and top-left must be incremented by 180 deg
     if ( x2 - x1 < 0 ) angle += 180;
 
     line.setSize(sf::Vector2f(len, thickness));
     line.setFillColor(sf::Color(100, 100, 100));
     line.setRotation(angle);
     return line;
}

void set_xy_coordinates_for_nodes( unsigned int numnodes, NodeKL * data, int max_x, int max_y ) {
     float x, y, tmp;
     srand(time(NULL));
     for (unsigned int i = 0; i < numnodes; ++i) {
       switch ( i % 10 ) {
         case 0: tmp = (max_x / 22);
                break;
         case 1: tmp = (2 * max_x / 22);
                break;
         case 2: tmp = (3 * max_x / 22);
                break;
         case 3: tmp = (4 * max_x / 22);
                break;
         case 4: tmp = (5 * max_x / 22);
                break;
         case 5: tmp = (6 * max_x / 22);
                break;
         case 6: tmp = (7 * max_x / 22);
                break;
         case 7: tmp = (8 * max_x / 22);
                break;
         case 8: tmp = (9 * max_x / 22);
                break;
         case 9: tmp = (10 * max_x / 22);
                break;
       }
       if ( data[i].getGroup() == 1 ) {
          x = tmp;
       } else {
          x = (max_x / 2) + tmp;
       }
       y = rand() % max_y;
       data[i].setX(x);
       data[i].setY(y);
     }
}

void drawGraph(unsigned int n_nodes, NodeKL * nodeList, int height, int width) {
     sf::CircleShape nodeCircles[n_nodes];
     for (unsigned int i = 0; i < n_nodes; ++i) {
        float radius = 5;
        nodeCircles[i].setRadius(radius);
        nodeCircles[i].setPosition(sf::Vector2f(nodeList[i].x() - radius, nodeList[i].y() - radius));
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
      for (unsigned int i = 0; i < n_nodes; ++i) {
          window.draw(nodeCircles[i]);
          for (std::pair<NodeKL*,float> &neighbor: nodeList[i].neighbors()) {
              sf::RectangleShape line = Line(nodeList[i].x(), nodeList[i].y(), neighbor.first->x(), neighbor.first->y(), neighbor.second);
              if (neighbor.second > 0.67 ) {
                 line.setOutlineColor(sf::Color(255,0,0,200));
                 line.setFillColor(sf::Color(255,0,0));
              } else if ( neighbor.second > 0.33 ) {
                 line.setOutlineColor(sf::Color(0,255,0,200));
                 line.setFillColor(sf::Color(0,255,0));
              } else {
                 line.setOutlineColor(sf::Color(0,0,255,200));
                 line.setFillColor(sf::Color(0,0,255));
              }
              window.draw(line);
          }
      }
      float dividing_line_thickness = 5;
      sf::RectangleShape line = Line((width/2),0,(width/2),height,dividing_line_thickness);
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

template <class anyNode>
void fillGraph(anyNode* nodeList[], int n_nodes, int max_x, int max_y, int max_neighbors, int min_neighbors) {
     srand(time(NULL));
     float x;
     float y;
     float tmp;
     for (int i = 0; i < n_nodes; ++i) {
         switch ( i % 10 ) {
           case 0: tmp = (max_x / 22);
                  break;
           case 1: tmp = (2 * max_x / 22);
                  break;
           case 2: tmp = (3 * max_x / 22);
                  break;
           case 3: tmp = (4 * max_x / 22);
                  break;
           case 4: tmp = (5 * max_x / 22);
                  break;
           case 5: tmp = (6 * max_x / 22);
                  break;
           case 6: tmp = (7 * max_x / 22);
                  break;
           case 7: tmp = (8 * max_x / 22);
                  break;
           case 8: tmp = (9 * max_x / 22);
                  break;
           case 9: tmp = (10 * max_x / 22);
                  break;
         }
         if ( i < n_nodes / 2) {
            x = tmp;
         } else {
            x = (max_x / 2) + tmp;
         }
         y = rand() % max_y;
         nodeList[i] = new anyNode(x,y);
     }
     for (int i = 0; i < n_nodes; ++i) {
         int n_neighbors = min_neighbors + rand() % (max_neighbors - min_neighbors);
         for (int j = 0; j < n_neighbors; ++j) {
             int neighbor_index = rand() % n_nodes;
             if (neighbor_index == i ) { 
                j--;
                continue;
             }
             nodeList[i]->addNeighbor(nodeList[neighbor_index]);
         }
     }
}

template <class anyNode>
void fillGraphGrid(anyNode* nodeList[], int space, int gridWidth, int gridHeight) {
     srand(time(NULL));

     for (int i = 0; i < gridWidth; ++i)
         for (int j = 0; j < gridHeight; ++j) {
             // add space/2 for padding
             int x = space/2 + (i * space);
             int y = space/2 + (j * space);
             nodeList[i + j * gridWidth] = new anyNode(x, y);
         }
     
     for (int i = 0; i < gridWidth; ++i)
         for (int j = 0; j < gridHeight; ++j) {
             float rnd;
             if ( i > 0 ) {
                rnd = float(rand()) / RAND_MAX;
                if ( rnd < 0.70 )
                   nodeList[i + j * gridWidth]->addNeighbor(nodeList[i-1 + j * gridWidth]);
             }
             if ( j > 0 ) {
                rnd = float(rand()) / RAND_MAX;
                if ( rnd < 0.70 )
                   nodeList[i + j * gridWidth]->addNeighbor(nodeList[i + (j-1) * gridWidth]);
             }
             if ( i > 0 && j > 0 ) {
                rnd = float(rand()) / RAND_MAX;
                if ( rnd < 0.60 ) 
                   nodeList[i + j * gridWidth]->addNeighbor(nodeList[i-1 + (j-1) * gridWidth]);
             }
         }
}

template <class anyNode>
void graphInfo(anyNode* nodeList[], int n_nodes) {
     for (int i = 0; i < n_nodes; ++i) {
         std::cout << "Node " << nodeList[i] << std::endl;
         std::cout << "  Coordinate: (" << nodeList[i]->x() << ", " << nodeList[i]->y() << ")" << std::endl;
         std::cout << "  Neighbors: " << std::endl;
         for (anyNode* neighbor: nodeList[i]->neighbors())
             std::cout << "  - " << neighbor << " - Distance: " << nodeList[i]->distance(neighbor) << std::endl;
     }
}

