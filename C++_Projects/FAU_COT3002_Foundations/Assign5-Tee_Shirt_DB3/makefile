a.out: TeesForHaiti_linked_list.o Tinv.o safeio.o
	g++ TeesForHaiti_linked_list.o Tinv.o safeio.o

TeesForHaiti_linked_list.o: TeesForHaiti_linked_list.cpp Tinv.h safeio.h
	g++ -c TeesForHaiti_linked_list.cpp

Tinv.o: Tinv.cpp Tinv.h safeio.h
	g++ -c Tinv.cpp

safeio.o: safeio.cpp safeio.h
	g++ -c safeio.cpp