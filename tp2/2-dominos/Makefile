SOURCE = dominos2.cpp

exe: $(SOURCE)
	g++ -O0 -g $(SOURCE) -o $@

.PHONY: clean, run
clean:
	rm exe
	
run: exe
	./exe < test1
	./exe < test2
	./exe < test3
	./exe < test4
	./exe < test5

