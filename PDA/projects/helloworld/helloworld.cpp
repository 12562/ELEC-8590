#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;


struct Node { 
              string node;
              int degree;
              Node * next;
            } *start, *newptr, *save, *ptr, *rear;

Node * Create_New_Node(string, int);
void Display_data (Node ** data, int numnets);
void Insert_End(Node*);

int main(int argc, char * argv[]) {
    int numpins, numpins_read, degree;
    int ctr = 1;
    int ctr2 = 1;
    string input_file;
    if ( argc > 1 ) {
        input_file = argv[1];
    } else {
        input_file = "../../partitioning/spp_N151_E167_R11_80_nets.txt";
    }
    int starting_pos = input_file.find("E") + 1;
    int num_characters = input_file.find("_",input_file.find("_") + 1);
    int numnets = atoi(input_file.substr(starting_pos,num_characters).c_str());
    cout << numnets;
    Node * data [numnets];
    string mytext, node, tmp;
    ifstream file(input_file.c_str());
    //ifstream file("/home/mohit/README-FIRST.txt");
    getline(file,mytext);
    while (mytext.find("NumPins") == string::npos) { 
        getline(file,mytext);
    }
    //cout << mytext << "\n";
    tmp = mytext.substr(mytext.find(":") + 2);
    cout << tmp << endl;
            //std::stringstream ss(tmp);
            //ss >> numpins;
            //numpins = stoi(mytext.substr(mytext.find("NumPins") + 2));
    numpins = atoi(tmp.c_str());
    
    while (ctr <= numnets) {
        getline(file,mytext);
        if ( mytext.find("NetDegree") != string::npos) {
            tmp = mytext.substr(mytext.find(":") + 2);
            cout << tmp << " ";
            degree = atoi(tmp.c_str());
            //data[ctr]->degree = degree;
            //data[ctr]->node = "";
            //data[ctr]->next = NULL;
            rear = NULL;
            ctr2 = 1;
            while ( ctr2 <= degree) {
                getline(file,mytext);
                node = mytext.substr(0,mytext.find(" "));
                cout << node << " ";
                newptr = Create_New_Node(node, degree);
                if (ctr2 == 1) {
                    data[ctr] = newptr;
                    rear = newptr;
                } else {
                    rear->next = newptr;
                    rear = newptr;
                }
                ctr2++;
            }
            cout << "\n";
            ctr++;
        }
    }

    file.close();
    Display_data(data,numnets);
    return 0;
}

Node * Create_New_Node (string node, int degree) {
    ptr = new Node;
    ptr->node = node;
    cout << "Node: " << ptr->node << "\n";
    ptr->degree = degree;
    ptr->next = NULL;
    return ptr;
}

void Display_data (Node ** data, int numnets) {
     int ctr = 1;
     cout << "*****************************DISPLYAING DATA***************************\n";
     while ( ctr <= numnets ) {
        ptr = data[ctr];
        while (ptr->next != NULL) {
            cout << ptr->node << " ";
            ptr = ptr->next;
        }
        cout << ptr->node << "\n";
        ctr++;
     }
}