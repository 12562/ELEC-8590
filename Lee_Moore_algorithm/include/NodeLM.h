
class NodeLM: public Node {
      public:
        NodeLM(float x, float y, std::string name = ""): Node(x, y, name) {}
        NodeLM() {}
        void setLabel(int label); 
        int getLabel();
        bool is_obstruction();
        void setnodeasobstruction();
        std::vector<NodeLM*> neighbors();
        void addNeighbor(NodeLM* node);
        void update_line_exists_with_neighbor_node(NodeLM*,int);
        void update_has_source_node(int);
        int is_source_node();
        int is_target_node();
        void update_has_target_node(int);
        int is_to_be_shown_connected_to(NodeLM*);
        //int is_shown_connected_to(NodeLM*);
        //void update_is_shown_to(NodeLM*,int,int);
        //int* getColor();
        //void setColor(int *color); 
        //void add_path_prevNode(NodeLM*, int);
        //NodeLM* get_prev_node(int,int,int);
        //std::string get_direction(int,int,int); 
        std::string get_direction(int,NodeLM*,std::string,std::string); 
        //int get_num_bends(int,int,int);
        int get_num_bends(int,NodeLM*,std::string,std::string);
        std::vector<std::pair<std::pair<std::string,std::string>,NodeLM*>> get_path(int);
        //std::vector<std::pair<int,int>> get_path(int);
        void add_prev_node_data(int, std::string, std::string, NodeLM*, std::string, int, int, int);
        void delete_prev_node_data();
        int is_already_on_a_nets_path(int);
        int is_already_on_a_selected_path();
        void add_on_selected_path();
        void delete_from_selected_path();
        std::pair<std::string,NodeLM*> get_path_with_min_bends(int, std::string);
        std::pair<int,int> get_path_on_single_net_and_with_min_bends(int);
        std::pair<int,int> get_coordinates(int);
        int get_node_num(int, int);
      private:
        int _label = 0;
        bool _is_obstruction = false;
        std::vector<std::pair<NodeLM*,int>> _neighbors;
        int _is_on_selected_path;
        int _has_source_node = 0;
        int _has_target_node = 0;
        //int _color[3] = {0,0,0};
        //std::vector<std::pair<int,NodeLM*>> _prev_node;
        std::vector<std::tuple<int,std::pair<std::string,std::string>,NodeLM*,std::string,int,int>> _path_data;
};
