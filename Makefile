CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic
TARGET = matrix_ops
SRC = main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)