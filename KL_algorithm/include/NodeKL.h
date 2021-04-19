
class NodeKL: public Node {
      public:
        NodeKL(float x, float y, std::string name = ""): Node(x, y, name) {}
        NodeKL() {}
        void setDvalue(float D); 
        float getDvalue();
        std::vector<std::pair<NodeKL*,float>> neighbors();
        void addNeighbor(NodeKL* node, float distance, bool distance_update);
        void update_distance (NodeKL* node, float distance);
        int getGroup();
        void setGroup(int g);
        float is_node2_connected(NodeKL node2);
      private:
        float _Dvalue;
        int _Group;
        std::vector<std::pair<NodeKL*,float>> _neighbors;
};
