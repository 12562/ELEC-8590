#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <random>
#include <set>
#include <algorithm>
#include <climits>
#include <fstream>
#include <map>
#include <regex>

using namespace std;

void display_data(int num_nodes, string * data2) {
    int i;
    for (i=0;i<num_nodes;i++) {
        cout << i+1 << " : " << data2[i] << "\n";
    }
}

void read_node_names(std::map<std::string,int> *nodeList, std::string nodes_file, unsigned int * numnodes, unsigned int * numterminals) {
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
        //nodeList = new string[*numnodes];
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
       nodeList->insert(std::pair<string,int>(node_name,i));
       std::cout << node_name << ": "<< (*nodeList)[node_name] << std::endl;
    }
    file.close();
}

int read_nets(std::string nets_file, vector<string> *data, std::map<std::string,int> *mapping, unsigned int num_term, unsigned int numnodes) {
    int degree;
    int ctr = 1;
    int ctr2 = 1;
    
    std::string curr_node, node_type, neighbor_node, neighbor_type;
    int node_num = 2, neighbor_num = 2;
    int starting_pos = nets_file.find("E") + 1;
    int num_characters = nets_file.find("_",nets_file.find("_") + 1);
    int numnets = atoi(nets_file.substr(starting_pos,num_characters).c_str());
    std::string mytext, node[numnodes+1], tmp;
    std::ifstream file(nets_file.c_str());

    getline(file,mytext);
    while (mytext.find("NumPins") == std::string::npos) { 
        getline(file,mytext);
    }
    tmp = mytext.substr(mytext.find(":") + 2);
    
    while (ctr <= numnets) {
        getline(file,mytext);
        if ( mytext.find("NetDegree") != std::string::npos) {
            tmp = mytext.substr(mytext.find(":") + 2);
            degree = atoi(tmp.c_str());
            ctr2 = 1;
            while ( ctr2 <= degree) {
                getline(file,mytext);
                node[ctr2] = mytext.substr(0,mytext.find(" "));
                ctr2++;
            }
            ctr2 = 1;
            while ( ctr2 <= degree ) {
              curr_node = (*mapping)[node[ctr2]];
              for ( int ctr4 = ctr2 + 1; ctr4 <= degree; ctr4++ ) {
                neighbor_node = (*mapping)[node[ctr4]];
                float dist = static_cast<float>(100 / (degree - 1)) / 100;
                if ( ) {
                   
                   data[curr_node] += std::to_string(neighbor_node) + "_" + std::to_string(dist) + " ";  
                } else {
                   data[curr_node] += std::to_string(neighbor_node) + "_" + std::to_string(dist) + " ";  
                }
                data[neighbor_node] += std::to_string(curr_node) + "_" + std::to_string(dist) + " "; 
              }
              ctr2++;
            }
            ctr++;
        }
    }

    file.close();
    return 0;
}


string * read_node_data(int * num_nodes, string * data1) {
    int i, read_type;
    string filename,mytext;
    cout << "Read data from file(0) or manual input(1):";
    cin >> read_type;
    if ( read_type ) {
       cout << "Enter number of nodes :";
       cin >> *num_nodes;
       data1 = new string[*num_nodes];
       for (i=0 ; i<*num_nodes; i++) {
           cout << "Enter comma separated list of connecting nodes to node " << i + 1 << ":";
           cin >> data1[i];
           replace(data1[i].begin(), data1[i].end(), ',', ' ');
       }
    } else {
       cout << "Enter file path :";
       cin >> filename;
       ifstream file(filename.c_str());
       getline(file,mytext);
       *num_nodes = atoi(mytext.c_str());
       data1 = new string[*num_nodes];
       for (i=0 ; i<*num_nodes; i++) {
           getline(file,mytext);
           data1[i] = mytext;
           cout << data1[i];
       }
       file.close();
    }
    //display_data(*num_nodes,data1);
    return data1;
}

void initial_partition(int num_nodes, string * group1 , string * group2) {
    bool partition_type;
    int i,num;
    //string group1 = "1 2 3, group2;
    // arr[numnodes]
    // arr[1] = "2 3 5"
    // arr[2] = "1 5"
    set<int> numbers,numbers2;
    set<int> complete_set;
    for ( i = 1; i <= num_nodes ; i ++) { complete_set.insert(i); }
    cout << "\n\n Making initial bi-partition....... \n";
    cout << "Random(0) or User input(1) :";
    cin >> partition_type;
    if (partition_type) {
        cout << "Enter group 1 :";
        cin >> *group1;
        replace(group1->begin(), group1->end(), ',', ' ');
        cout << "Enter group 2 :";
        cin >> *group2;
        replace(group2->begin(), group2->end(), ',', ' ');
    } else {
        srand( (unsigned)time(NULL));
        while (numbers.size() < (num_nodes / 2 )) {
            numbers.insert((rand() % num_nodes) + 1);
        }
        set_difference(complete_set.begin(), complete_set.end(), numbers.begin(), numbers.end(), inserter(numbers2, numbers2.end()));
        i = 1;
        for (auto const& e : numbers) {
            if ( i == 1 ) {
               *group1 += to_string(e);
            } else {
               *group1 += ' ' + to_string(e);
            }
            i++;
        } 
        i = 1;
        for (auto const& e : numbers2) {
            if ( i == 1 ) {
               *group2 += to_string(e);
            } else {
               *group2 += ' ' + to_string(e);
            }
            i++;
        }
 
    }
}

