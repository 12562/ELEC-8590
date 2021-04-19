// Taken from https://github.com/abangfarhan/graph-sfml/blob/master/include/graphHelper.h

#include <math.h>
#include <time.h>

#define PI 3.14159265

sf::CircleShape Triangle(float x1, float y1, float x2, float y2, float radius) {
     sf::CircleShape triangle(radius, 3);
     float angle;
     
     if ( x1  == x2 )
        if ( y1 < y2 ) {
           angle = 180;
           triangle.setPosition(x2 + 3*radius/4,y2 + 1*radius/4);
        } else {
           angle = 0;
           triangle.setPosition(x2 - 3*radius/4,y2 - 3*radius/4);
        }
     else
        if ( x1 < x2 ) {
           angle = 90;
           triangle.setPosition(x2 - 1*radius/4,y2 - 3*radius/4);
        } else {
           angle = 270;
           triangle.setPosition(x2 - 1*radius/4,y2 + 3*radius/4);
        }   
     triangle.setRotation(angle);
     return triangle;
}

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

void drawtext(float x, float y, int charsize, sf::Color txt_color, sf::Font *font, std::string txt_string, sf::RenderWindow *window) {
     sf::Text txt;
     txt.setPosition(x, y);
     txt.setCharacterSize(charsize);
     txt.setColor(txt_color);
     txt.setFont((*font));
     txt.setString(txt_string);
     (*window).draw(txt);
}

void drawGraph(int n_nodes, NodeLM * nodeList, int grid_node_size, int gridsize, NodeLM s, NodeLM t) {
     sf::RectangleShape nodesqrs[n_nodes];
     int width = grid_node_size * gridsize;
     int height = grid_node_size * gridsize;
     for (int i = 0; i < n_nodes; ++i) {
        nodesqrs[i].setPosition(nodeList[i].x() - grid_node_size/2,nodeList[i].y() - grid_node_size/2);
        nodesqrs[i].setOutlineColor(sf::Color(0,0,0));
        nodesqrs[i].setSize(sf::Vector2f(grid_node_size, grid_node_size));
        nodesqrs[i].setOutlineThickness(1);
        if ( nodeList[i].is_obstruction() ) {
           nodesqrs[i].setFillColor(sf::Color(0, 0, 0));
        } else {
           nodesqrs[i].setFillColor(sf::Color(255,255,255));
        }
     }
   
     int radius = 3;
 
     sf::CircleShape startNode;
     startNode.setPosition(s.x() - radius, s.y() - radius); 
     startNode.setRadius(radius);
     startNode.setFillColor(sf::Color::Blue);

     sf::CircleShape endNode;
     endNode.setPosition(t.x() - radius, t.y() - radius); 
     endNode.setRadius(radius);
     endNode.setFillColor(sf::Color::Red);
     
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
          window.draw(nodesqrs[i]);
          window.draw(startNode);
          window.draw(endNode);
      }
      window.display();
    }
}

void fillGraphGrid (NodeLM* nodeList, int gridsize, int grid_node_size) {
     int num_nodes, next_element, previous_element, next_row, previous_row; 
       
     num_nodes = gridsize * gridsize;
     for (int i=0; i < num_nodes; i++) {
         nodeList[i].setX(((i / gridsize) * grid_node_size) + grid_node_size + grid_node_size/2);
         nodeList[i].setY(((i % gridsize) * grid_node_size) + grid_node_size + grid_node_size/2);
         previous_row = i - gridsize;
         next_row = i + gridsize;
         next_element = i + 1;
         previous_element = i - 1;
         if ( previous_row >= 0 )
            nodeList[i].addNeighbor(&nodeList[previous_row]);
         if ( next_row < num_nodes ) 
            nodeList[i].addNeighbor(&nodeList[next_row]); 
         if ( previous_element > 0 && ((previous_element / gridsize) == (i / gridsize)) )
            nodeList[i].addNeighbor(&nodeList[i-1]);
         if ( next_element < num_nodes && ((next_element / gridsize) == (i / gridsize)) )
            nodeList[i].addNeighbor(&nodeList[i+1]);
     }

}


