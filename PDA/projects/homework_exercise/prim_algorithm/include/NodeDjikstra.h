// Taken from https://github.com/abangfarhan/graph-sfml/blob/master/include/NodeDjikstra.h

#define large_number 99999

class NodeDj: public Node {
      public:
        NodeDj(float x, float y, std::string name = ""): Node(x, y, name) {}
        // tn is short for tentative
        float tnDist();
        void setTnDist(float newTnDist);
        bool visited();
        void setVisited(bool newVisited);
        NodeDj* prev();
        void setPrev(NodeDj* newPrev);
        std::vector<NodeDj*> neighbors();
        void addNeighbor(NodeDj* node);
      private:
        float _tnDist = large_number;
        bool _visited = false;
        NodeDj* _prev = NULL;
        std::vector<NodeDj*> _neighbors;
};
        
