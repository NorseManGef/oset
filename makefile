bin/testoset: src/test_oset.cpp Include/oset.h | bin
	g++ -std=c++20 -o bin/testoset -I Include src/test_oset.cpp

test: bin/testoset
	./bin/testoset

bin:
	mkdir bin

clean:
	rm -rf bin