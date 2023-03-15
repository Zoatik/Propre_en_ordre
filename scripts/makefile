PEO: main.o Robot.o File.o message.o simulation.o shape.o Particle.o
	g++ obj/main.o obj/Robot.o obj/File.o obj/message.o obj/simulation.o obj/shape.o obj/Particle.o -o PEO

main.o: main.cpp simulation.h 
	g++ -c main.cpp -o obj/main.o

simulation.o: simulation.cpp simulation.h
	g++ -c simulation.cpp -o obj/simulation.o

Robot.o: Robot.cpp Robot.h
	g++ -c Robot.cpp -o obj/Robot.o

Particle.o: Particle.cpp Particle.h
	g++ -c Particle.cpp -o obj/Particle.o

File.o: File.cpp File.h
	g++ -c File.cpp -o obj/File.o

message.o: message.cc message.h
	g++ -c message.cc -o obj/message.o

shape.o: shape.cc shape.h
	g++ -c shape.cc -o obj/shape.o

clean:
	rm obj/*.o PEO


        
