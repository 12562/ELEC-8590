## Introduction
This KL algorithm implementation project was implemented as a programming assignment for [ELEC-8950 Physical Design Automation](https://sites.google.com/view/mohammedaskhalid/teaching?authuser=0) course at [University of Windsor](@UWindsor) 

## Report explaining the implementation and the experiments in detail
[Hypergraph Partitioning KL algorithm implementation](https://github.com/12562/ELEC-8590/blob/master/KL_algorithm/Hypergraph_partitioning_KL_algorithm_implementation.pdf)

## To run
./bin/KL_algorithm <nodes_file> <nets_file>

## To make KL_algorithm binary, run command:
make bin/KL_algorithm
## This will create the KL_algorithm binary in ./bin directory

## Pseudo Code:
main
--Read_command_line_parameters() ## Sets the variables nodes_file and nets_file
--read_node_names()              ## Reads the nodes file and saves node names in array of NodeKL class object (variable : node_data)
--read_nets()                    ## Updates node neighbors and distance from those neighbors in the node_data object (distance =  1 / (number_of_terminals - 1))  
--initial_partition()            ## Creates two vectors of NodeKL* (partition1 and partition2)which point to node_data objects.
--cut_cost()                     ## Calculates the initial cut cost
--initial_d_values()             ## Calculates the initial D values from the neighbor and distance information stored for each node.
--main_pass()                    ## Run the KL algorithm


## Files:
src/KL_partitioning.cpp :    Contains  "main" function
include/KL_helper.h:         Contains  "show_partitions() cut_cost() initial_partition() initial_d_values()" functions 
include/KL_bipartion_main.h: Contains  "get_largest_decrease_cutcost_exchange_nodes(), delete_element(), swap_element_for_group(), 
                                        update_d_values_(), max_element_index(), swap_ele(), main_pass()" functions
include/read_data_helper.h   Contains  "read_node_names, get_node_type, get_node_num, read_nets, display_data" functions
src/NodeKL.cpp               Contains  "NodeKL::getDvalue(), NodeKL::setDvalue(),  NodeKL::neighbors(), NodeKL::addNeighbor(), 
                                     NodeKL::update_distance(), NodeKL::getGroup(), NodeKL::setGroup(), NodeKL::is_node2_connected()" functions
src/Node.cpp                 Contains  "Node::Node(), Node::x, Node::y, Node::name, Node::setX, Node::setY, Node::setName, 
                                        Node::addNeighbor, Node::neighbors, Node::distance" functions
include/Node.h               Header file for Node.cpp (Class declaration for Node)
include/NodeKL.h             Header file for NodeKL.cpp (Class declaration for NodeKL)
