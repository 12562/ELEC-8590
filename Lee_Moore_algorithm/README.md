# Lee-Moore Algorithm Implementation

## Introduction
This LM algorithm implementation was done as a programming assignment for [ELEC-8950 Physical Design Automation](https://sites.google.com/view/mohammedaskhalid/teaching?authuser=0) course at [University of Windsor](https://github.com/UWindsor) 

## Report explaining the implementation and the experiments in detail
[LM-Maze router implementation](https://github.com/12562/ELEC-8590/blob/master/Lee_Moore_algorithm/Maze_router_implementation.pdf)

## Graphical Output result
  - Running the program binary would give a graphical output where a wave propagates from the source node to the target node where adjacent grid cells are 
progressively labeled one by one according to the distance of the “wavefront” from Source until the target node is reached. 

  - Once the target node is reached, a shortest path is then retraced from Target to Source with decreasing labels during the retracing phase.

  - The final output looks like the following:


    ![Final maze router output](https://github.com/12562/ELEC-8590/blob/eefb436ea7dbbf0c6acba7ae12f520f81281138a/Lee_Moore_algorithm/img/Maze%20router%20implementation%20graphical%20output.png)
    
  - A video demonstration of the graphical output can be found here:

    <a href="http://www.youtube.com/watch?feature=player_embedded&v=807nTElZUS4" target="_blank"><img src="http://img.youtube.com/vi/807nTElZUS4/0.jpg" alt="IMAGE ALT TEXT HERE" width="240" height="180" border="10" /></a>

## To run
```
./bin/LM_routing <Mazetests file> <debug=0|1>
```
   - Mazetests file can be found in the testcases directory [here](https://github.com/12562/ELEC-8590/tree/master/Lee_Moore_algorithm/testcases)

## To make LM_routing binary, run command:
```
make bin/LM_routing
```
   - This will create the LM_routing binary in ./bin directory
   - Dependencies for building bin/LM_routing are [SFML](https://www.sfml-dev.org/download.php), [freetype](https://freetype.org/download.html) and [jpeg](http://libjpeg.sourceforge.net/)

## Pseudo Code:
```
 -main
   --Read_command_line_parameters() ## Sets the variables maze_file and debug
   --read_maze_file()               ## Reads the maze file and saves gridsize, obstruction nodes and source and target nodes for nets to be routed 
   --fillGraphGrid()                ## Sets the x-y coordinates of each node and adds neighbors for a node
   --lm_router()                    ## Runs the LM Maze router algorithm and draws on screen while propagating wave front and retracing
```

## Files:
```
src/Lee_Moore_routing.cpp  :   Contains  "main" function
include/LM_router.h        :   Contains  "get_dir() retrace() lm_router()" functions 
include/LM_graphHelper.h   :   Contains  "Triangle(), Line(), drawtext(), drawGraph(), fillGraphGrid(), initialize_nodes_to_draw(), 
                                          draw_boundary_nodes_and_starting_grid(), draw_previous_nets_sources_and_sinks(), 
                                          draw_current_source_and_sink(), blink_current_source_and_sink(), draw_traced_path()" functions
include/read_data_helper.h :   Contains  "read_maze_file()" function
src/NodeKL.cpp             :   Contains  "NodeLM(), setLabel(), getLabel(), is_obstruction(), setnodeasobstruction(), neighbors(),
                                          addNeighbor(), update_line_exists_with_neighbor_node(), update_has_source_node(), is_source_node(),
                                          is_target_node(), update_has_target_node(), is_to_be_shown_connected_to(),
                                          get_direction(), get_num_bends(), get_path(), add_prev_node_data(), delete_prev_node_data(),
                                          is_already_on_a_nets_path(), is_already_on_a_selected_path(), add_on_selected_path(), 
                                          delete_from_selected_path(), get_path_with_min_bends(),
                                          get_path_on_single_net_and_with_min_bends(), get_coordinates(), get_node_num()" functions
src/Node.cpp               :   Contains  "Node::Node(), Node::x, Node::y, Node::name, Node::setX, Node::setY, Node::setName, 
                                          Node::addNeighbor, Node::neighbors, Node::distance" functions
include/Node.h             :   Header file for Node.cpp (Class declaration for Node)
include/NodeKL.h           :   Header file for NodeLM.cpp (Class declaration for NodeLM)
```

## References:

   - [Repository for Graph Node](https://github.com/abangfarhan/graph-sfml) 
   - [Algorithm Notes](https://github.com/12562/ELEC-8590/blob/26ceacf35a0acc6589e9a28547a57f326947e4e9/Lee_Moore_algorithm/related_papers/maze_route.pdf)
