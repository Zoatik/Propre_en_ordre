PEP: main.o Robot.o File.o message.o
	g++ main.o Robot.o File.o message.o -o PEP

main.o: main.cpp Robot.h
	g++ -c main.cpp

Robot.o: Robot.cpp Robot.h File.h 
	g++ -c Robot.cpp 

File.o: File.cpp File.h constantes.h
	g++ -c File.cpp

message.o: message.cc message.h
	g++ -c message.cc

clean:
	rm *.o PEP
        
