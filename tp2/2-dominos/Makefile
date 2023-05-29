SOURCE = dominosLineal.cpp

exe: $(SOURCE)
	g++ -O2 $(SOURCE) -o $@

.PHONY: clean, run
clean:
	rm exe

run: exe
	./exe < test1
	./exe < test2
	./exe < test3
	./exe < test4
	./exe < test5
