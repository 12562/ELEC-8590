#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <regex>

/*#include "Node.h"
#include "NodeKL.h"*/

NodeKL* read_node_names(std::string nodes_file, unsigned int * numnodes, unsigned int * numterminals) {
    NodeKL* nodeList;
    std::string line = "";
     
    std::ifstream file(nodes_file.c_str());
    while (line.find("NumNodes") == std::string::npos) {
      getline(file,line);
    }
    std::regex pattern (":[ \\t]*(\\d*)");
    std::smatch match;
    bool pattern_matched = std::regex_search (line, match, pattern);
    //std::cout << match; 
    //for (auto x:match) std::cout << "Contains:" << x << " ";
    //std::cout << std::endl;
    if ( pattern_matched ) {
        *numnodes = atoi(match[1].str().c_str());
        nodeList = new NodeKL[*numnodes];
    }
    //std::cout << *numnodes << std::endl;
    getline(file,line);
    pattern_matched = std::regex_search (line, match, pattern);
    if ( pattern_matched ) {
       *numterminals = atoi(match[1].str().c_str()); 
       //std::cout << *numterminals << std::endl;
    }
    std::string node_name;
    for ( unsigned int i = 0; i < *numnodes; i++ ) {
       getline(file,line);
       std::stringstream sstm(line);
       sstm >> node_name;
       nodeList[i].setName(node_name); 
       std::cout << i << ": "<< nodeList[i].name() << std::endl;
    }
    file.close();
    return nodeList;
}

std::string get_node_type (std::string node) {
    if ( node.find("a") == std::string::npos )
       return "p";
    else
       return "a";
}
    
int get_node_num (std::string node) {
    return atoi(node.substr(1).c_str());
}

int read_nets(std::string nets_file, NodeKL* node_data, unsigned int num_term, unsigned int numnodes) {
    int degree;
    int ctr = 1;
    int ctr2 = 1;
    NodeKL *curr_KL_node, *neighbor_KL_node;
    
    std::string curr_node, node_type, neighbor_node, neighbor_type;
    int node_num = 2, neighbor_num = 2;
    int starting_pos = nets_file.find("E") + 1;
    int num_characters = nets_file.find("_",nets_file.find("_") + 1);
    int numnets = atoi(nets_file.substr(starting_pos,num_characters).c_str());
    //std::cout << numnets;
    //Node * data [numnets];
    std::string mytext, node[numnodes+1], tmp;
    std::ifstream file(nets_file.c_str());
    //ifstream file("/home/mohit/README-FIRST.txt");
    getline(file,mytext);
    while (mytext.find("NumPins") == std::string::npos) { 
        getline(file,mytext);
    }
    //cout << mytext << "\n";
    tmp = mytext.substr(mytext.find(":") + 2);
    //std::cout << tmp << std::endl;
            //std::stringstream ss(tmp);
            //ss >> numpins;
            //numpins = stoi(mytext.substr(mytext.find("NumPins") + 2));
    // int numpins;
    // numpins = atoi(tmp.c_str());
    
    while (ctr <= numnets) {
        getline(file,mytext);
        if ( mytext.find("NetDegree") != std::string::npos) {
            tmp = mytext.substr(mytext.find(":") + 2);
            //std::cout << tmp << " ";
            degree = atoi(tmp.c_str());
            //data[ctr]->degree = degree;
            //data[ctr]->node = "";
            //data[ctr]->next = NULL;
            //std::cout << degree << "\n";
            ctr2 = 1;
            while ( ctr2 <= degree) {
                getline(file,mytext);
                node[ctr2] = mytext.substr(0,mytext.find(" "));
                //std::cout << node[ctr2] << " " << std::endl;
                ctr2++;
            }
            ctr2 = 1;
            while ( ctr2 <= degree ) {
              //std::cout << "Current node ::" << node[ctr2] << "__" << std::endl;
              curr_node = node[ctr2];
              node_type = get_node_type(curr_node);
              node_num  = get_node_num(curr_node);
              //std::cout << node_type << " " << node_num << std::endl;
              if ( node_type == "a" ) {
                 curr_KL_node = &node_data[node_num + num_term];
              } else {
                 curr_KL_node = &node_data[node_num - 1];
              }
              for ( int ctr4 = ctr2 + 1; ctr4 <= degree; ctr4++ ) {
                //std::cout << "Neighbor node\t" << node[ctr4] << std::endl;
                neighbor_node = node[ctr4];
                neighbor_type = get_node_type(neighbor_node);
                neighbor_num = get_node_num(neighbor_node);
                if ( neighbor_type == "a") {
                   neighbor_KL_node = &node_data[neighbor_num + num_term];
                } else {
                   neighbor_KL_node = &node_data[neighbor_num - 1];
                }
                float dist = static_cast<float>(100 / (degree - 1)) / 100;
                //std::cout << "***********************************************\n";
                //std::cout << curr_KL_node->name() << "***********  Neighbors :";
                //for (std::pair<NodeKL*,float> &neighbor: curr_KL_node->neighbors()) {
                //   std::cout << neighbor.first->name() << " " ;
                //}
                //std::cout << std::endl;
                //std::cout << "NN:" << neighbor_KL_node->name() << "\n";
                //printf ("\n%0.2f %d\n", dist, degree);
                //std::cout << "***********************************************\n";
                curr_KL_node->addNeighbor(neighbor_KL_node, dist, true);
              }
              ctr2++;
            }
            ctr++;
        }
    }

    file.close();
    return 0;
}

void display_data(NodeKL *node_data, unsigned int numnodes) {
     for (unsigned int i = 0; i < numnodes; i++) {
       std::cout << node_data[i].name() << std::endl;
        for (std::pair<NodeKL*, float> &neighbor: node_data[i].neighbors()) {
          std::cout << neighbor.first->name() << " : " << neighbor.second << " ";
       }
       std::cout << std::endl;
     }
       
}

 //std::vector<NodeKL*> neighbors_; 
     //for ( std::vector<std::pair<NodeKL*, float>>::iterator it = _neighbors.begin(); it != _neighbors.end(); ++it) {
     //  neighbors_.push_back(it->first);
       //std::cout << "\n" << this->name() << " Current nodes neighbors: " << neighbor.first->name() << " ";
     //}
     //std::cout << std::endl;
     //return neighbors_;



/*int main(int argc, char * argv[]) {
    std::string nodes_file, nets_file; 
    int numnodes, numterminals;
    NodeKL* node_data;
    if ( argc > 1 ) {
        nodes_file = argv[1];
        nets_file = argv[2];
    } else {
        nodes_file = "/home/mohit/Downloads/uwindsor/Physical_design_automation/lecture_notes/partitioning/spp_N151_E167_R11_80_nodes.txt";
        nets_file = "/home/mohit/Downloads/uwindsor/Physical_design_automation/lecture_notes/partitioning/spp_N151_E167_R11_80_nets.txt";
    }
    node_data = read_node_names(nodes_file, &numnodes, &numterminals); 
    read_nets(nets_file, node_data, numterminals, numnodes);
    display_data(node_data, numnodes);
    //for ( int i = 0; i < numnodes; i ++)
    //   std::cout << ptr[i].name() << std::endl;
    return 0; 
}*/

