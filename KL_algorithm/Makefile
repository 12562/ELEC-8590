CXX := g++
CXXFLAGS := --std=c++11 -g -Wall
INC := -I include
SFML_INCLUDE := -DSFML_STATIC -I "D:/Program Files (x86)/SFML/include"
SFML_LIB := -l sfml-graphics \
	-l sfml-window \
	-l sfml-system \
	-l freetype \
	-l jpeg \

bin/KL_partitioning: build/KL_partitioning.o build/NodeKL.o build/Node.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIB)

build/KL_partitioning.o: src/KL_partitioning.cpp include/read_data_helper.h include/KL_helper.h include/KL_bipartition_main.h include/NodeKL.h include/Node.h include/KL_graphHelper.h
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(INC)

build/NodeKL.o: src/NodeKL.cpp include/NodeKL.h
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(INC)
 
bin/base_KL: build/base_KL.o build/Node.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIB)

build/base_KL.o: src/base_KL.cpp include/Node.h include/KL_graphHelper.h
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(INC)


bin/base: build/base.o build/Node.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIB)

build/base.o: src/base.cpp include/Node.h include/graphHelper.h
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(INC)

build/Node.o: src/Node.cpp include/Node.h
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(INC)



bin/sp-djikstra: build/sp-djikstra.o build/NodeDjikstra.o build/Node.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIB)

build/sp-djikstra.o: src/sp-djikstra.cpp include/NodeDjikstra.h include/graphHelper.h
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(INC)

build/NodeDjikstra.o: src/NodeDjikstra.cpp include/NodeDjikstra.h
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(INC)




bin/st-prim: build/st-prim.o build/NodeDjikstra.o build/Node.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIB)

build/st-prim.o: src/st-prim.cpp include/NodeDjikstra.h include/graphHelper.h
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(INC)

clean:
	rm build/*.*
