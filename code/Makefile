CXX = g++
CXXFLAGS = -g -Wall -Wextra -Wpedantic

.PHONY : all
all: execute

execute : main.cpp vehicle.o separateChaining.o redBlackTree.o
	$(CXX) $(CXXFLAGS) -o $@ $^
	
vehicle.o : vehicle.cpp
	$(CXX) $(CXXFLAGS) -c $<

separateChaining.o : separateChaining.cpp
	$(CXX) $(CXXFLAGS) -c $<

redBlackTree.o : redBlackTree.cpp
	$(CXX) $(CXXFLAGS) -c $<

.PHONY : clean
clean :
	$(RM) *.o
	$(RM) execute

