#include <limits>
#include <iostream>
#include <vector>
#include "KL_graphHelper.h"

void get_largest_decrease_cutcost_exchange_nodes(std::vector<NodeKL*> A, std::vector<NodeKL*> B, float * max_gain, NodeKL ** ELE1, NodeKL ** ELE2, unsigned int num_nodes) {
       NodeKL node1, node2;
       float gain;
       *max_gain = INT_MIN;
       for (unsigned int i=0; i<A.size(); i++) {
         node1 = *A[i];
         //std::cout << "\nGroup1 element, node1 = " << node1.name() << "\n";
         for (unsigned int j=0; j<B.size(); j++) {
           node2 = *B[j];
           //std::cout << "\nGroup2 element, node2 = " << node2.name() << "\n";
           gain = node1.getDvalue() + node2.getDvalue() - 2.0*(node1.is_node2_connected(node2));
           gain = std::ceil(gain * 100.0) / 100.0;
           if ( gain > *max_gain ) {
              *max_gain = gain; *ELE1 = A[i]; *ELE2 = B[j];
           }
           //std::cout << "Node1 " << node1.name() << " : Node1 d value" << node1.getDvalue() << " :: " << " Node2 " << node2.name() << " : Node2 d value" << node2.getDvalue() << " : Node 1 node 2 connected : " << node1.is_node2_connected(node2) << " :: " << "Gain " << gain << "\n";
           //std::cout <<  node1.name() << ":" << node1.getDvalue() << "::" << node2.name() << ":" << node2.getDvalue() << "::" << node1.is_node2_connected(node2) << "::" << gain << "__________";
         }
         //std::cout << "\n";
       }
       //std::cout << "\n\nExiting get_largest_decrease_cutcost_exchange_nodes...\n\n";

}

void delete_element(std::vector<NodeKL*> *group, NodeKL ele) {
     for (std::vector<NodeKL*>::iterator it=group->begin(); it != group->end(); ) {
         if ( (*it)->name() == ele.name() ) {
            it = group->erase(it);
         } else {
            ++it;
         }
     }     
}

void swap_element_for_group(std::vector<NodeKL*> *group, NodeKL *ele1, NodeKL *ele2) {
     for (std::vector<NodeKL*>::iterator it=group->begin(); it != group->end(); ++it) {
         if ( (*it)->name() == ele1->name() ) {
            (*it) = ele2;
         }
     }     
}

int update_d_values2(unsigned int num_nodes, NodeKL * data, NodeKL* node1, NodeKL* node2) {
    std::set<NodeKL*> neighbors_of_exchange_nodes;
    int num_d_values_updated = 0;
    for ( std::pair<NodeKL*,float> &neighbor: node1->neighbors()) {
        neighbors_of_exchange_nodes.insert(neighbor.first);
    }
    for ( std::pair<NodeKL*,float> &neighbor: node2->neighbors()) {
        neighbors_of_exchange_nodes.insert(neighbor.first);
    }
    for (auto const& e : neighbors_of_exchange_nodes) {
        //std::cout << e->name() << ":" << e->getDvalue() << "::";
        if (e->getGroup() == node1->getGroup()) {
           e->setDvalue(e->getDvalue() + 2 * e->is_node2_connected(*node1) - 2 * e->is_node2_connected(*node2));
               num_d_values_updated++;
        } else {
           e->setDvalue(e->getDvalue() + 2 * e->is_node2_connected(*node2) - 2 * e->is_node2_connected(*node1));
               num_d_values_updated++;
        }
        //std::cout << e->getDvalue() << "\n";
    }
    //std::cout << "\n";
    return num_d_values_updated;
}

int update_d_values_(unsigned int num_nodes, NodeKL * data, NodeKL* node1, NodeKL* node2) {
     int num_d_values_updated = 0;
     for ( std::pair<NodeKL*,float> &neighbor: node1->neighbors()) {
         if (neighbor.first->getGroup() == node1->getGroup()) {
            if (neighbor.first->getDvalue() != (neighbor.first->getDvalue() + 2 - 2 * (neighbor.first->is_node2_connected(*node2))))
               num_d_values_updated++;
            neighbor.first->setDvalue(neighbor.first->getDvalue() + 2 - 2 * (neighbor.first->is_node2_connected(*node2))); 
         } else {
            if (neighbor.first->getDvalue() != (neighbor.first->getDvalue() + 2 * (neighbor.first->is_node2_connected(*node2)) - 2))
               num_d_values_updated++;
            neighbor.first->setDvalue(neighbor.first->getDvalue() + 2 * (neighbor.first->is_node2_connected(*node2)) - 2); 
         }
     }
     for ( std::pair<NodeKL*,float> &neighbor: node2->neighbors()) {
         if (neighbor.first->getGroup() == node2->getGroup()) {
            if (neighbor.first->getDvalue() != (neighbor.first->getDvalue() + 2 - 2 * (neighbor.first->is_node2_connected(*node1))))
               num_d_values_updated++;
            neighbor.first->setDvalue(neighbor.first->getDvalue() + 2 - 2 * (neighbor.first->is_node2_connected(*node1))); 
         } else {
            if (neighbor.first->getDvalue() != (neighbor.first->getDvalue() + 2 * (neighbor.first->is_node2_connected(*node1)) - 2))
               num_d_values_updated++;
            neighbor.first->setDvalue(neighbor.first->getDvalue() + 2 * (neighbor.first->is_node2_connected(*node1)) - 2); 
         }
     }
     return num_d_values_updated;
}

