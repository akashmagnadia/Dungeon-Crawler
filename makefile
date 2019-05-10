amagna2Proj7: amagna2Proj7.o roomClass.o tileClass.o playerClass.o
	g++ -o proj7 amagna2Proj7.o roomClass.o tileClass.o playerClass.o

amagna2Proj7.o: amagna2Proj7.cpp amagna2Proj7.h
	g++ -c amagna2Proj7.cpp

roomClass.o: roomClass.cpp amagna2Proj7.h
	g++ -c roomClass.cpp

tileClass.o: tileClass.cpp amagna2Proj7.h
	g++ -c tileClass.cpp

playerClass.o: playerClass.cpp amagna2Proj7.h
	g++ -c playerClass.cpp

clean:
	rm amagna2Proj7.o roomClass.o tileClass.o playerClass.o amagna2Proj7
