CXX=g++
CXXFLAGS=-std=c++23 -Wall  -Iinclude

SRC=$(wildcard src/*.cpp)

route: $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o test