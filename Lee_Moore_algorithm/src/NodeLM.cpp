#include <vector>
#include <string>
#include <utility>
#include <iostream>
#include <iterator>
#include <map>
#include <climits>

#include "Node.h"
#include "NodeLM.h"

int NodeLM::getLabel() {
      return _label;
}

void NodeLM::setLabel(int label) {
     _label = label;
}

bool NodeLM::is_obstruction() {
     return _is_obstruction;
}

void NodeLM::setnodeasobstruction() {
    _is_obstruction = true; 
}

std::vector<NodeLM*> NodeLM::neighbors() {
     std::vector<NodeLM*> neighbors;
     std::vector<std::pair<NodeLM*,int>>::iterator neighbor;
     for (neighbor = _neighbors.begin(); neighbor!=_neighbors.end(); neighbor++)
        neighbors.push_back((*neighbor).first);
     return neighbors;
}

void NodeLM::addNeighbor(NodeLM* node) {
     for (std::pair<NodeLM*,int> neighbor: _neighbors)
         if (neighbor.first == node) {
            neighbor.second = 0;
            return;
         }
     _neighbors.push_back(std::make_pair(node,0));
     node->addNeighbor(this);
}

void NodeLM::update_line_exists_with_neighbor_node(NodeLM* node, int value) {
     std::vector<std::pair<NodeLM*,int>>::iterator neighbor;
     for (neighbor = _neighbors.begin(); neighbor!=_neighbors.end(); neighbor++)
         if ((*neighbor).first == node)
            (*neighbor).second = value;
}          

int NodeLM::is_to_be_shown_connected_to(NodeLM* node) {
    for (std::pair<NodeLM*,int> neighbor: _neighbors)
        if (neighbor.first == node)
           return neighbor.second;
    return 0;
}

void NodeLM::update_has_source_node(int value) {
     _has_source_node = value;
}

int NodeLM::is_source_node() {
    return _has_source_node;
}

int NodeLM::is_target_node() {
    return _has_target_node;
}

void NodeLM::update_has_target_node(int value) {
     _has_target_node = value;
}

/*int NodeLM::is_shown_connected_to(NodeLM* node) {
    for (std::pair<NodeLM*,int> neighbor: _neighbors)
        if (neighbor.first == node)
           return neighbor.second;
    return 0;
}

void NodeLM::update_is_shown_to(NodeLM* node,int value, int update) {
     std::vector<std::pair<NodeLM*,int>>::iterator neighbor;
     for (neighbor = _neighbors.begin(); neighbor!=_neighbors.end(); neighbor++)
         if ((*neighbor).first == node)
            (*neighbor).second = value;
     if ( update )
        node->update_is_shown_to(this,value,0);
}*/
  
/*int* NodeLM::getColor() {
    return _color;
}

void NodeLM::setColor(int *color) {
     _color[0] = color[0]; 
     _color[1] = color[1]; 
     _color[2] = color[2]; 
}*/

/*void NodeLM::add_path_prevNode(NodeLM* node, int path_num) {
     _prev_node.push_back(std::make_pair(path_num,node));
}*/

/*NodeLM* NodeLM::get_prev_node(int net_num_to_route, int path_num_for_the_net_x, int path_num_for_the_net_y) {
  for (auto const& currentPath: _path_data) {
    //if ( (std::get<0>(currentPath) == net_num_to_route) && (std::get<1>(currentPath) == path_num_for_the_net) ) 
    if ( (std::get<0>(currentPath) == net_num_to_route) && ((std::get<1>(currentPath)).first == path_num_for_the_net_x) && ((std::get<1>(currentPath)).second == path_num_for_the_net_y)) 
       return std::get<2>(currentPath);
  }
}*/

/*std::string NodeLM::get_direction(int net_num_to_route, int path_num_for_the_net_x, int path_num_for_the_net_y) {
  for (auto const& currentPath: _path_data) {
    //if ( (std::get<0>(currentPath) == net_num_to_route) && (std::get<1>(currentPath) == path_num_for_the_net) ) 
    if ( (std::get<0>(currentPath) == net_num_to_route) && ((std::get<1>(currentPath)).first == path_num_for_the_net_x) && ((std::get<1>(currentPath)).second == path_num_for_the_net_y)) 
       return std::get<3>(currentPath);
  }
}*/


std::string NodeLM::get_direction(int net_num_to_route, NodeLM* prev_node, std::string path_num_for_the_net_x, std::string path_num_for_the_net_y ) {
  for (auto const& currentPath: _path_data) {
    if ( (std::get<0>(currentPath) == net_num_to_route) && (std::get<2>(currentPath) == prev_node) && ((std::get<1>(currentPath)).first == path_num_for_the_net_x) && ((std::get<1>(currentPath)).second == path_num_for_the_net_y)) 
       return std::get<3>(currentPath);
  }
}

/*int NodeLM::get_num_bends(int net_num_to_route, int path_num_for_the_net_x, int path_num_for_the_net_y) {
  for (auto const& currentPath: _path_data) {
    //if ( std::get<0>(currentPath) == net_num_to_route && std::get<1>(currentPath) == path_num_for_the_net ) 
    if ( (std::get<0>(currentPath) == net_num_to_route) && ((std::get<1>(currentPath)).first == path_num_for_the_net_x) && ((std::get<1>(currentPath)).second == path_num_for_the_net_y)) 
       return std::get<4>(currentPath);
  }
}*/

