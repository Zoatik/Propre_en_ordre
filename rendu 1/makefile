projet: projet.o Robot.o File.o message.o Simulation.o shape.o Particle.o
	g++ projet.o Robot.o File.o message.o Simulation.o shape.o Particle.o -o projet

projet.o: projet.cc Simulation.h 
	g++ -c projet.cc -o projet.o

Simulation.o: Simulation.cc Simulation.h
	g++ -c Simulation.cc -o Simulation.o

Robot.o: Robot.cc Robot.h
	g++ -c Robot.cc -o Robot.o

Particle.o: Particle.cc Particle.h
	g++ -c Particle.cc -o Particle.o

File.o: File.cc File.h
	g++ -c File.cc -o File.o

message.o: message.cc message.h
	g++ -c message.cc -o message.o

shape.o: shape.cc shape.h
	g++ -c shape.cc -o shape.o

clean:
	rm *.o projet


        