int get_group(int num, string first_group) {
    stringstream sstm(first_group);
    string tmp,str_num = to_string(num);
    while (sstm.good()) {
       sstm >> tmp;
       if ( !str_num.compare(tmp) ) {
          return 1;
       }
    } 
    return 2;
}

void initial_d_values(int num_nodes, string group1, string * data, int * d) {
    int i;
    int group, connecting_node_group;
    string connecting_node;
    cout << "\n\nCalculating initial D values .....\n";
    for(i=1;i<=num_nodes;i++) {
       d[i] = 0;
       //cout << "Node : " << i << "\n";
       group = get_group(i,group1); 
       //cout << "Group : " << group << "\n";
       stringstream connecting_nodes_iterator(data[i-1]);
       while (connecting_nodes_iterator.good()) {
         connecting_nodes_iterator >> connecting_node;
         //cout << "Connecting node : " << connecting_node << "\n";
         connecting_node_group = get_group(atoi(connecting_node.c_str()),group1);  
         //cout << "Connecting node group : " << connecting_node_group << "\n";
         if ( group == connecting_node_group ) {
            d[i]--;
         } else {
            d[i]++; 
         }
       }
       cout << "D value of " << i << ": " << d[i] << "\n";
       //cout << "************************************\n";
    }
    
}



int is_node1_node2_connected( int node1, string node2, string * data) {
    stringstream node1_connections(data[node1 - 1]);
    string tmp;
    while (node1_connections.good()) {
          node1_connections >> tmp;
          if ( !node2.compare(tmp) ) {
             return 1;
          }
    }    
    return 0;
}
    

void get_largest_decrease_cutcost_exchange_nodes(int * d, string * data, string A, string B, int * max_gain, string * ELE1, string * ELE2) {
       stringstream group1_elements(A);
       stringstream group2_elements(B);
       string ele_1, ele_2;
       int node1, node2, gain;
       *max_gain = INT_MIN;
       while (group1_elements.good()){
             group1_elements >> ele_1;
             node1 = atoi(ele_1.c_str());
             //cout << "\nAfter conversion of group1 element, node1 = " << node1 << "\n";
             //cout << "\nSeeking to 0th position for group2\n";
             group2_elements.seekg(0);
             while (group2_elements.good()) {
                   group2_elements >> ele_2;
                   node2 = atoi(ele_2.c_str());
                   //cout << "\nAfter conversion of group2 element, node2 = " << node2 << "\n";
                   gain = d[node1] + d[node2] - 2*is_node1_node2_connected(node1, to_string(node2), data);
                   if ( gain > *max_gain ) {
                      *max_gain = gain; *ELE1 = ele_1; *ELE2 = ele_2;
                   } 
                   cout << "Node1 " << node1 << " :: " << "Node2 " << node2 << " :: " << "Gain " << gain << "\n";
             } 
       }
       //cout << "\n\nExiting get_largest_decrease_cutcost_exchange_nodes...\n\n";

}

void update_d_values(int num_nodes, string group1, string group2, string * data, int * d, string node1, string node2) {
     int i; 
     string same_group_node, different_group_node, tmp; 
     string all_nodes = group1 + ' ' +  group2;
     stringstream node(all_nodes); 
     int group;
     cout << "\n\nUpdating D values ........\n";
     while (node.good()) {
        node >> tmp;
        i = atoi(tmp.c_str());
        group = get_group(i,group1);
        if ( group == 1 ) {
           same_group_node = node1; different_group_node = node2;
        } else {
           same_group_node = node2; different_group_node = node1;  
        }
        d[i] = d[i] + 2 * is_node1_node2_connected(i, same_group_node, data) -  2 * is_node1_node2_connected(i, different_group_node, data); 
        cout << "D value of " << i << ": " << d[i] << "\n";
     }

}

void delete_element(string * group, string * ele) {
         string search_string;
         *group = " " + *group + " "; search_string = " " + *ele + " ";
         group->replace(group->find(search_string),search_string.length()," ");
         group->erase(group->begin() + group->find_first_of(" "));
         if ( group->length() > 0 ) {
            group->erase(group->begin() + group->find_last_of(" "));
         }
}

void swap_ele(string * G1, string * G2, string ele_A, string ele_B) {
     cout << "\nEnter swap\n";
     delete_element(G1, &ele_A); 
     //cout << "\nAfter delete A\n";
     *G1 = *G1 + ' ' + ele_B;
     //cout << "\nAfter append A\n";
     delete_element(G2, &ele_B);
     //cout << "\nAfter delete B\n";
     *G2 = *G2 + ' ' + ele_A;
     //cout << "\nAfter append B\n";
     cout << "After swap:: G1: " << *G1 << ":: G2: " << *G2 << "\n\n";
}

