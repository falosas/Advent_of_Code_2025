bin/AOC1: AOC1.cpp
	mkdir -p bin
	g++ -o bin/AOC1 AOC1.cpp

bin/AOC1-2: AOC1-2.cpp
	mkdir -p bin
	g++ -o bin/AOC1-2 AOC1-2.cpp

bin/AOC5: AOC5.cpp
	mkdir -p bin
	g++ -o bin/AOC5 AOC5.cpp

bin/AOC5-2: AOC5-2.cpp
	mkdir -p bin
	g++ -o bin/AOC5-2 AOC5-2.cpp

bin/AOC7: AOC7.cpp
	mkdir -p bin
	g++ -o bin/AOC7 AOC7.cpp

bin/AOC7-2: AOC7-2.cpp
	mkdir -p bin
	g++ -o bin/AOC7-2 AOC7-2.cpp

bin/AOC8: AOC8.cpp
	mkdir -p bin
	g++ -o bin/AOC8 AOC8.cpp

bin/AOC8-2: AOC8-2.cpp
	mkdir -p bin
	g++ -o bin/AOC8-2 AOC8-2.cpp


clean:
	rm -r *.o *.gch bin