void initialize_nodes_to_draw(sf::RectangleShape *nodesqrs, NodeLM *nodeList, sf::Text *text, sf::Font *font, int n_nodes, int grid_node_size) {
  for (int i = 0; i < n_nodes; ++i) {
     nodesqrs[i].setPosition(nodeList[i].x() - grid_node_size/2,nodeList[i].y() - grid_node_size/2);
     nodesqrs[i].setOutlineColor(sf::Color(0,0,0));
     nodesqrs[i].setSize(sf::Vector2f(grid_node_size, grid_node_size));
     nodesqrs[i].setOutlineThickness(1);
     if ( nodeList[i].is_obstruction() ) {
        nodesqrs[i].setFillColor(sf::Color(0, 0, 0));
     } else {
        nodesqrs[i].setFillColor(sf::Color(255,255,255));
     }
     text[i].setPosition(nodeList[i].x() - grid_node_size/4, nodeList[i].y() - grid_node_size/4);
     text[i].setCharacterSize(20);
     text[i].setColor(sf::Color::Black);
     text[i].setFont((*font));
  }
}

void draw_boundary_nodes_and_starting_grid (sf::RenderWindow *window, sf::RectangleShape *nodesqrs, sf::Font *font, int radius, int gridsize, int grid_node_size, int gridwidth, int gridheight, int n_nodes) {
  int i;
  for (int index = 0; index <= n_nodes + (2*gridsize - 1); ++index) {
    i = index - (gridsize + 1) - (index/(gridsize +1));
    if ( index <= gridsize  || index % (gridsize + 1) == 0) { 
       sf::RectangleShape boundary_node;
       int x_coordinate = (((index%(gridsize+1)) * grid_node_size)); 
       int y_coordinate = (((index/(gridsize+1)) * grid_node_size));
       boundary_node.setPosition(x_coordinate,y_coordinate);
       boundary_node.setOutlineColor(sf::Color(0,0,0));
       boundary_node.setOutlineThickness(1);
       boundary_node.setSize(sf::Vector2f(grid_node_size, grid_node_size));
       boundary_node.setFillColor(sf::Color(255, 255, 0));
       (*window).draw(boundary_node);
       if ( !index ) {
          drawtext(x_coordinate + (2.5 *grid_node_size)/4, y_coordinate + grid_node_size/10, 20, sf::Color::Black, font, "x", window); 
          drawtext(x_coordinate + grid_node_size/8, y_coordinate + (3*grid_node_size)/8, 20, sf::Color::Black, font, "y", window); 
          sf::RectangleShape line = Line(0,0,grid_node_size,grid_node_size,2);
          (*window).draw(line); 
       } else if ( index <= gridsize ) {
          drawtext(x_coordinate + grid_node_size/4, y_coordinate + grid_node_size/4, 20, sf::Color::Black, font, std::to_string(index - 1), window); 
       } else {
          drawtext(x_coordinate + grid_node_size/4, y_coordinate + grid_node_size/4, 20, sf::Color::Black, font, std::to_string((index/(gridsize+1)) - 1), window); 
       }
    } else {
       if ( i >= 0 )
          (*window).draw(nodesqrs[i]);
    }
  }
  sf::RectangleShape line = Line(gridwidth + 3.5,0,gridwidth + 3.5,gridheight,7);
  line.setFillColor(sf::Color(0,0,0));
  (*window).draw(line);
  sf::CircleShape greenCircle_legend;
  greenCircle_legend.setPosition(gridwidth + grid_node_size, (gridsize*grid_node_size / 5));  
  greenCircle_legend.setRadius(radius);
  greenCircle_legend.setFillColor(sf::Color::Green);
  (*window).draw(greenCircle_legend);
  drawtext(gridwidth + 2*grid_node_size, (gridsize*grid_node_size / 5), 20, sf::Color::Black, font, "Current source & target nodes being routed", window); 
  sf::CircleShape redCircle_legend;
  redCircle_legend.setPosition(gridwidth + grid_node_size, (2 * gridsize*grid_node_size / 5));  
  redCircle_legend.setRadius(radius);
  redCircle_legend.setFillColor(sf::Color::Red);
  (*window).draw(redCircle_legend);
  drawtext(gridwidth + 2*grid_node_size, (2 * gridsize*grid_node_size / 5), 20, sf::Color::Black, font, "Target node", window); 
  sf::CircleShape blueCircle_legend;
  blueCircle_legend.setPosition(gridwidth + grid_node_size, (3 * gridsize*grid_node_size / 5));  
  blueCircle_legend.setRadius(radius);
  blueCircle_legend.setFillColor(sf::Color::Blue);
  (*window).draw(blueCircle_legend);
  drawtext(gridwidth + 2*grid_node_size, (3 * gridsize*grid_node_size / 5), 20, sf::Color::Black, font, "Source node", window); 
  sf::RectangleShape obstruction_legend;
  obstruction_legend.setPosition(gridwidth + grid_node_size , (4 * gridsize*grid_node_size / 5));
  obstruction_legend.setOutlineColor(sf::Color(0,0,0));
  obstruction_legend.setOutlineThickness(1);
  obstruction_legend.setSize(sf::Vector2f(grid_node_size, grid_node_size));
  obstruction_legend.setFillColor(sf::Color(0, 0, 0));
  (*window).draw(obstruction_legend);
  drawtext(gridwidth + 3*grid_node_size, (4 * gridsize*grid_node_size / 5), 20, sf::Color::Black, font, "Obstruction node", window); 
}

