#ifndef NODE_H
#define NODE_H

class Node {
      public:
         Node();
         Node(float x, float y, std::string name = "");
         Node(Node* node);
         float x();
         float y();
         std::string name();
         void setX(float x);
         void setY(float y);
         void setName(std::string name);
         void addNeighbor(Node* node);
         std::vector<Node*> neighbors();
         float distance(Node* neighbor);
      private:
         float _x;
         float _y;
         std::string _name;
         std::vector<Node*> _neighbors;
};

#endif
