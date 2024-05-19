# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -I./libs/glad -I./src

# Linker flags
LDFLAGS = -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl

# Source files
SRC = ./src/main.cpp ./libs/glad/glad.c

# Output executable
TARGET = openChess

# Build target
$(TARGET): $(SRC)
	$(CXX) -o $(TARGET) $(SRC) $(CXXFLAGS) $(LDFLAGS)

# Clean up build files
clean:
	rm -f $(TARGET)