projet: main.o Robot.o File.o message.o Simulation.o shape.o Particle.o
	g++ obj/main.o obj/Robot.o obj/File.o obj/message.o obj/Simulation.o obj/shape.o obj/Particle.o -o projet

main.o: main.cpp Simulation.h 
	g++ -c main.cpp -o obj/main.o

Simulation.o: Simulation.cpp Simulation.h
	g++ -c Simulation.cpp -o obj/Simulation.o

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
	rm obj/*.o projet


        
