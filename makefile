# Compiler and compiler flags
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Targets for part1 and part2
all: part1 part2

part1: part1.o List.o
	$(CXX) $(CXXFLAGS) -o part1 part1.o List.o

part2: part2.o spinlock.o
	$(CXX) $(CXXFLAGS) -o part2 part2.o spinlock.o 

# To compile part1.cpp
part1.o: part1.cpp
	$(CXX) $(CXXFLAGS) -c part1.cpp

# To compile part2.cpp
part2.o: part2.cpp
	$(CXX) $(CXXFLAGS) -c part2.cpp

# To compile List.cpp
List.o: List.cpp
	$(CXX) $(CXXFLAGS) -c List.cpp

spinlock.o: spinlock.cpp
	$(CXX) $(CXXFLAGS) -c spinlock.cpp

# Clean the build
clean:
	rm -f *.o part1 part2
