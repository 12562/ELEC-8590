#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <regex>

NodeLM* read_maze_file(std::string maze_file, int * gridsize, std::vector<std::pair<std::pair<int,int>,std::pair<int,int>>> *nets, int grid_node_size, int debug) {
    NodeLM* nodeList;
    std::string line = "";
    int x_coordinate, y_coordinate, source_x_coordinate, source_y_coordinate, dest_x_coordinate, dest_y_coordinate;
    //std::vector<std::pair<std::pair<int,int>,std::pair<int,int>>> nets;
     
    std::ifstream file(maze_file.c_str());
    while (line.find("grid size") == std::string::npos) {
      getline(file,line);
    }
    std::regex pattern ("(\\d*).*");
    std::smatch match;
    
    // Read grid size
    bool pattern_matched = std::regex_search (line, match, pattern);
    if ( pattern_matched ) {
        *gridsize = atoi(match[1].str().c_str());
        nodeList = new NodeLM[(*gridsize) * (*gridsize)];
    }
    if ( debug ) { std::cout << (*gridsize) * (*gridsize) << std::endl; }
    while ( line.find("obstruction") == std::string::npos) {
      getline(file,line);
    }
    
    // Read obstruction nodes
    pattern = ("obstruction (\\d*) (\\d*)"); 
    while ( line.find("obstruction") != std::string::npos) {
      pattern_matched = std::regex_search (line, match, pattern);
      if ( pattern_matched ) {
         x_coordinate = atoi(match[1].str().c_str()); 
         y_coordinate = atoi(match[2].str().c_str()); 
      }
      nodeList[x_coordinate * (*gridsize) + y_coordinate].setnodeasobstruction();
      if ( debug ) { std::cout << x_coordinate << ":" << y_coordinate << "\n";}
      getline(file,line);
    }
    
    while ( line.find("net") == std::string::npos) {
      getline(file,line);
    }
    
    // Read source and destination nodes for all nets
    pattern = ("net *(\\d*) *(\\d*) *(\\d*) *(\\d*)");
    while ( line.find("net") != std::string::npos) {
      pattern_matched = std::regex_search (line, match, pattern);
      if ( pattern_matched ) {
         source_x_coordinate = atoi(match[1].str().c_str()); 
         source_y_coordinate = atoi(match[2].str().c_str()); 
         dest_x_coordinate = atoi(match[3].str().c_str()); 
         dest_y_coordinate = atoi(match[4].str().c_str()); 
      }
      (*nets).push_back(std::make_pair(std::make_pair(source_x_coordinate,source_y_coordinate),std::make_pair(dest_x_coordinate,dest_y_coordinate)));
      if ( debug ) { std::cout << source_x_coordinate << ":" << source_y_coordinate << "::" << dest_x_coordinate << ":" << dest_y_coordinate << "\n";}
      getline(file,line);
    }
    /*std::string node_name;
    for ( unsigned int i = 0; i < *numnodes; i++ ) {
       getline(file,line);
       std::stringstream sstm(line);
       sstm >> node_name;
       nodeList[i].setName(node_name); 
       std::cout << i << ": "<< nodeList[i].name() << std::endl;
    }*/
    file.close();
    return nodeList;
}
