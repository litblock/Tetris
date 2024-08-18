CXX = g++

CXXFLAGS = -std=c++17 -Wall

SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

SRCS = main.cpp

TARGET = tetris

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) $(SFML_LIBS)

clean:
	rm -f $(TARGET)