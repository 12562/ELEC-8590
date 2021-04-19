#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <regex>
#include <set>
#include <algorithm>
#include <climits>
#include <cfloat>
#include <typeinfo>
#include <cmath>
#include <SFML/Graphics.hpp>


#include "Node.h"
#include "NodeLM.h"
#include "read_data_helper.h"
#include "LM_graphHelper.h"
//#include "KL_helper.h"
#include "LM_router.h"

int main(int argc, char * argv[]) {
    //const int width = 1200;
    //const int height = 600;
    const int grid_node_size = 40;
    std::string maze_file; 
    int debug = 1;
    int gridsize;
    std::vector<std::pair<std::pair<int,int>,std::pair<int,int>>> nets;
    NodeLM* node_data;
     
    if ( argc == 3 ) {
        maze_file = argv[1];
        std::cout << maze_file << "\n";
        debug = atoi(argv[2]);
        std::cout << debug << "\n";
    } else {
        maze_file = "/home/mohit/Downloads/uwindsor/Physical_design_automation/lecture_notes/routing/maze_tests.txt";
        std::cout << maze_file << "\n";
        debug = 0;
        std::cout << debug << "\n";
    }
     
    node_data = read_maze_file(maze_file, &gridsize, &nets, grid_node_size, debug); 
    if (debug) {
       std::cout << "\n\nPrinting net sources and sinks from main function:\n";
       for ( std::pair<std::pair<int,int>,std::pair<int,int>> &net_coordinates: nets ) {
           std::cout << net_coordinates.first.first << ":" << net_coordinates.first.second << "::" << net_coordinates.second.first << ":" << net_coordinates.second.second << "\n";
       }
       std::cout << "********************************************************\n";
    }
     
    fillGraphGrid(node_data, gridsize, grid_node_size);
    if ( debug ) {
       for ( int i = 0; i < gridsize; i++ ) {
         for (int j = 0; j < gridsize; j++ ) {
             std::cout << i << ":" << j  << " " << node_data[i * 15 + j].x() << ":" << node_data[i * 15 + j].y() << "\n\t"; 
             for (NodeLM* neighbor: node_data[i*15 + j].neighbors()) {
                std::cout << " " << neighbor->x() << ":" << neighbor->y();
             }
             std::cout << "\n";
         } 
         std::cout << "\n\n";
       } 
    }

    //drawGraph(gridsize * gridsize,node_data,grid_node_size, gridsize, node_data[nets.at(0).first.first * gridsize + nets.at(0).first.second], node_data[nets.at(0).second.first * gridsize + nets.at(0).second.second]);
    /*lm_router(&node_data[nets.at(0).first.first * gridsize + nets.at(0).first.second], &node_data[nets.at(0).second.first * gridsize + nets.at(0).second.second], node_data, gridsize * gridsize, gridsize, grid_node_size);*/
    lm_router(&nets, node_data, gridsize * gridsize, gridsize, grid_node_size);
    //std::cout << "\n\n\n\n\n********************************" << partition1[0]->getDvalue() << "******************\n\n\n\n\n";
    //main_pass(numnodes, node_data, partition1, partition2,width,height);*/
    return 0; 
}

