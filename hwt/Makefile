SOURCE := $(wildcard *.cpp)
CXX := clang++-14

all:
	$(CXX) -O2 $(SOURCE) -Wpedantic -o hwt.bin
debug:
	$(CXX) -O0 -ggdb $(SOURCE) -Wpedantic -o hwt.bin
clean:
	rm hwt.bin
