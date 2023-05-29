CXX := g++
CXXFLAGS := -O3 -march=native

IN = $(wildcard implementaciones/*.cpp)
PRE = $(patsubst %.cpp,%.o,$(IN))
OUT  = $(patsubst implementaciones/%,binarios/%, $(PRE))

binarios/%: implementaciones/%
	$(CXX) $(CXXFLAGS) $< -o $@

default: $(OUT)
	python create-random-input.py
	python create-path-input.py

.PHONY: clean run
clean:
	rm ./binarios/*
	touch ./binarios/nodelete
	rm ./inputs/*
	touch ./inputs/nodelete
	rm ./runtime-data/*
	touch ./runtime-data/nodelete

run: default
	./run-random.sh
