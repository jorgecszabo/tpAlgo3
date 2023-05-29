CXX := g++
CXXFLAGS := -O3 -march=native

IN = $(wildcard implementaciones/*.cpp)
#OUT = $(subst .cpp,,$(IN))
PRE = $(patsubst %.cpp,%.o,$(IN))
OUT  = $(patsubst implementaciones/%,binarios/%, $(PRE))

binarios/%: implementaciones/%
	$(CXX) $(CXXFLAGS) $< -o $@

default: $(OUT)

.PHONY: clean
clean:
	rm ./binarios/*
	touch ./binarios/nodelete
	rm ./inputs/*
	touch ./inputs/nodelete
	rm ./runtime-data/*
	touch ./runtime-data/nodelete
