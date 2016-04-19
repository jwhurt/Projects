a.out: fly.o balloon.o randgen.o
	g++ fly.o balloon.o randgen.o

fly.o: fly.cpp balloon.h

balloon.o: balloon.cpp balloon.h
	g++ -c balloon.cpp

randgen.o: randgen.cpp randgen.h
	g++ -c randgen.cpp