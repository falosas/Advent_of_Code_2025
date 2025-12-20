bin/AOC1: Dia-1/AOC1.cpp
	mkdir -p bin
	g++ -o bin/AOC1 Dia-1/AOC1.cpp

bin/AOC1-2: Dia-1/AOC1-2.cpp
	mkdir -p bin
	g++ -o bin/AOC1-2 Dia-1/AOC1-2.cpp

bin/AOC5: Dia-5/AOC5.cpp
	mkdir -p bin
	g++ -o bin/AOC5 Dia-5/AOC5.cpp

bin/AOC5-2: Dia-5/AOC5-2.cpp
	mkdir -p bin
	g++ -o bin/AOC5-2 Dia-5/AOC5-2.cpp

bin/AOC7: Dia-7/AOC7.cpp
	mkdir -p bin
	g++ -o bin/AOC7 Dia-7/AOC7.cpp

bin/AOC7-2: Dia-7/AOC7-2.cpp
	mkdir -p bin
	g++ -o bin/AOC7-2 Dia-7/AOC7-2.cpp

bin/AOC8: Dia-8/AOC8.cpp
	mkdir -p bin
	g++ -o bin/AOC8 Dia-8/AOC8.cpp

bin/AOC8-2: Dia-8/AOC8-2.cpp
	mkdir -p bin
	g++ -o bin/AOC8-2 Dia-8/AOC8-2.cpp

bin/AOC11: Dia-11/AOC11.cpp
	mkdir -p bin
	g++ -o bin/AOC11 Dia-11/AOC11.cpp

bin/AOC11-2: Dia-11/AOC11-2.cpp
	mkdir -p bin
	g++ -o bin/AOC11-2 Dia-11/AOC11-2.cpp


clean:
	rm -r *.o *.gch bin

