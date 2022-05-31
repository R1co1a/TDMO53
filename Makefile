ALL=mo53
CXX=g++
CXXFLAGS=-std=c++14

mo53: main.cpp data_list.o data_table.o
	$(CXX) $(CXXFLAGS) -o mo53 main.cpp data_list.o data_table.o

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) $< -c -o $@

clean:
	rm -f *.o
	rm -f mo53
