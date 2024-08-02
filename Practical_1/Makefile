Main: main.o DynamicArrays.o testingFramework.o
	g++ main.o DynamicArrays.o testingFramework.o -o Main

main.o: main.cpp DynamicArrays.h testingFramework.h
	g++ -c main.cpp

DynamicArrays.o: DynamicArrays.cpp DynamicArrays.h
	g++ -c DynamicArrays.cpp

testingFramework.o: testingFramework.cpp testingFramework.h
	g++ -c testingFramework.cpp

run: Main
	./Main

clean:
	rm -f *.o Main

leaks: Main
	export MallocStackLogging=1; leaks -atExit --list -- ./Main | awk 'BEGIN { print "Memory Leak Summary:\\n" } /^Process/ { print } /^Leak/ { print }'
