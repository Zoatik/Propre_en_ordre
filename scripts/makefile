PEO: main.o Robot.o File.o message.o
	g++ main.o Robot.o File.o message.o -o PEO

main.o: main.cpp simulation.h 
	g++ -c main.cpp

simulation.o: simulation.cpp simulation.h
	g++ -c simulation.cpp

Robot.o: Robot.cpp Robot.h
	g++ -c Robot.cpp 

File.o: File.cpp File.h
	g++ -c File.cpp

message.o: message.cc message.h
	g++ -c message.cc
clean:
	rm *.o PEO


        
