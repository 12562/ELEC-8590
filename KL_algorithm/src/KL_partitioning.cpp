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
#include "NodeKL.h"
#include "read_data_helper.h"
#include "KL_helper.h"
#include "KL_bipartition_main.h"

int main(int argc, char * argv[]) {
    const int width = 1200;
    const int height = 600;
    std::string nodes_file, nets_file; 
    unsigned int numnodes, numterminals;
    NodeKL* node_data;
     
    if ( argc > 1 ) {
        nodes_file = argv[1];
        std::cout << nodes_file;
        nets_file = argv[2];
        std::cout << nets_file;
    } else {
        //nodes_file = "/home/mohit/Downloads/uwindsor/Physical_design_automation/lecture_notes/partitioning/spp_N10_E17_R11_80_nodes.txt";
        //nets_file = "/home/mohit/Downloads/uwindsor/Physical_design_automation/lecture_notes/partitioning/spp_N10_E17_R11_80_nets.txt";
        nodes_file = "../PDA/lecture_notes/partitioning/part_bm_ckts/spp_N199_E232_R11_154.nodes.txt";
        nets_file = "../PDA/lecture_notes/partitioning/part_bm_ckts/spp_N199_E232_R11_154.nets.txt";
    }
     
    node_data = read_node_names(nodes_file, &numnodes, &numterminals); 
    read_nets(nets_file, node_data, numterminals, numnodes);
    //display_data(node_data, numnodes);
 
    std::vector<NodeKL*> partition1; 
    std::vector<NodeKL*> partition2; 
    //std::cout << numnodes - (numnodes/2);
    initial_partition(numnodes, partition1, partition2, node_data);
    cut_cost(numnodes, partition1);
    initial_d_values(numnodes, node_data); 

    set_xy_coordinates_for_nodes(numnodes,node_data,width,height);
    drawGraph(numnodes,node_data,height,width);
    d_values_stats(numnodes, node_data);
    //std::cout << "\n\n\n\n\n********************************" << partition1[0]->getDvalue() << "******************\n\n\n\n\n";
    main_pass(numnodes, node_data, partition1, partition2,width,height);
    return 0; 
}

