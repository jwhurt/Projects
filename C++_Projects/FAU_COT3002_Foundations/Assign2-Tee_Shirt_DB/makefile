a.out: TeesForHaiti.o Tinv.o safeio.o
	g++ TeesForHaiti.o Tinv.o safeio.o

TeesForHaiti.o: TeesForHaiti.cpp safeio.h
	g++ -c TeesForHaiti.cpp

Tinv.o: Tinv.cpp Tinv.h safeio.h
	g++ -c Tinv.cpp

safeio.o: safeio.cpp	
	g++ -c safeio.cpp