void draw_previous_nets_sources_and_sinks (sf::RenderWindow *window, NodeLM *nodeList, int radius, int n_nodes) {
  for (int i = 0; i < n_nodes; ++i) {
    if (nodeList[i].is_source_node()) {
       sf::CircleShape startNode;
       startNode.setPosition(nodeList[i].x() - radius, nodeList[i].y() - radius);  
       startNode.setRadius(radius);
       startNode.setFillColor(sf::Color::Blue);
       (*window).draw(startNode);
    }
    if (nodeList[i].is_target_node()) {
       sf::CircleShape endNode;
       endNode.setPosition(nodeList[i].x() - radius, nodeList[i].y() - radius);  
       endNode.setRadius(radius);
       endNode.setFillColor(sf::Color::Red);
       (*window).draw(endNode);
    }
    for (NodeLM* neighbor : nodeList[i].neighbors()) {
        if (nodeList[i].is_to_be_shown_connected_to(neighbor)) {
           //std::cout << nodeList[i].x() << ":" << nodeList[i].y() << "::" << neighbor->x() << ":" << neighbor->y() << "\n";
           sf::RectangleShape line = Line(nodeList[i].x(), nodeList[i].y(), neighbor->x(), neighbor->y(), 5);
           line.setFillColor(sf::Color(255,255,0));
           sf::CircleShape triangle = Triangle(nodeList[i].x(), nodeList[i].y(), neighbor->x() , neighbor->y(), 7); 
           triangle.setFillColor(sf::Color(0,0,0));
           (*window).draw(line);
           (*window).draw(triangle);
        }
    } 
  }
}

void draw_current_source_and_sink (NodeLM *s, NodeLM *t, int radius, sf::RenderWindow *window, sf::Color source_color, sf::Color target_color) {
  sf::CircleShape startNode;
  startNode.setPosition(s->x() - radius, s->y() - radius);  
  startNode.setRadius(radius);
  startNode.setFillColor(source_color);

  sf::CircleShape endNode;
  endNode.setPosition(t->x() - radius, t->y() - radius);  
  endNode.setRadius(radius);
  endNode.setFillColor(target_color);
  (*window).draw(startNode);
  (*window).draw(endNode);
  (*window).display();
} 

void blink_current_source_and_sink (NodeLM* s, NodeLM* t, int radius, sf::RenderWindow *window) {
  int ctr = 5;
  while ( ctr > 0 ) {
    draw_current_source_and_sink (s, t, radius, window, sf::Color::Black, sf::Color::Black);
    sf::sleep(sf::milliseconds(500));
    draw_current_source_and_sink (s, t, radius, window, sf::Color::Blue, sf::Color::Red);
    sf::sleep(sf::milliseconds(500));
    ctr--;
  }
}

void draw_traced_path(NodeLM *s, NodeLM *t, int ctr, sf::RenderWindow *window) {
  NodeLM* curr_node, *prev_node;
  std::pair<std::string,NodeLM*> min_bends_path;
  std::string dir = "none"; 
  
  curr_node = s;
  do {
    min_bends_path = curr_node->get_path_with_min_bends(ctr,dir);
    dir = min_bends_path.first;
    prev_node = min_bends_path.second;
    //prev_node = curr_node->get_prev_node(ctr, min_bends_path.first.first, min_bends_path.first.second);
    //std::cout << "\n" << curr_node->get_path_with_min_bends(ctr) << ":" << (curr_node->get_coordinates(grid_node_size)).first << "," << (curr_node->get_coordinates(grid_node_size)).second << ":" << (prev_node->get_coordinates(grid_node_size)).first << "," << (prev_node->get_coordinates(grid_node_size)).second << ":" << curr_node->get_direction(ctr, min_bends_path) << ":" << curr_node->get_num_bends(ctr,min_bends_path) << "\n";
    sf::RectangleShape line = Line(curr_node->x(), curr_node->y(), prev_node->x(), prev_node->y(), 5);
    line.setFillColor(sf::Color(255,255,0));
    (*window).draw(line);
    curr_node->update_line_exists_with_neighbor_node(prev_node,1);
    curr_node->add_on_selected_path();
    curr_node = prev_node;
    (*window).display();
  } while (curr_node != t); 
  (*window).display();
}