void update_d_values(unsigned int num_nodes, NodeKL * data, NodeKL node1, NodeKL node2) {
     NodeKL same_group_node, different_group_node;
     int group;
     //std::cout << "\n\nUpdating D values ........\n";
     for (unsigned int i = 0; i < num_nodes; i++) {
        group = data[i].getGroup();
        if ( group == 1 ) {
           same_group_node = node1; different_group_node = node2;
        } else {
           same_group_node = node2; different_group_node = node1;
        }
        data[i].setDvalue(data[i].getDvalue() + 2 * data[i].is_node2_connected(same_group_node) -  2 * data[i].is_node2_connected(different_group_node));
        //std::cout << "D value of " << data[i].name() << ": " << data[i].getDvalue() << "\n";
        //std::cout << data[i].name() << ": " << data[i].getDvalue() << "__";
     }
     //std::cout << "\n\n";

}

int max_element_index(float * g, unsigned int max_index) {
    float max = -FLT_MAX; 
    unsigned int index, index_of_max;
    for (index=0;index < max_index;index++) {
        if ( g[index] > max ) {
           max = g[index];
           index_of_max = index;
        }
    }
    return index_of_max;
}

void swap_ele(std::vector<NodeKL*> * G1, std::vector<NodeKL*> * G2, NodeKL *ele_A, NodeKL *ele_B) {
     //std::vector<NodeKL*>::iterator it;
     //std::cout << "\nEnter swap\n";
     //std::cout << "Before swap:: G1: ";
     //for (it = G1->begin(); it != G1->end(); ++it ) {
     //    std::cout << (*it)->name() << " "; 
     //} 
     //std::cout <<  ":: G2: ";
     //for (it = G2->begin(); it != G2->end(); ++it ) {
     //    std::cout << (*it)->name() << " "; 
     //} 
     //std::cout << "\n\n";
     ele_B->setGroup(1);
     swap_element_for_group(G1, ele_A, ele_B);
     //std::cout << "\nAfter delete A\n";
     //std::cout << "\nAfter append A\n";
     ele_A->setGroup(2);
     swap_element_for_group(G2, ele_B, ele_A);
     //std::cout << "\nAfter delete B\n";
     //std::cout << "\nAfter append B\n";
     //std::cout << "After swap:: G1: ";
     //for (it = G1->begin(); it != G1->end(); ++it ) {
     //    std::cout << (*it)->name() << " "; 
     //} 
     //std::cout <<  ":: G2: ";
     //for (it = G2->begin(); it != G2->end(); ++it ) {
     //    std::cout << (*it)->name() << " "; 
     //} 
     //std::cout << "\n\n*************************************************\n\n";
}

