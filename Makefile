dep = mem.h mem.cpp queue.h queue.cpp process.h process.cpp system.h system.cpp simulator.h

simulator : $(dep)
	g++ -std=c++11 -o simulator mem.cpp queue.cpp process.cpp system.cpp simulator.cpp

clean :
	rm simulator *.txt
