# KL Algorithm Implementation

## Introduction
This KL algorithm implementation was done as a programming assignment for [ELEC-8950 Physical Design Automation](https://sites.google.com/view/mohammedaskhalid/teaching?authuser=0) course at [University of Windsor](@UWindsor) 

## Report explaining the implementation and the experiments in detail
[Hypergraph Partitioning KL algorithm implementation](https://github.com/12562/ELEC-8590/blob/master/KL_algorithm/Hypergraph_partitioning_KL_algorithm_implementation.pdf)

## Example Experiment Result
   - Running the program binary would give two images displayed in succession. First is the initial partition and second is the final partition. Both images show the crossings incurred due to the partition similar to the following:
   
![Experiment result with initial cut size of 104.84](https://github.com/12562/ELEC-8590/blob/6b2d0834c303b0a1854f0e24b364cb51aeffcfe9/KL_algorithm/img/KL%20partitioning%20result%20image.png)
   - Red crossings have a distance greater than 0.67 and have the highest weight followed by blue with distance greater than 0.33 followed by green which has the least weight.
   - The algorithm endeavours to reduce the cut size (Reduce the number of higher weight crossings).

## To run
```
./bin/KL_algorithm <nodes_file> <nets_file>
```

## To make KL_algorithm binary, run command:
   ```
   make bin/KL_algorithm
   ```
 * This will create the KL_algorithm binary in ./bin directory

## Pseudo Code:
```
   - main
     - Read_command_line_parameters():  ## Sets the variables nodes_file and nets_file
     - read_node_names()             :  ## Reads the nodes file and saves node names in array of NodeKL class object (variable : node_data)
     - read_nets()                   :  ## Updates node neighbors and distance from those neighbors in the node_data object (distance =  1 / (number_of_terminals - 1))  
     - initial_partition()           :  ## Creates two vectors of NodeKL* (partition1 and partition2)which point to node_data objects.
     - cut_cost()                    :  ## Calculates the initial cut cost
     - initial_d_values()            :  ## Calculates the initial D values from the neighbor and distance information stored for each node.
     - main_pass()                   :  ## Run the KL algorithm
```

## Files:
```
   - src/KL_partitioning.cpp         : Contains  "main" function
   - include/KL_helper.h             : Contains  "show_partitions() cut_cost() initial_partition() initial_d_values()" functions 
   - include/KL_bipartion_main.h     : Contains  "get_largest_decrease_cutcost_exchange_nodes(), delete_element(), swap_element_for_group(), 
                                                 update_d_values_(), max_element_index(), swap_ele(), main_pass()" functions
   - include/read_data_helper.h      : Contains  "read_node_names, get_node_type, get_node_num, read_nets, display_data" functions
   - src/NodeKL.cpp                  : Contains  "NodeKL::getDvalue(), NodeKL::setDvalue(),  NodeKL::neighbors(), NodeKL::addNeighbor(), 
                                                  NodeKL::update_distance(), NodeKL::getGroup(), NodeKL::setGroup(), NodeKL::is_node2_connected()" functions
   - src/Node.cpp                    : Contains  "Node::Node(), Node::x, Node::y, Node::name, Node::setX, Node::setY, Node::setName, 
                                                  Node::addNeighbor, Node::neighbors, Node::distance" functions
   - include/Node.h                  : Header file for Node.cpp (Class declaration for Node)
   - include/NodeKL.h                : Header file for NodeKL.cpp (Class declaration for NodeKL)
```

## References:

   - B.W. Kernighan and S. Lin, " An Efficient Heuristic Procedure for Partitioning Graphs", Bell Systems Technical Journal 49, (February 1970), 291-307. 
   - [Repository for Graph Node](https://github.com/abangfarhan/graph-sfml)   