void main_pass(unsigned int num_nodes, NodeKL * data, std::vector<NodeKL*> &A, std::vector<NodeKL*> &B, int width, int height) {
     int j,k, iteration = 1, color=0;
     float actual_gain = FLT_MAX, max_gain, g[num_nodes/2],Gain[num_nodes/2];
     bool colored_print = false;
     NodeKL *max_gain_ele1, *max_gain_ele2, *to_swap_ele_A[num_nodes/2], *to_swap_ele_B[num_nodes/2]; 
     //std::cout << A.size() << "\n";
     //std::cout << sizeof(NodeKL) << "\n";
     std::vector<NodeKL*> group1 (A);
     std::vector<NodeKL*> group2 (B.begin(), B.end());
     max_gain_ele1 = group1[0];
     max_gain_ele2 = group2[0];
     while (actual_gain > 0 ) {
        std::cout << "\n\nPass : " << iteration << "\n\n";
        std::cout << "\n\n\nPartitions before pass are:\nA:";
        for ( auto it = group1.begin(); it != group1.end(); ++it ) {
            std::cout << (*it)->name() << " "; 
        } 
        std::cout << "\nB:";
        for ( auto it = group2.begin(); it != group2.end(); ++it ) {
            std::cout << (*it)->name() << " "; 
        } 
        cut_cost(num_nodes,group1);
        initial_d_values(num_nodes,data);
        for (unsigned int i=0;i<num_nodes/2;i++) {
            get_largest_decrease_cutcost_exchange_nodes(group1,group2,&max_gain,&max_gain_ele1,&max_gain_ele2,num_nodes);
            g[i] = max_gain; to_swap_ele_A[i] = max_gain_ele1; to_swap_ele_B[i] = max_gain_ele2;
            //std::cout << "\n\nMax gain achieved in iteration " << i << " is:" << max_gain << "\n";
            //std::cout << "********************************************************************\n";
            delete_element(&group1, *max_gain_ele1);
            delete_element(&group2, *max_gain_ele2);
            //std::cout << "\n\nA after deletion of " << max_gain_ele1->name() << " is: ";
            //for ( auto it = group1.begin(); it != group1.end(); ++it ) {
            //    std::cout << (*it)->name() << " "; 
            //} 
            //std::cout << " :: B after deletion of " << max_gain_ele2->name() << " is: ";
            //for ( auto it = group2.begin(); it != group2.end(); ++it ) {
            //    std::cout << (*it)->name() << " "; 
            //} 
            //std::cout  << "\n\n";
            //std::cout << "\n\nCheck\n";
            //std::cout << "\nLength of A:" << A.length() << "\n\n";
            //std::cout << "Exchange nodes are : " << max_gain_ele1->name() << "::" << max_gain_ele2->name() << "\n";
            if ( group1.size() > 0 ) {
               update_d_values2(num_nodes,data,max_gain_ele1,max_gain_ele2);
            }
            //d_values_stats(num_nodes, data);
        }
        Gain[0] = g[0];
        //std::cout << "Gain[0] = " << Gain[0] << "\n";
        for (unsigned int i=1;i<num_nodes/2;i++) {
            //std::cout << i << "\n";
            Gain[i] = Gain[i-1] + g[i];
            //std::cout << "Gain[" << i << "] = " << Gain[i] << "\n";
        }
        //std::cout << "\n\nCheck\n\n";
        //k = distance(Gain, max_element(Gain, Gain + num_nodes/2));
        k = max_element_index(Gain,num_nodes/2) + 1;
        actual_gain = Gain[k-1];
        if ( actual_gain - 0.01 <= 0 ) {
           actual_gain = 0;
        }
        if ( actual_gain > 0 ) {
           std::cout << "\n\nNumber of elements to swap (k value) : " << k << "\n\n";
           for (j=0;j<k;j++) {
               swap_ele(&A, &B, to_swap_ele_A[j], to_swap_ele_B[j]);
           }
        }
        group1 = A; group2 = B;
        std::cout << "\n\n\nPartitions after pass are(Swapped elements highlighted):\nA:";
        for ( auto it = group1.begin(); it != group1.end(); ++it ) {
            colored_print = false;
            for (j=0;j<k;j++)
               if ( (*it)->name() == to_swap_ele_B[j]->name() ) {
                  colored_print = true;
                  color = j;
               }
            if ( colored_print ) {
               std::cout << "\033[38;5;" << color << "m\"" << (*it)->name() << "\"\033[0m "; 
            } else {
               std::cout << (*it)->name() << " "; 
            }
        } 
        std::cout << "\nB:";
        for ( auto it = group2.begin(); it != group2.end(); ++it ) {
            colored_print = false;
            for (j=0;j<k;j++)
               if ( (*it)->name() == to_swap_ele_A[j]->name() ) {
                  colored_print = true;
                  color = j;
               }
            if ( colored_print ) {
               std::cout << "\033[38;5;" << color << "m\"" << (*it)->name() << "\"\033[0m ";
            } else {
               std::cout << (*it)->name() << " "; 
            }
        } 
        std::cout << "\nGain achieved = " << actual_gain << "\n\n";
        //exit(0);
        //if ( actual_gain > 0 ) {
        //   cut_cost(num_nodes,group1,data);
        //   initial_d_values(num_nodes,data);
        //}
        //if ( actual_gain < 1 ) {
        //   set_xy_coordinates_for_nodes(num_nodes,data,width,height);
        //   drawGraph(num_nodes,data,height,width);
        //}
        iteration++;
     }
     cut_cost(num_nodes,group1,true);
     set_xy_coordinates_for_nodes(num_nodes,data,width,height);
     drawGraph(num_nodes,data,height,width);
}