void cut_cost(int num_nodes,string group1, string * data) {
    int i;
    int group, connecting_node_group, cost=0;
    string connecting_node;
    cout << "\n\nCalculating cut cost for the current partition.....\n";
    for(i=1;i<=num_nodes;i++) {
       cout << "Node : " << i << "\n";
       group = get_group(i,group1); 
       cout << "Group : " << group << "\n";
       stringstream connecting_nodes_iterator(data[i-1]);
       while (connecting_nodes_iterator.good()) {
         connecting_nodes_iterator >> connecting_node;
         cout << "Connecting node : " << connecting_node << "\n";
         connecting_node_group = get_group(atoi(connecting_node.c_str()),group1);  
         cout << "Connecting node group : " << connecting_node_group << "\n";
         if ( group != connecting_node_group ) {
            cost++; 
         }
       }
       cout << "************************************\n";
    }
    cout << "\n\nCut cost of current partitioning : " << cost / 2 << "\n\n";
    
}

int max_element_index(int * g, int max_index) {
    int max = INT_MIN; int index_of_max, index;
    for (index=1;index <=max_index;index++) {
        if ( g[index] > max ) { 
           max = g[index];
           index_of_max = index;
        }
    }
    return index_of_max;
}

void main_pass(int num_nodes, int * d, string * data, string A, string B) {
     int i,j,k, max_gain, g[num_nodes/2], Gain[num_nodes/2], actual_gain = INT_MAX, iteration = 0;
     string max_gain_ele1, max_gain_ele2, search_string, to_swap_ele_A[num_nodes/2], to_swap_ele_B[num_nodes/2], group1, group2;
     while (actual_gain > 0 && iteration < 50) {
        group1 = A; group2 = B; 
        for (i=1;i<=num_nodes/2;i++) {
            get_largest_decrease_cutcost_exchange_nodes(d,data,A,B,&max_gain,&max_gain_ele1,&max_gain_ele2); 
            g[i] = max_gain; to_swap_ele_A[i-1] = max_gain_ele1; to_swap_ele_B[i-1] = max_gain_ele2;
            cout << "\n\nMax gain achieved in iteration " << i << " is:" << max_gain << "\n";
            cout << "********************************************************************\n"; 
            delete_element(&A, &max_gain_ele1);
            delete_element(&B, &max_gain_ele2);
            cout << "\n\nA after deletion of " << max_gain_ele1 << " is: " << A << ":: B after deletion of " << max_gain_ele2 << " is: " << B << "\n\n";
            //cout << "\n\nCheck\n";
            //cout << "\nLength of A:" << A.length() << "\n\n";
            if ( A.length() > 0 ) {
               update_d_values(num_nodes,A,B,data,d,max_gain_ele1,max_gain_ele2);
            }
        }
        Gain[1] = g[1];
        for (i=2;i<=num_nodes/2;i++) {
            //cout << i << "\n";
            Gain[i] = Gain[i-1] + g[i];
        }
        //cout << "\n\nCheck\n\n";
        //k = distance(Gain, max_element(Gain, Gain + num_nodes/2));
        k = max_element_index(Gain,num_nodes/2);
        cout << "\n\nNumber of elements to swap (k value) : " << k << "\n\n";
        actual_gain = Gain[k];
        for (j=1;j<=k;j++) {
            swap_ele(&group1, &group2, to_swap_ele_A[j-1], to_swap_ele_B[j-1]);
        }
        A = group1; B = group2;
        cout << "\n\n\nPartitions after pass are:\nA:" << A << "\nB:" << B << "\nGain achieved = " << actual_gain << "\n\n"; 
        //exit(0);
        cut_cost(num_nodes,A,data);
        initial_d_values(num_nodes,A,data,d);
        iteration++;
     }
}


int main () {
    string * data;
    string group1, group2, A, B;
    unsigned int num_nodes, num_terminals;
    std::string nodes_file, nets_file;
    std::map<std::string,int> node_mapping;
    nodes_file = "/home/mohit/Downloads/uwindsor/Physical_design_automation/lecture_notes/partitioning/part_bm_ckts/spp_N199_E232_R11_154.nodes.txt";
    nets_file = "/home/mohit/Downloads/uwindsor/Physical_design_automation/lecture_notes/partitioning/part_bm_ckts/spp_N199_E232_R11_154.nets.txt";
    read_node_names(&node_mapping, nodes_file, &num_nodes, &num_terminals);
    std::string data[num_nodes];
    /*data = read_node_data(&num_nodes, data);
    cout << "\n\n\nNum nodes is :" << to_string(num_nodes) << "\n\n\n";
    int d[num_nodes];
    display_data(num_nodes, data);
    initial_partition(num_nodes,&group1,&group2);
    cout << "Group1 : " << group1 << "\n";
    cout << "Group2 : " << group2 << "\n";
    cut_cost(num_nodes, group1, data);
    A = group1;
    B = group2;
    initial_d_values(num_nodes,group1,data,d);
    main_pass(num_nodes,d,data,A,B); */
    return 0;
}
