#include <limits>
#include <iostream>
#include <vector>
#include <set>
#include <random>
#include <string>
#include <cstddef>
#include <math.h>

#define PI 3.14159265

std::string get_dir(int node1_x, int node1_y, int node2_x, int node2_y) {
  std::string dir;
  if ( node1_x  == node2_x )
     if ( node1_y < node2_y ) 
        dir = "down";
     else
        dir = "up";
  else
     if ( node1_x < node2_x )
        dir = "right";
     else
        dir = "left";
  return dir;
}

void retrace(NodeLM* s, NodeLM* t, int gridsize, int grid_node_size, int ctr, sf::RenderWindow *window) {
  std::set<NodeLM*> previous_node;
  std::set<NodeLM*> new_previous_nodes;
  //int node_num, count; *color;
  int num_bends; 
  std::string path_sum_x, path_sum_y;
  std::string dir;
  previous_node.insert(t);
  do {
    for (NodeLM* e : previous_node) {
      //count = 0;
      for (NodeLM* neighbor : e->neighbors()) {
        //if ( ((neighbor->getLabel() == (e->getLabel() - 1)) || ((neighbor->getLabel()) - 1 == e->getLabel())) && !e->is_shown_connected_to(neighbor) ) 
        if ( neighbor->getLabel() == (e->getLabel() - 1) ) {
           if ( e->x() == t->x() && e->y() == t->y() ) {
              //node_num = (((e->x() - grid_node_size/2) / grid_node_size) * gridsize) + ((e->y() - grid_node_size/2) / grid_node_size);
              e->add_prev_node_data(ctr,std::to_string((e->get_coordinates(grid_node_size)).first), std::to_string((e->get_coordinates(grid_node_size)).second),e,"none",0,0,0);
           } 
           dir = get_dir(e->x(), e->y(), neighbor->x(), neighbor->y());
           //node_num = (((neighbor->x() - grid_node_size/2) / grid_node_size) * gridsize) + ((neighbor->y() - grid_node_size/2) / grid_node_size);
           //for (std::pair<int,int> path: e->get_path(ctr))
           for (std::pair<std::pair<std::string,std::string>,NodeLM*> path: e->get_path(ctr)) {
             if ( dir == e->get_direction(ctr,path.second,path.first.first,path.first.second) || e->get_direction(ctr,path.second,path.first.first,path.first.second) == "none" ) {
                num_bends = e->get_num_bends(ctr,path.second,path.first.first,path.first.second);
             } else {
                num_bends = e->get_num_bends(ctr,path.second,path.first.first,path.first.second) + 1;
             }
             //path_sum = path + node_num;
             path_sum_x = path.first.first + std::to_string((neighbor->get_coordinates(grid_node_size)).first);
             path_sum_y = path.first.second + std::to_string((neighbor->get_coordinates(grid_node_size)).second);
             neighbor->add_prev_node_data(ctr,path_sum_x,path_sum_y,e,dir,num_bends,neighbor->is_already_on_a_nets_path(ctr),0);
           }
           new_previous_nodes.insert(neighbor);
           //e->add_path_prevNode(neighbor,1);
           sf::RectangleShape line = Line(e->x(), e->y(), neighbor->x(), neighbor->y(), 3);
           //std::cout << neighbor->x() << ":" << neighbor->y() << "\n";
           //color = e->getColor();
           /*if ( count && !color[0] && !color[1] && !color[2] ) {
              color[0] = (rand() % 255);
              color[1] = (rand() % 255);
              color[2] = (rand() % 255);
           }
           neighbor->setColor(color);*/
           line.setFillColor(sf::Color::Green);
           sf::CircleShape triangle = Triangle(e->x(), e->y(), neighbor->x() , neighbor->y(), 5); 
           triangle.setFillColor(sf::Color::Green);
           (*window).draw(line);
           (*window).draw(triangle);
           (*window).display();
           //e->update_is_shown_to(neighbor,1,0);
           sf::sleep(sf::milliseconds(25));
           //count++;
        }
      }
    } 
    previous_node = new_previous_nodes;
    new_previous_nodes.clear();
  } while (!previous_node.empty());
}

 
void lm_router(std::vector<std::pair<std::pair<int,int>,std::pair<int,int>>> *nets, NodeLM *nodeList, int n_nodes, int gridsize, int grid_node_size) {
  std::set<NodeLM*> plist;
  std::set<NodeLM*> nlist;
  NodeLM *s,*t;
  int temp = 1, path_exists = 0,  already_drawn = 0, ctr = 0; 
  std::pair<std::pair<int,int>,std::pair<int,int>> tmp_value;
  int num_nets = nets->size();
  int num_tries = num_nets;
  int num_nets_successfully_routed = 0;
  
  srand( (unsigned)time(NULL));
  
  sf::RectangleShape nodesqrs[n_nodes];
  sf::Text text[n_nodes];
  sf::Font font;
  font.loadFromFile("/home/mohit/Downloads/uwindsor/Physical_design_automation/projects/programming_assignment/Lee_Moore_algorithm/src/Roboto/Roboto-Regular.ttf");
    
  int width = grid_node_size * (gridsize+1) + 500;
  int grid_width = grid_node_size * (gridsize+1);
  int height = grid_node_size * (gridsize+1);
  int radius = 10;
  
  initialize_nodes_to_draw(nodesqrs, nodeList, text, &font, n_nodes, grid_node_size);
  
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;
  sf::RenderWindow window;
  window.create(sf::VideoMode(width, height), "Net Routing", sf::Style::Default, settings);
  
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if ( event.type == sf::Event::Closed) {
         window.close();
      }
    }
    if ( ctr < num_nets ) { 
      std::vector<std::pair<std::pair<int,int>,std::pair<int,int>>>::iterator path = (*nets).begin();
      window.clear(sf::Color::White);  
      draw_boundary_nodes_and_starting_grid (&window, nodesqrs, &font, radius, gridsize, grid_node_size, grid_width, height, n_nodes);
      draw_previous_nets_sources_and_sinks (&window, nodeList, radius, n_nodes);
      std::cout << "\n*******************************************************************\n";
      std::cout << "*Try number : " << num_nets - num_tries + 1<< "\n\n";
      while ( path != (*nets).end() ) {
        std::cout << "**Routing net number: " << ctr + 1 << "\n";
        for (std::pair<std::pair<int,int>,std::pair<int,int>> s_and_t_pairs: (*nets)) {
          s = &nodeList[(s_and_t_pairs).first.first * gridsize + (s_and_t_pairs).first.second];
          s->update_has_source_node(1);
          t = &nodeList[(s_and_t_pairs).second.first * gridsize + (s_and_t_pairs).second.second];
          t->update_has_target_node(1);
        }
         
        s = &nodeList[(*path).first.first * gridsize + (*path).first.second];
        t = &nodeList[(*path).second.first * gridsize + (*path).second.second];

        plist.insert(s);
        std::cout << "\n----------------------------\n";
        std::cout << "***Source coordinates: " << (s->get_coordinates(grid_node_size)).first << ":" << (s->get_coordinates(grid_node_size)).second << "\n";
        std::cout << "***Target coordinates: " << (t->get_coordinates(grid_node_size)).first << ":" << (t->get_coordinates(grid_node_size)).second << "\n";
        std::cout << "----------------------------\n";
        
        draw_previous_nets_sources_and_sinks (&window, nodeList, radius, n_nodes);
        draw_current_source_and_sink (s, t, radius, &window, sf::Color::Green, sf::Color::Green);
        
        if ( !already_drawn ) {
          while (!plist.empty()) {
            for (NodeLM* e : plist) {
              for (NodeLM* neighbor : e->neighbors()) {
                if ( !neighbor->is_already_on_a_selected_path() && !neighbor->is_obstruction() && neighbor->getLabel() == 0 && !neighbor->is_source_node() && (!neighbor->is_target_node() || neighbor == t)){
                   neighbor->setLabel(temp);
                   text[neighbor->get_node_num(grid_node_size,gridsize)].setString(std::to_string(temp));
                   window.draw(text[neighbor->get_node_num(grid_node_size,gridsize)]);
                   window.display();
                   sf::sleep(sf::milliseconds(25));
                   nlist.insert(neighbor);
                   //std::cout << neighbor->x() << ":" << neighbor->y() << " ";
                   if ((neighbor->x() == t->x() ) && (neighbor->y() == t->y())) {
                      path_exists = 1;
                      break;
                   }
                }
                if ( neighbor->is_obstruction() && neighbor->getLabel() == 0 && neighbor->x() == t->x() && neighbor->y() == t->y() ) {
                   neighbor->setLabel(temp);
                   path_exists = 1;
                   break;
                }
              } 
              //std::cout << "\n";
            }
            if ( path_exists ) { break; }
            temp++;
            plist = nlist;
            nlist.clear();
          }
          if ( path_exists && !already_drawn ) {
             already_drawn = 1;
             std::cout << "Path exists between source and target nodes\n_________________________________________________\n\n";
             num_nets_successfully_routed++;
             retrace(s, t, gridsize, grid_node_size, ctr, &window); 
             draw_traced_path(s, t, ctr, &window);
          } else {
             if ( !path_exists ) {
                std::cout << "Path does not exist between source and target nodes\n\n";
                std::cout << "\n*******************************************************************\n";
                //new_nets.push_back(path);
                //for (std::pair<std::pair<int,int>,std::pair<int,int>> other_path: (*nets))
                //  if ( other_path != path )
                //     new_nets.push_back(other_path);
                //nets = &new_nets;
                if ( num_tries > 0 ) {
                   //draw_current_source_and_sink (s, t, radius, &window);
                   blink_current_source_and_sink (s, t, radius, &window);
                   num_tries--; 
                   tmp_value = (*path);  
                   (*nets).erase(path);
                   path = (*nets).begin();
                   (*nets).insert(path, tmp_value);
                   path = (*nets).begin();
                   ctr = 0;
                   already_drawn = 0;
                   path_exists = 0;
                   temp = 1;
                   plist.clear();
                   nlist.clear();
                   num_nets_successfully_routed = 0; 
                   //new_nets.clear();
                   for ( int i = 0; i < n_nodes ; i ++ ) {
                     nodeList[i].setLabel(0);
                     nodeList[i].delete_from_selected_path();
                     nodeList[i].delete_prev_node_data();
                     nodeList[i].update_has_target_node(0);
                     nodeList[i].update_has_source_node(0);
                     for (NodeLM* neighbor : nodeList[i].neighbors()) {
                        nodeList[i].update_line_exists_with_neighbor_node(neighbor,0);
                     }
                   }
                   //std::cout << "\nChecking" << (*nets).size() << "\n";
                   sf::sleep(sf::milliseconds(10000));
                   window.clear(sf::Color::White);
                   draw_boundary_nodes_and_starting_grid (&window, nodesqrs, &font, radius, gridsize, grid_node_size, grid_width, height, n_nodes);
                   draw_previous_nets_sources_and_sinks (&window, nodeList, radius, n_nodes);
                   window.display();
                   std::cout << "*Try number : " << num_nets - num_tries + 1 << "\n\n";
                   continue;
                }
             }
          }
        }
        //window.display();
        sf::sleep(sf::milliseconds(25));
        ctr++;
        already_drawn = 0;
        path_exists = 0;
        temp = 1;
        plist.clear();
        nlist.clear();
        for ( int i = 0; i < n_nodes ; i ++ ) {
          nodeList[i].setLabel(0);
          //for (NodeLM* neighbor : nodeList[i].neighbors()) {
          //  nodeList[i].update_is_shown_to(neighbor,0,0);
          //}
        }
        path++;
        window.clear(sf::Color::White);  
        draw_boundary_nodes_and_starting_grid (&window, nodesqrs, &font, radius, gridsize, grid_node_size, grid_width, height, n_nodes);
        draw_previous_nets_sources_and_sinks (&window, nodeList, radius, n_nodes);
        window.display();
      }
      std::cout << "*******************************************************************\n\n";
      std::cout << "*******************************************************************\n";
      std::cout << "Number of nets successfully routed = " << num_nets_successfully_routed << "/" << num_nets << " in try number " << num_nets - num_tries + 1;
      std::cout << "\n*******************************************************************\n";
    }
  }
  /*sf::Text text1;
  text1.setFont(font);

  //sf::ContextSettings settings;
  //settings.antialiasingLevel = 8;
  //sf::RenderWindow window;
  //window.create(sf::VideoMode(width, height), "Individual Net Routing", sf::Style::Default, settings);
  ctr = 0;
  NodeLM *source[num_nets], *target[num_nets];
  sf::CircleShape startNode[num_nets];
  sf::CircleShape endNode[num_nets];
  for (std::pair<std::pair<int,int>,std::pair<int,int>> path: (*nets)) {
    source[ctr] = &nodeList[path.first.first * gridsize + path.first.second];
    target[ctr] = &nodeList[path.second.first * gridsize + path.second.second];

    startNode[ctr].setPosition(source[ctr]->x() - radius, source[ctr]->y() - radius);  
    startNode[ctr].setRadius(radius);
    startNode[ctr].setFillColor(sf::Color::Blue);

    endNode[ctr].setPosition(target[ctr]->x() - radius, target[ctr]->y() - radius);  
    endNode[ctr].setRadius(radius);
    endNode[ctr].setFillColor(sf::Color::Red);
    
    ctr++;
  }
  already_drawn = 0;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if ( event.type == sf::Event::Closed) {
         window.close();
      }
    }
    if ( ! already_drawn ) {
      window.clear(sf::Color::White);  
      for (int i = 0; i < n_nodes; ++i) {
        window.draw(nodesqrs[i]);
      }
      for (ctr=0;ctr<num_nets;ctr++) {
        window.draw(startNode[ctr]);
        window.draw(endNode[ctr]);
        curr_node = source[ctr];
        do {
          min_bends_path = curr_node->get_path_on_single_net_and_with_min_bends(ctr);
          prev_node = curr_node->get_prev_node(ctr, min_bends_path);
          sf::RectangleShape line = Line(curr_node->x(), curr_node->y(), prev_node->x(), prev_node->y(), 5);
          line.setFillColor(sf::Color(255,255,0));
          window.draw(line);
          window.display();
          curr_node->add_on_selected_path();
          curr_node = prev_node;
        } while (curr_node != target[ctr]); 
      }
      window.display();
      already_drawn = 1;
    }
  }*/
}
