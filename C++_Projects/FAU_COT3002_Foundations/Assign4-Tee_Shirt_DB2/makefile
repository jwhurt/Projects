a.out: TeesForHaiti2.o Tinv.o safeio.o
	g++ TeesForHaiti2.o Tinv.o safeio.o

TeesForHaiti2.o: TeesForHaiti2.cpp Tinv.h safeio.h
	g++ -c TeesForHaiti2.cpp

Tinv.o: Tinv.cpp Tinv.h safeio.h
	g++ -c Tinv.cpp

safeio.o: safeio.cpp safeio.h
	g++ -c safeio.cpp