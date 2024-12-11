# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall

# Project name
TARGET = my_program

# Source files
SRCS = main_aee.cpp input.cpp parser.cpp data_storage.cpp


OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

rebuild: clean all
