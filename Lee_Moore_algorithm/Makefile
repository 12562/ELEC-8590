CXX := g++
CXXFLAGS := --std=c++11 -g -Wall
INC := -I include
SFML_INCLUDE := -DSFML_STATIC -I "D:/Program Files (x86)/SFML/include"
SFML_LIB := -l sfml-graphics \
	-l sfml-window \
	-l sfml-system \
	-l freetype \
	-l jpeg \

bin/LM_routing: build/Lee_Moore_routing.o build/NodeLM.o build/Node.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIB)

build/Lee_Moore_routing.o: src/Lee_Moore_routing.cpp include/read_data_helper.h include/LM_graphHelper.h include/LM_router.h include/NodeLM.h include/Node.h
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(INC)

build/NodeLM.o: src/NodeLM.cpp include/NodeLM.h
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(INC)
 
build/Node.o: src/Node.cpp include/Node.h
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(INC)

clean:
	rm build/*.*
