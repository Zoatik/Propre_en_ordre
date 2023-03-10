PEO: main.o Robot.o File.o message.o
	g++ obj/main.o obj/Robot.o obj/File.o obj/message.o -o PEO

main.o: main.cpp simulation.h 
	g++ -c main.cpp -o obj/main.o

simulation.o: simulation.cpp simulation.h
	g++ -c simulation.cpp -o obj/simulation.o

Robot.o: Robot.cpp Robot.h
	g++ -c Robot.cpp -o obj/Robot.o

File.o: File.cpp File.h
	g++ -c File.cpp -o obj/File.o

message.o: message.cc message.h
	g++ -c message.cc -o obj/message.o
clean:
	rm obj/*.o PEO


        