int NodeLM::get_num_bends(int net_num_to_route, NodeLM* prev_node, std::string path_num_for_the_net_x, std::string path_num_for_the_net_y) {
  for (auto const& currentPath: _path_data) {
    if ( (std::get<0>(currentPath) == net_num_to_route) && (std::get<2>(currentPath) == prev_node) && ((std::get<1>(currentPath)).first == path_num_for_the_net_x) && ((std::get<1>(currentPath)).second == path_num_for_the_net_y)) 
       return std::get<4>(currentPath);
  }
}

/*std::vector<std::pair<int,int>> NodeLM::get_path(int net_num_to_route) {
  std::vector<std::pair<int,int>> vints;
  for (auto const& tuple: _path_data) {
      if ( std::get<0>(tuple) == net_num_to_route )
        vints.push_back(std::get<1>(tuple));
  }
  return vints;
}*/

std::vector<std::pair<std::pair<std::string,std::string>,NodeLM*>> NodeLM::get_path(int net_num_to_route) {
  std::vector<std::pair<std::pair<std::string,std::string>,NodeLM*>> vints;
  for (auto const& tuple: _path_data) {
      if ( std::get<0>(tuple) == net_num_to_route )
        vints.push_back(std::make_pair(std::get<1>(tuple),std::get<2>(tuple)));
  }
  return vints;
}

void NodeLM::add_prev_node_data(int net_num_to_route, std::string path_sum_x, std::string path_sum_y, NodeLM* prev_node, std::string direction, int num_bends, int is_on_multiple_net_paths, int is_on_already_selected_path) {
      //std::vector<std::map<int,std::tuple<NodeLM*,std::string,int>>>::iterator it;
     //it = _path_data.begin();
     _path_data.push_back(std::make_tuple(net_num_to_route, std::make_pair(path_sum_x, path_sum_y), prev_node, direction, num_bends, is_on_multiple_net_paths));
     //std::map <int,std::tuple<NodeLM*, std::string, int>> word;
     //word.insert(std::make_pair(path_num_for_the_net,std::make_tuple(prev_node, direction, num_bends)));
     //_path_data.insert(std::make_pair(net_num_to_route,word));
     //(_path_data.insert(net_num_to_route))[path_num_for_the_net] = std::make_tuple(prev_node, direction, num_bends);
}

void NodeLM::delete_prev_node_data() {
     _path_data.clear();
}

int NodeLM::is_already_on_a_nets_path (int net_num_to_route) {
    for (auto const& currentPath: _path_data) {
      if (std::get<0>(currentPath) != net_num_to_route ) {
         return 1;
      }
    }
    return 0;
}

int NodeLM::is_already_on_a_selected_path () {
    return _is_on_selected_path;
}

void NodeLM::add_on_selected_path () {
    _is_on_selected_path = 1;
}

void NodeLM::delete_from_selected_path () {
    _is_on_selected_path = 0;
}

std::pair<std::string,NodeLM*> NodeLM::get_path_with_min_bends(int net_num_to_route, std::string dir) {
     //std::pair<int,std::tuple<NodeLM*, std::string, int>> path_with_min_bends;
     std::pair<std::string,NodeLM*> path_with_min_bends;
     int min_bends = INT_MAX;
     //std::map<int, std::tuple<NodeLM*, std::string, int>>::iterator currentPath;
     for (auto const& currentPath: _path_data) {
       //std::cout << "---" << (std::get<1>(currentPath)) << "---\n";
       if ( std::get<0>(currentPath) == net_num_to_route ) {
          if ( std::get<4>(currentPath) < min_bends ) {
             path_with_min_bends = std::make_pair(std::get<3>(currentPath), std::get<2>(currentPath));
             min_bends = std::get<4>(currentPath);
          } else if ( (std::get<4>(currentPath) == min_bends) && (std::get<3>(currentPath) == dir)) {
             path_with_min_bends = std::make_pair(std::get<3>(currentPath), std::get<2>(currentPath));
             min_bends = std::get<4>(currentPath);
        
          }
       }
     }
     return path_with_min_bends;
}

/*std::pair<int,int> NodeLM::get_path_on_single_net_and_with_min_bends(int net_num_to_route) {
    std::pair<int,int> path_on_single_net_and_with_min_bends;
    int min_bends = INT_MAX;
    for (auto const& currentPath: _path_data) {
      if ( std::get<0>(currentPath) == net_num_to_route ) {
        if ( (std::get<4>(currentPath) < min_bends) && !std::get<5>(currentPath) ) {
           path_on_single_net_and_with_min_bends = std::get<1>(currentPath);
           min_bends = std::get<4>(currentPath);
        } //else {
          // if ((std::get<4>(currentPath) < min_bends) || !std::get<6>(currentPath)) {
          //   path_on_single_net_and_with_min_bends = std::get<1>(currentPath);
          //   min_bends = std::get<4>(currentPath);
          // }
        //}
      }
    }
    return path_on_single_net_and_with_min_bends;
}*/

std::pair<int,int> NodeLM::get_coordinates(int grid_node_size) {
     int x = (this->x() - grid_node_size - grid_node_size/2) / grid_node_size;
     int y = (this->y() - grid_node_size - grid_node_size/2) / grid_node_size;
     return std::make_pair(x,y);
}

int NodeLM::get_node_num(int grid_node_size, int gridsize) {
    std::pair<int,int> coordinates = get_coordinates(grid_node_size);
    return coordinates.first * gridsize + coordinates.second;
}
