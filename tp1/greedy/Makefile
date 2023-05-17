CXX := g++
CXXFLAGS := -O2

TARGET = app

$(TARGET): version-sort.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -f $(TARGET)
