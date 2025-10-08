CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O2
TARGET = calculator
SOURCES = calculator.cpp

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

.PHONY: clean