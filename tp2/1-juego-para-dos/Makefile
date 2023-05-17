SOURCE = juego-para-dos.cpp

exe: $(SOURCE)
	g++ -O0 -g $(SOURCE) -o $@

.PHONY: clean, run
clean:
	rm exe
	
run: exe
	./exe < test1
	./exe < test2
	./exe < test3
