SOURCE = modems.cpp

exe: $(SOURCE)
	g++ -O2 $(SOURCE) -o $@

.PHONY: clean, run
clean:
	rm exe

run: exe
	./exe < test1
