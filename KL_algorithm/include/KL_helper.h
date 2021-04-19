#include <iostream>
#include <string>
#include <random>
#include <set>
#include <algorithm>

void show_partitions(std::vector<NodeKL*> &group1, std::vector<NodeKL*> &group2, unsigned int numnodes) {
    std::cout << "\033[1;36mGroup1 : \033[0m";
     for ( unsigned int i = 0; i < (numnodes/2); i++)
       std::cout << group1[i]->name() << " ";
    std::cout << std::endl;
    std::cout << "\033[1;36mGroup2 : \033[0m";
    for ( unsigned int i = 0; i < (numnodes - (numnodes/2)); i++)
       std::cout << group2[i]->name() << " ";
    std::cout << std::endl;
}

void cut_cost(unsigned int num_nodes, std::vector<NodeKL*> &group1, bool final = false) {
    int group, connecting_node_group; 
    float cost=0, connecting_node_distance; 
    std::string connecting_node, node;
    //std::cout << "\n\nCalculating cut cost for the current partition.....\n";
    for( unsigned int i=0;i<(num_nodes/2);i++) {
       node = (*group1[i]).name();
       //std::cout << "Node : " << node << "\n";
       group = 1; 
       //std::cout << "Group : " << group << "\n";
       for (std::pair<NodeKL*, float> &neighbor: (*group1[i]).neighbors()) {
         connecting_node = neighbor.first->name();
         //std::cout << "Connecting node : " << connecting_node << "\n";
         connecting_node_group = neighbor.first->getGroup();
         connecting_node_distance = neighbor.second;
         //std::cout << "Connecting node group : " << connecting_node_group << "\n";
         if ( group != connecting_node_group ) {
            cost+=connecting_node_distance; 
         }
       }
       //std::cout << "************************************\n";
    }
    if ( final ) {
       std::cout << "\n\n******Cut cost of final partitioning : \033[1;31m" << cost << "\033[0m ********\n\n";
    } else {
       std::cout << "\n\nCut cost of current partitioning : \033[1;31m" << cost << "\033[0m\n\n";
    }

}

void initial_partition(unsigned int num_nodes, std::vector<NodeKL*> &group1 , std::vector<NodeKL*> &group2, NodeKL * node_data) {
  unsigned int i = 1;
  int j = 0;
  std::set<int> numbers,numbers2;
  std::set<int> complete_set;
   
  std::cout << "\n\n Making initial bi-partition....... \n" << num_nodes;
  for ( i = 0; i < num_nodes ; i++) {complete_set.insert(j);j++;}
  srand( (unsigned)time(NULL));
  while (numbers.size() < (num_nodes / 2 )) {
    numbers.insert((rand() % num_nodes));
  }
  //numbers.insert(0);
  //numbers.insert(1);
  //numbers.insert(2);
  //numbers.insert(8);
  //numbers.insert(9);
  std::set_difference(complete_set.begin(), complete_set.end(), numbers.begin(), numbers.end(), inserter(numbers2, numbers2.end()));
  for (auto const& e : numbers) {
    group1.push_back(&node_data[e]);
    node_data[e].setGroup(1);
  } 
  for (auto const& e : numbers2) {
    group2.push_back(&node_data[e]);
    node_data[e].setGroup(2);
  } 
  show_partitions(group1, group2, num_nodes);
}

void initial_d_values(unsigned int num_nodes, NodeKL * data) {
    int group, connecting_node_group;
    std::string connecting_node;
    float connecting_node_distance;
    //std::cout << "\n\nCalculating initial D values .....\n";
    for(unsigned int i=0;i<num_nodes;i++) {
       data[i].setDvalue(0);
       //std::cout << "Node : " << data[i].name() << "\n";
       group = data[i].getGroup();
       //std::cout << "Group : " << group << "\n";
       for (std::pair<NodeKL*, float> &neighbor: data[i].neighbors()) {
         connecting_node = neighbor.first->name();
         //std::cout << "Connecting node : " << connecting_node << "\n";
         connecting_node_group = neighbor.first->getGroup();
         connecting_node_distance = neighbor.second;
         //std::cout << "Connecting node group : " << connecting_node_group << "\n";
         if ( group == connecting_node_group ) {
            data[i].setDvalue(data[i].getDvalue() - connecting_node_distance);
         } else {
            data[i].setDvalue(data[i].getDvalue() + connecting_node_distance);
         }
       }
       //std::cout << "D value of node " << data[i].name() << ": " << data[i].getDvalue() << "\n";
       //std::cout << "************************************\n";
    }
    std::cout << "************************************\n";

}

void d_values_stats(unsigned int num_nodes, NodeKL * data) {
    int positive_d_values = 0, negative_d_values = 0, zero_d_values = 0, total = 0;
    for(unsigned int i=0;i<num_nodes;i++) {
       if ( data[i].getDvalue() > 0 )
          positive_d_values++; 
       if ( data[i].getDvalue() < 0 )
          negative_d_values++;
       if ( data[i].getDvalue() == 0 )
          zero_d_values++;
    }
    total = positive_d_values + negative_d_values + zero_d_values;
    std::cout << positive_d_values << "::" << negative_d_values << "::" << zero_d_values << "::" << total << "\n";
}
